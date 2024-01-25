#include"Channel.h"


Channel::Channel(Epoll* ep,int fd):ep_(ep),fd_(fd)    // 构造函数。
{

}

Channel::~Channel()                           // 析构函数。 
{
    // 在析构函数中，不要销毁ep_，也不能关闭fd_，因为这两个东西不属于Channel类，Channel类只是需要它们，使用它们而已。
}

void Channel::useet()                                    // 采用边缘触发。
{
    events_=events_|EPOLLET;
}

void Channel::enablereading()                     // 让epoll_wait()监视fd_的读事件。
{
    events_|=EPOLLIN;
    ep_->updatechannel(this);
}

int Channel::fd()                                            // 返回fd_成员。
{
    return fd_;
}




void Channel::setinepoll()                           // 把inepoll_成员的值设置为true。
{
    inepoll_=true;
}

void Channel::setrevents(uint32_t ev)         // 设置revents_成员的值为参数ev。
{
    revents_=ev;
}

bool Channel::inpoll()                                  // 返回inepoll_成员。
{
    return inepoll_;
}

uint32_t Channel::events()                           // 返回events_成员。
{
    return events_;
}

uint32_t Channel::revents()                          // 返回revents_成员。
{
    return revents_;
}

void Channel::handleevent()
{
   if(events_ & EPOLLRDHUP)
   {
      printf("client(eventfd=%d) disconnected.\n",fd_);
    close(fd_);    
   }
   else if(events_ & (EPOLLIN || EPOLLPRI))
   {
       readcallback_();
   }
   else if(revents_ &EPOLLOUT)
   {

   }
   else
   {
        printf("client(eventfd=%d) error.\n",fd_);
        close(fd_);            // 关闭客户端的fd。
   }
}

    void Channel::newconnection(Socket *servsock)
    {
        InetAddress clientaddr;             // 客户端的地址和协议。
        // 注意，clientsock只能new出来，不能在栈上，否则析构函数会关闭fd。
        // 还有，这里new出来的对象没有释放，这个问题以后再解决。
        Socket *clientsock=new Socket(servsock->accept(clientaddr));

        printf ("accept client(fd=%d,ip=%s,port=%d) ok.\n",clientsock->fd(),clientaddr.ip(),clientaddr.port());

        // 为新客户端连接准备读事件，并添加到epoll中。
        Channel *clientchannel=new Channel(ep_,clientsock->fd());   // 这里new出来的对象没有释放，这个问题以后再解决。
        clientchannel->setreadcallback(std::bind(&Channel::onmessage,clientchannel));
        clientchannel->useet();                 // 客户端连上来的fd采用边缘触发。
        clientchannel->enablereading();   // 让epoll_wait()监视clientchannel的读事件
    }
    void Channel::onmessage()
    {
        char buffer[1024];
        while (true)             // 由于使用非阻塞IO，一次读取buffer大小数据，直到全部的数据读取完毕。
        {    
            bzero(&buffer, sizeof(buffer));
            ssize_t nread = read(fd_, buffer, sizeof(buffer));
            if (nread > 0)      // 成功的读取到了数据。
            {
            // 把接收到的报文内容原封不动的发回去。
                printf("recv(eventfd=%d):%s\n",fd_,buffer);
                send(fd_,buffer,strlen(buffer),0);
            } 
            else if (nread == -1 && errno == EINTR) // 读取数据的时候被信号中断，继续读取。
            {  
                continue;
            } 
            else if (nread == -1 && ((errno == EAGAIN) || (errno == EWOULDBLOCK))) // 全部的数据已读取完毕。
            {
                break;
            } 
            else if (nread == 0)  // 客户端连接已断开。
            {  
                printf("client(eventfd=%d) disconnected.\n",fd_);
                close(fd_);            // 关闭客户端的fd。
                break;
            }
        }
    }
    void Channel::setreadcallback(std::function<void()>fn)
    {
        readcallback_ = fn;
    }