#include"EventLoop.h"

// 在构造函数中创建Epoll对象ep_。
EventLoop::EventLoop():ep_(new Epoll)                   
{

}

// 在析构函数中销毁ep_。
EventLoop::~EventLoop()
{
    delete ep_;
}

void EventLoop::run()
{
    while (true)
    {
        std::vector<Channel *> channels = ep_->loop();

        for(auto &ch:channels)
        {
            ch->handleevent();  
        }
    }    
}

Epoll* EventLoop::ep()
{
    return ep_;
}

