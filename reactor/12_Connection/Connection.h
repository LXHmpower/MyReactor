#pragma once 
#include <functional>
#include"Socket.h"
#include"Channel.h"
#include "InetAddress.h"
#include"EventLoop.h"


class Connection
{
private:
    EventLoop *loop_;
    Socket *clientsock_;
    Channel *clientchannel_;
public:
    Connection(EventLoop *loop,Socket *clientsock);
    ~Connection();
};