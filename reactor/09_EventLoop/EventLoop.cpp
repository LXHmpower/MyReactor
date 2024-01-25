#include "EventLoop.h"

/* class EventLoop
{
private:
    Epoll *ep_;
public:
    EventLoop();
    ~EventLoop();

    void run();
    Epoll *ep();
};
 */


EventLoop::EventLoop():ep_(new Epoll)
{

}

EventLoop::~EventLoop()
{
    delete(ep_);
}

void EventLoop::run()
{
    while (true)        // 事件循环。
    {
       std::vector<Channel *> channels=ep_->loop();         // 等待监视的fd有事件发生。

        for (auto &ch:channels)
        {
            ch->handleevent();        // 处理epoll_wait()返回的事件。
        }
    }
}


Epoll* EventLoop::ep()
{
    return ep_;
}