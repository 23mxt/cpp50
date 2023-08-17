#ifndef _Acceptor_H_
#define _Acceptor_H_

#include "InetAddress.h"
#include "Socket.h"
#include "NonCopyable.h"
#include <string>

using std::string;


class Acceptor
:NonCopyable
{
public:
    Acceptor(const string &ip, unsigned short port); 
    ~Acceptor();
    void ready();
private:
    void setReuseAddress() const;
    void setReusePort() const;
    void bind();
    void listen();
public:
    int fd() const;
    int accept();

private:
    Socket _sock;
    InetAddress _addr;
};

#endif 

