#pragma once 

#include<arpa/inet.h>
#include<netinet/in.h>
#include<string>

class InetAddress
{
private:
    sockaddr_in addr_;
public:
    InetAddress(const std::string &ip , uint16_t port);   //服务端监听socket的构造函数
    InetAddress(const sockaddr_in addr);                   //服务端处理客户端socket连接的构造函数
    ~InetAddress();

    const char *ip() const;                                 //返回ip地址
    uint16_t port() const;                                  //返回端口号
    const sockaddr* addr() const;                            //返回结构体  返回addr_成员的地址，转换成了sockaddr。                         
};