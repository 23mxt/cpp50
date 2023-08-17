#include "TcpConnection.h"
#include <sstream>
#include <iostream>
#include <sys/socket.h>

using namespace std;


TcpConnection::TcpConnection(int fd)
:_sockIO(fd)
,_sock(fd)
,_localAddr(getlocalAddr())
,_peerAddr(getpeerAddr())
{

}

TcpConnection::~TcpConnection()
{

}

void TcpConnection::send(const string &msg)
{
    _sockIO.write(msg.c_str(), msg.size());
}

string TcpConnection::receive()
{
    char buff[65535] = {0};
    _sockIO.readn(buff, sizeof(buff));

    return string(buff);
}


//打印本端和对端的端口和地址信息
string TcpConnection::toString()
{
    ostringstream oss;
    oss << _localAddr.ip() << "--------"
        << _localAddr.port() << "--------->"
        << _peerAddr.ip() << "--------"   
        << _peerAddr.port() << "-------->";

    return oss.str();
    //因为oss的打印本身是以char类型进行打印，所以要用string类型进行返回
}

//获取本端和对端的信息
InetAddress TcpConnection::getlocalAddr()
{
    struct sockaddr_in _addr;
    socklen_t len = sizeof(struct sockaddr);
    int ret = getsockname(_sock.fd(), (struct sockaddr *)&_addr, &len);
    if(ret == -1)
    {
        perror("getsockname");
    }

    return _localAddr(&_addr); 
}


InetAddress TcpConnection::getpeerAddr()
{
    struct sockaddr_in _addr;
    socklen_t len = sizeof(struct sockaddr);
    int ret = getsockname(_sock.fd(), (struct sockaddr *)&_addr, &len);
    if(ret == -1)
    {
        perror("getsockname");
    }

    return _peerAddr(&_addr); 

}
