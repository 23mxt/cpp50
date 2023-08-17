#include "InetAddress.h"
#include <strings.h>
#include <iostream>

using namespace std;

InetAddress::InetAddress(const string &ip, unsigned short port)
{
    cout << " InetAddress(const string &ip = 127.0.0.1 , unsigned short port = 8888) " << endl;
    //先清空_addr
    bzero(&_addr, sizeof(sockaddr_in));
    
    //再设置
    _addr.sin_family = AF_INET;
    _addr.sin_port = htons(port);   
    _addr.sin_addr.s_addr = inet_addr(ip.c_str());
}

InetAddress::InetAddress(const struct sockaddr_in &addr)
:_addr(addr)
{
}

InetAddress::~InetAddress()
{

}

//从sockaddr_in
//获取ip
string InetAddress::ip()
{
    return string(inet_ntoa(_addr.sin_addr));
}

//获取端口号
unsigned short InetAddress::port()
{
    return ntohs(_addr.sin_port);
}

const struct sockaddr_in* InetAddress::getInetAddress()
{
    return &_addr;
}
