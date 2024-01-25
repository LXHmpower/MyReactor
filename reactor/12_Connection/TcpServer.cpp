#include "TcpServer.h"

/*
class TcpServer
{
private:
    EventLoop loop_;         // 一个TcpServer可以有多个事件循环，现在是单线程，暂时只用一个事件循环。
public:
    TcpServer(const std::string &ip,const uint16_t port);
    ~TcpServer();
};*/

TcpServer::TcpServer(const std::string &ip,const uint16_t port)
{
    acceptor_ =  new Acceptor(&loop_,ip,port);   
}

TcpServer::~TcpServer()
{
    delete acceptor_;
}

// 运行事件循环。
void TcpServer::start()          
{
    loop_.run();
}