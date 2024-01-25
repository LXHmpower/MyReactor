#include"Channel.h"


Channel::Channel(Epoll* ep,int fd,bool islisten):ep_(ep),fd_(fd),islisten_(islisten)      // 构造函数。
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

void Channel::handleevent(Socket *servsock)
{
   if(events_ & EPOLLRDHUP)
   {
      printf("client(eventfd=%d) disconnected.\n",fd_);
    close(fd_);    
   }
   else if(events_ & (EPOLLIN || EPOLLPRI))
   {
        if(islisten_ == true)
        {
            InetAddress clientaddr ;
            Socket *clientsock = new Socket(servsock->accept(clientaddr));
            printf ("accept client(fd=%d,ip=%s,port=%d) ok.\n",clientsock->fd(),clientaddr.ip(),clientaddr.port());

           Channel *clientchannel = new Channel(ep_,clientsock->fd(),false);
           clientchannel->useet();
           clientchannel->enablereading();
        }
        else
        {
            char buffer[1024];
            while(true)
            {
                bzero(&buffer,sizeof(buffer));
                ssize_t nread = read(fd_,buffer,sizeof(buffer));
                if(nread > 0)
                {
                    printf("recv(eventfd=%d):%s\n",fd_,buffer);
                    send(fd_,buffer,strlen(buffer),0);
                }
                else if(nread == -1 && errno == EINTR)
                {
                    continue;
                }
                else if(nread == 0 && (errno == EAGAIN || errno == EWOULDBLOCK))
                {
                    break;
                }
                else if(nread == 0)
                {
                    printf("client(eventfd=%d) disconnected.\n",fd_);
                    close(fd_);            // 关闭客户端的fd。
                    break;
                }
            }
        }
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
