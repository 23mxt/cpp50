#include "Connector.h"

Connector::Connector(const string&msg,unsigned short port)
:_sock()
,_addr(msg,port){
}
Connector::~Connector(){
}
void Connector::connect(){
    int ret =::connect(_sock.fd(),(struct sockaddr*)_addr.getSockaddrPtr(),sizeof(_addr));
    if(ret==-1){
        ::perror("connect");
        return;
       /* exit(-1); */
    }
}
