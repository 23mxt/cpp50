#include "TcpConnection.h"
#include <string.h>
#include <iostream>
#include <sstream>

using std::cout;
using std::endl;
using std::ostringstream;

TcpConnection::TcpConnection(int fd)
:_sockIO(fd)
,_sock(fd)
,_localAddr(getLocalAddr())
,_peerAddr(getPeerAddr())
{}

TcpConnection::~TcpConnection()
{
    cout << " ~TcpConnection() " << endl;
}

void TcpConnection::send(const string &msg)
{
    _sockIO.writen(msg.c_str(), msg.size());
}

int TcpConnection::receive()
{
    char buff[65535] = {0};
    bzero(buff, sizeof(buff));
    return _sockIO.readline(buff, sizeof(buff));
}

string TcpConnection::toString()//打印四元组信息
{
    ostringstream oss;
    
    oss << _localAddr.ip() << ":"
        << _localAddr.port() << "------>"
        << _peerAddr.ip() << ":"
        << _peerAddr.port() << " ";

    return oss.str();
}

//获取本端网络信息
InetAddress TcpConnection::getLocalAddr()
{
    struct sockaddr_in _addr; 
    socklen_t len = sizeof(_addr); 
    int ret = getsockname(_sock.fd(), (struct sockaddr *)&_addr, &len);
    if(ret)
    {
        perror("getsockname");
    }

    return InetAddress(_addr);
}

InetAddress TcpConnection::getPeerAddr()
{
    struct sockaddr_in _addr; 
    socklen_t len = sizeof(_addr); 
    int ret = getpeername(_sock.fd(), (struct sockaddr *)&_addr, &len);
    if(ret)
    {
        perror("getpeername");
    }

    return InetAddress(_addr);
}

//const 要去掉，因为readline可能修改
bool TcpConnection::isClosed() 
{
    char buff[64] = {0};
    int ret = 0;
    do {
        ret = _sockIO.readline(buff, sizeof(buff));
    }while(ret == -1 && errno == EINTR);

    return ret == 0;
}

void TcpConnection::setConnectionCallback
    (const TcpConnectionCallback &cb)
{
    if(_onConnection)
    {
        _onConnection(cb);
    }       
}
void TcpConnection::setMessageCallback
    (const TcpConnectionCallback &cb)
{
    if(_onMessage)
    {
        _onMessage(cb);
    }
}
void TcpConnection::setCloseCallback
    (const TcpConnectionCallback &cb)
{
    if(_onClose)
    {
        _onClose(cb);
    }
}

void TcpConnection::handleConnectionCallback()
{
    if(_onConnection)
    {
        _onConnection();
    }
}

void TcpConnection::handleMessageCallback()
{
    if(_onMessage)
    {
        _onMessage();
    }
}

void TcpConnection::handleCloseCallback()
{
    if(_onClose)
    {
        _onClose();
    }
}
