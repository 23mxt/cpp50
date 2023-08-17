#ifndef _InetAddress_H_
#define _InetAddress_H_

#include <arpa/inet.h>
#include <string>

using std::string;

class InetAddress
{
public:
    InetAddress(const string &ip, int port);
    InetAddress(const sockaddr_in addr);
    ~InetAddress();

    string ip() const;
    int port() const;
    const struct sockaddr_in *getInetAddressPtr();

private:
    struct sockaddr_in _addr;
};

#endif 

