#ifndef _INETADDRESS_H_
#define _INETADDRESS_H_

#include <arpa/inet.h>  //sockaddr_in头文件
#include <string>

using std::string;

class InetAddress
{
public:
    InetAddress(const string &ip, unsigned short port);
    InetAddress(const struct sockaddr_in &addr);
    ~InetAddress();

    //从sockaddr_in
    //获取ip
    string ip();
    //获取端口号
    unsigned short port();
    const struct sockaddr_in* getInetAddress();

private:
    struct sockaddr_in _addr;
};

#endif 
