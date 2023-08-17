#ifndef _TCPCONNECTION_H_
#define _TCPCONNECTION_H_ 

#include "Socket.h"
#include "SocketIO.h"
#include "InetAddress.h"


class TcpConnection
{
public:
    TcpConnection(int fd); 
    ~TcpConnection();
    void send(const string &msg);
    string receive();

    //打印本端和对端的端口和地址信息
    string toString();

    //获取本端和对端的信息
    InetAddress getlocalAddr();
    InetAddress getpeerAddr();

private:
    SocketIO _sockIO;
    Socket _sock;

    InetAddress _localAddr;
    InetAddress _peerAddr;
};

#endif
