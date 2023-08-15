/**
 * Project CPP49
 */


#include "InetAddress.h"
#include<sys/socket.h>
#include<arpa/inet.h>
/**
 * InetAddress implementation
 */


/**
 * @param addr
 */
InetAddress::InetAddress(const struct sockaddr_in addr)
:_addr(addr)
{
}

/**
 * @param ip
 * @param port
 */
InetAddress::InetAddress(const string& ip, unsigned short port) 
{
    _addr.sin_family = AF_INET;
    _addr.sin_addr.s_addr = inet_addr(ip.c_str());
    _addr.sin_port = htons(port);
}

InetAddress::~InetAddress() {

}

/**
 * @return string
 */
string InetAddress::ip()const{
    return inet_ntoa(_addr.sin_addr);
}

/**
 * @return unsigned short
 */
unsigned short InetAddress::port()const{
    return ntohs(_addr.sin_port);
}

/**
 * @return struct sockaddr_in*
 */
struct sockaddr_in* InetAddress::getSockaddrPtr() {
    return &_addr;
}