#include"Epoll.h"

/* class Epoll
{
private:
    static const int MaxEvents = 100;
    int epollfd_ = -1;
    epoll_event events_[MaxEvents];
public:
    Epoll();
    ~Epoll();

    void addfd(int fd , uint32_t op);
    std::vector<epoll_event> loop(int timeout=-1);
}; */

Epoll::Epoll()
{
    if((epollfd_ = epoll_create(1)) == -1)
    {
         printf("epoll_create() failed(%d).\n",errno); exit(-1);
    }
}


Epoll::~Epoll()                                          
{
    close(epollfd_);           // 在析构函数中关闭epollfd_。
}

void Epoll::addfd(int fd , uint32_t op)
{
    epoll_event ev;
    ev.data.fd = fd;
    ev.events = op;
    if(epoll_ctl(epollfd_,EPOLL_CTL_ADD,fd,&ev)  == -1)
    {
         printf("epoll_ctl() failed(%d).\n",errno); exit(-1);
    }
}

std::vector<epoll_event> Epoll::loop(int timeout)
{
    std::vector<epoll_event> evs;

    bzero(events_,sizeof(events_));
    int infds = epoll_wait(epollfd_,events_,MaxEvents,timeout);

    if(infds < 0)
    {
         perror("epoll_wait() failed"); exit(-1);
    }
    if(infds == 0)
    {
       printf("epoll_wait() timeout.\n"); return evs; 
    }
    

    for(int ii=0;ii<infds;ii++)
    {
        evs.push_back(events_[ii]);
    }
    return evs;
}
