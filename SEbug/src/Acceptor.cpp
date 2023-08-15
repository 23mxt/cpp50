#include "../include/Acceptor.h"
#include"sys/types.h"
#include"sys/socket.h"
Acceptor::Acceptor(const string& ip, const unsigned short port)
:_sock()
,_addr(ip,port){}
Acceptor::~Acceptor(){
}
void Acceptor::ready() {
    setReuseAddr();
    setReusePort();
    bind();
    listen();
    return;
}

int Acceptor::accept() {
    return ::accept(_sock.fd(),nullptr,nullptr);
}

void Acceptor::setReuseAddr() {
    int opt = 1;
    setsockopt(_sock.fd(),SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
    return;
}

void Acceptor::setReusePort() {
    int opt = 1;
    setsockopt(_sock.fd(),SOL_SOCKET,SO_REUSEPORT,&opt,sizeof(opt));
    return;
}

void Acceptor::bind() {
    ::bind(_sock.fd(),(struct sockaddr*)_addr.getsocketaddrptr(),sizeof(_addr));
    return;
}

void Acceptor::listen(int backlog) {
    ::listen(_sock.fd(),backlog);
    return;
}

int Acceptor::fd()const{
    return _sock.fd();
}