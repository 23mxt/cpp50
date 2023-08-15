#include "../include/InetAddress.h"
#include <string.h>
using std::string;
InetAddress::InetAddress(const struct sockaddr_in& addr)
:_addr(addr){

}

InetAddress::InetAddress(const string& ip, const unsigned short port)
{
    bzero(&_addr,sizeof(struct sockaddr_in));
    _addr.sin_family = AF_INET;
    _addr.sin_port = htons(port);
    _addr.sin_addr.s_addr = inet_addr(ip.c_str());
}

InetAddress::~InetAddress() {

}

string InetAddress::ip() const{
    return inet_ntoa(_addr.sin_addr);
}

unsigned short InetAddress::port()const {
    return ntohs(_addr.sin_port);
}

const struct sockaddr_in* InetAddress::getsocketaddrptr()const {
    return &_addr;
}