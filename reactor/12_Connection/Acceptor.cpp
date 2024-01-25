#include"Acceptor.h"


Acceptor::Acceptor(EventLoop *loop,const std::string &ip, uint16_t port):loop_(loop)
{
    servsock_=new Socket(createnonblocking());   
    InetAddress servaddr(ip,port);             // 服务端的地址和协议。
    servsock_->setreuseaddr(true);
    servsock_->settcpnodelay(true);
    servsock_->setreuseport(true);
    servsock_->setkeepalive(true);
    servsock_->bind(servaddr);
    servsock_->listen();

    acceptchannel=new Channel(loop_,servsock_->fd());       // 这里new出来的对象没有释放，这个问题以后再解决。
    acceptchannel->setreadcallback(std::bind(&Channel::newconnection,acceptchannel,servsock_));
    acceptchannel->enablereading();       // 让epoll_wait()监视servchannel的读事件。
}


Acceptor::~Acceptor()
{

}
