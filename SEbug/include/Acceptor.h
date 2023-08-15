#ifndef _ACCEPTOR_H
#define _ACCEPTOR_H
#include <string>
#include"Socket.h"
#include"InetAddress.h"
using std::string;
class Acceptor
{
public:
    Acceptor(const string &ip, const unsigned short port);

    ~Acceptor();

    void ready();

    int accept();
    
    int fd()const;
private:
    Socket _sock;
    InetAddress _addr;

    void setReuseAddr();

    void setReusePort();

    void bind();

    void listen(int backlog = 10);
};

#endif //_ACCEPTOR_H