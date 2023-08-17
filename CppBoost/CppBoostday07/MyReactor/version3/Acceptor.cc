#include "Acceptor.h"
#include <Mycpphead.h>

Acceptor::Acceptor(const string &ip, unsigned short port)
:_sock()
,_addr(ip, port)
{}

Acceptor::~Acceptor()
{}

void Acceptor::ready()
{
    setReuseAddress();
    setReusePort();
    bind();
    listen();
}

void Acceptor::setReuseAddress() const
{
    int on = 1;
    int ret = setsockopt(_sock.fd(), SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    if(ret == -1)
    {
        perror("setsockopt addr");
    }
}

void Acceptor::setReusePort() const
{
    int on = 1;
    int ret = setsockopt(_sock.fd(), SOL_SOCKET, SO_REUSEPORT, &on, sizeof(on));
    if(ret == -1)
    {
        perror("setsockopt port");
    }
}

void Acceptor::bind()
{
    int ret = ::bind(_sock.fd(), (struct sockaddr *)&_addr, sizeof(struct sockaddr));
    if(ret)
    {
        perror("bind");
    }
}

void Acceptor::listen()
{
    int ret = ::listen(_sock.fd(), 128);
    if(ret)
    {
        perror("listen");
    }
}

int Acceptor::accept()
{
    int cnnfd = ::accept(_sock.fd(), nullptr, nullptr);
    if(cnnfd == -1)
    {
        perror("accept");
    }

}

int Acceptor::fd() const
{
    return _sock.fd();
}

