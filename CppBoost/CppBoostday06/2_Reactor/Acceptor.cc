#include "Acceptor.h"
#include <sys/types.h>



Acceptor::Acceptor(const string &ip, const unsigned short &port)
:_addr(ip, port)
,_socket()
{
    
}

Acceptor::~Acceptor()
{
    //析构交给子对象
}

void Acceptor::ready()
{
    setReuseAddr();
    setReusePort();
    bind();
    listen();
}

void Acceptor::setReuseAddr()
{
    int on = 1;
    //允许地址重用
    int ret = setsockopt(_socket.fd(),SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    if(ret)
    {
        perror("setsockopt");
        return;
    }
}
void Acceptor::setReusePort()
{
    int on = 1;
    //允许端口重用
    int ret = setsockopt(_socket.fd(),SOL_SOCKET, SO_REUSEPORT, &on, sizeof(on));
    if(ret)
    {
        perror("setsockopt");
        return;
    }
}

void Acceptor::bind()
{
    int ret = ::bind(_socket.fd(), 
                   (struct sockaddr *)_addr.getInetAddress(), sizeof(struct sockaddr));
    if(ret)
    {
        perror("bind");
    }
    
}

void Acceptor::listen()
{
    int ret = ::listen(_socket.fd(), 20);
    if(ret)
    {
        perror("listen");
    }
}

int Acceptor::accept()
{
    int cnnfd = ::accept(_socket.fd(), nullptr, nullptr);
    if(cnnfd)
    {
        perror("accept");
        return -1;
    }
    return cnnfd;
}

int Acceptor::fd() const
{
    return _socket.fd();
}

