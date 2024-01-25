#include"Socket.h"




/* // 创建一个非阻塞的socket。
int createnonblocking();
 class Socket
{
private:
    const int fd_;
public:
    Socket(int fd);
    ~Socket();

    int fd() const;  //返回fd的值
    void setreuseaddr(bool on);       // 设置SO_REUSEADDR选项，true-打开，false-关闭。
    void setreuseport(bool on);       // 设置SO_REUSEPORT选项。
    void settcpnodelay(bool on);     // 设置TCP_NODELAY选项。
    void setkeepalive(bool on);       // 设置SO_KEEPALIVE选项。
    void bind(const InetAddress& servaddr);        // 服务端的socket将调用此函数。
    void listen(int nn=128);                                    // 服务端的socket将调用此函数。
    int   accept(InetAddress& clientaddr);  
              // 服务端的socket将调用此函数。
}; 
 */


int createnonblocking()
{
    int listenfd = socket(AF_INET,SOCK_STREAM|SOCK_NONBLOCK,IPPROTO_TCP);
    if(listenfd < 0)
    {
        printf("%s:%s:%d listen socket create error:%d\n", __FILE__, __FUNCTION__, __LINE__, errno); exit(-1);
    }
    return listenfd;
}


Socket::Socket(int fd):fd_(fd){}

Socket::~Socket()
{
    ::close(fd_);
}

int Socket::fd() const
{
    return fd_;
}


void Socket::settcpnodelay(bool on)
{
    int optval = on ? 1 : 0;
    ::setsockopt(fd_, IPPROTO_TCP, TCP_NODELAY, &optval, sizeof(optval)); // TCP_NODELAY包含头文件 <netinet/tcp.h>
}

void Socket::setreuseaddr(bool on)
{
    int optval = on ? 1 : 0;
    ::setsockopt(fd_, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)); 
}

void Socket::setreuseport(bool on)
{
    int optval = on ? 1 : 0;
    ::setsockopt(fd_, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval)); 
}

void Socket::setkeepalive(bool on)
{
    int optval = on ? 1 : 0;
    ::setsockopt(fd_, SOL_SOCKET, SO_KEEPALIVE, &optval, sizeof(optval)); 
}

void Socket::bind(const InetAddress& servaddr)
{
    if(::bind(fd_,servaddr.addr(),sizeof(servaddr)) < 0)
    {
        perror("bind() failed"); close(fd_); exit(-1);
    }
}

int Socket::accept(InetAddress& clientaddr)
{
    sockaddr_in peeraddr;
    socklen_t len = sizeof(peeraddr);
    int clientfd =accept4(fd_,(sockaddr*)&peeraddr,&len,SOCK_NONBLOCK);
    clientaddr.setaddr(peeraddr);
    return clientfd;
}

void Socket::listen(int nn)
{
    if (::listen(fd_,nn) != 0 )        // 在高并发的网络服务器中，第二个参数要大一些。
    {
        perror("listen() failed"); close(fd_); exit(-1);
    }
}



