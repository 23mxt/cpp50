#ifndef __CONNECTOR_H__
#define __CONNECTOR_H__
#include"InetAddress.h"
#include"Socket.h"
class Connector{
public:
    Connector(const string&msg,unsigned short port);
    ~Connector();
    void connect();
    int fd(){
        return _sock.fd();
    }
private:
    Socket _sock;
    InetAddress _addr;
};
#endif