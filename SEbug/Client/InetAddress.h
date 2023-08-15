/**
 * Project CPP49
 */


#ifndef _INETADDRESS_H
#define _INETADDRESS_H
#include<string>
#include<netinet/ip.h>
using std::string;
class InetAddress {
public: 
    
/**
 * @param addr
 */
explicit InetAddress(const struct sockaddr_in addr);
    
/**
 * @param ip
 * @param port
 */
InetAddress(const string& ip, unsigned short port);
    
~InetAddress();
    
string ip()const;
    
unsigned short port()const;
    
struct sockaddr_in* getSockaddrPtr();
private: 
    struct sockaddr_in _addr;
};

#endif //_INETADDRESS_H