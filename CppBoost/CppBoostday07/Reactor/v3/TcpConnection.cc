#include "TcpConnection.h"
#include <iostream>
#include <sstream>

using std::cout;
using std::endl;
using std::ostringstream;

TcpConnection::TcpConnection(int fd)
: _sockIO(fd)
, _sock(fd)
, _localAddr(getLocalAddr())
, _peerAddr(getPeerAddr())
{

}

TcpConnection::~TcpConnection()
{
    cout << "~TcpConnection()" << endl;
}

void TcpConnection::send(const string &msg)
{
    _sockIO.writen(msg.c_str(), msg.size());
}

string TcpConnection::receive()
{
    char buff[65535] = {0};
    _sockIO.readLine(buff, sizeof(buff));

    return string(buff);
}

string TcpConnection::toString()
{
    ostringstream oss;
    oss << _localAddr.ip() << ":"
        << _localAddr.port() << "---->"
        << _peerAddr.ip() << ":"
        << _peerAddr.port();

    return oss.str();
}
    
bool TcpConnection::isClosed() const
{
    int ret = 0;
    do{
        char buff[64] = {0};
        ret = recv(_sock.fd(), buff, sizeof(buff), MSG_PEEK);
    }while(ret == -1 && errno == EINTR);
    return ret == 0;
}

void TcpConnection::setConnectionCallback(const TcpConnectionCallback & cb)
{
    _onConneciton = cb;
}

void TcpConnection::setMessageCallback(const TcpConnectionCallback & cb)
{   _onMessage = cb;    }

void TcpConnection::setCloseCallback(const TcpConnectionCallback & cb)
{   _onClose = cb;  }

void TcpConnection::handleConnectionCallback()
{
    if(_onConneciton) {
        //通过this指针获取本对象的shared_ptr
        _onConneciton(shared_from_this());
    }    
}
void TcpConnection::handleMessageCallback()
{
    if(_onMessage) {
        _onMessage(shared_from_this());
    }
}

void TcpConnection::handleCloseCallback()
{
    if(_onClose) {
        _onClose(shared_from_this());
    }
}

//获取本端的网络地址信息
InetAddress TcpConnection::getLocalAddr()
{
    struct sockaddr_in addr;
    socklen_t len = sizeof(struct sockaddr );
    //获取本端地址的函数getsockname
    int ret = getsockname(_sock.fd(), (struct sockaddr *)&addr, &len);
    if(-1 == ret)
    {
        perror("getsockname");
    }

    return InetAddress(addr);
}

//获取对端的网络地址信息
InetAddress TcpConnection::getPeerAddr()
{
    struct sockaddr_in addr;
    socklen_t len = sizeof(struct sockaddr );
    //获取对端地址的函数getpeername
    int ret = getpeername(_sock.fd(), (struct sockaddr *)&addr, &len);
    if(-1 == ret)
    {
        perror("getpeername");
    }

    return InetAddress(addr);
}
