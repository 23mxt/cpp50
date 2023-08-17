#ifndef _ACCEPTOR_H_
#define _ACCEPTOR_H_

#include "InetAddress.h"
#include "Socket.h"
#include <string>

using namespace std;

class Acceptor
{
public:
    Acceptor(const string &ip, const unsigned short &port);
    ~Acceptor();
    void ready();

private:
    void setReuseAddr();
    void setReusePort();
    void bind();
    void listen();

public:
    int accept();
    int fd() const;

private:
    InetAddress _addr;
    Socket _socket;
};

#endif 
