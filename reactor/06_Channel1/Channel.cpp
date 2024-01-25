#include"Channel.h"

/* 
class Channel
{
private:
    int fd_;
    Epoll *ep_ = nullptr;
    bool inepoll = false;
    uint32_t events_ = 0;
    uint32_t revents_= 0;
public:
    Channel(Epoll* ep , int fd);
    ~Channel(); 

    int fd();
    void useet();
    void enablereading();
    void setrevents(uint32_t ev);
    bool isepoll();
    uint32_t events();
    uint32_t revents();

}
 */

Channel::Channel(Epoll* ep,int fd):ep_(ep),fd_(fd)      // 构造函数。
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
