#pragma once
#include<sys/epoll.h>
#include"Epoll.h"

class Epoll;

class Channel
{
private:
    int fd_;
    Epoll *ep_ = nullptr;
    bool inepoll_ = false;
    uint32_t events_ = 0;
    uint32_t revents_ = 0;

public:
    Channel(Epoll *ep,int fd);
    ~Channel();

    int fd();                                            // 返回fd_成员。
    void useet();                                    // 采用边缘触发。
    void enablereading();                     // 让epoll_wait()监视fd_的读事件。
    void setinepoll();                            // 把inepoll_成员的值设置为true。
    void setrevents(uint32_t ev);         // 设置revents_成员的值为参数ev。
    bool inpoll();                                  // 返回inepoll_成员。
    uint32_t events();                           // 返回events_成员。
    uint32_t revents();                          // 返回revents_成员。
};