#pragma once 
#include<functional>
#include"Socket.h"
#include"InetAddress.h"
#include"Channel.h"
#include"EventLoop.h"


class Acceptor
{
private:
    EventLoop* loop_;
    Socket* servsock_;
    Channel* acceptchannel;
public:
    Acceptor(EventLoop *loop,const std::string &ip, uint16_t port);
    ~Acceptor();
};
