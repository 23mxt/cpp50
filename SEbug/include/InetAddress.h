#ifndef _INETADDRESS_H
#define _INETADDRESS_H
#include<string>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
class InetAddress
{
public:
    explicit InetAddress(const struct sockaddr_in &addr);

    InetAddress(const std::string &ip, const unsigned short port);

    ~InetAddress();

    std::string ip()const;

    unsigned short port()const;

    const struct sockaddr_in *getsocketaddrptr()const;

private:
    struct sockaddr_in _addr;
};
#endif //_INETADDRESS_H