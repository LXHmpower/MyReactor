#include"InetAddress.h"


/* class InetAddress
{
private:
    sockaddr_in aadr_;
public:
    InetAddress(const std::string &ip , uint16_t port);
    InetAddress(const sockaddr_in addr);
    ~InetAddress();

    const char *ip() const;
    uint16_t port() const;
    const sockaddr* addr() const;
}; */




InetAddress::InetAddress(const std::string &ip , uint16_t port)  //服务端监听socket的构造函数
{
    addr_.sin_family = AF_INET;                       
    addr_.sin_port = htons(port);
    addr_.sin_addr.s_addr = inet_addr(ip.c_str());
}

InetAddress::InetAddress(const sockaddr_in addr):addr_(addr)     //服务端处理客户端socket连接的构造函数
{
}

InetAddress::~InetAddress(){}

const char* InetAddress::ip() const                  //返回ip地址
{
    return inet_ntoa(addr_.sin_addr);
}

uint16_t InetAddress::port() const                   //返回端口号
{
    return ntohs(addr_.sin_port);
} 

const sockaddr* InetAddress::addr() const           //返回结构体  返回addr_成员的地址，转换成了sockaddr。                                   
{
    return (sockaddr*)&addr_;
}