#ifndef __TCPCONNECTION_H__
#define __TCPCONNECTION_H__

#include "Socket.h"
#include "SocketIO.h"
#include "InetAddress.h"

#include <functional>
#include <memory>

using std::function;
using std::shared_ptr;

class TcpConnection;
using TcpConnectionPtr=shared_ptr<TcpConnection>;
using TcpConnectionCallback=function<void(const TcpConnectionPtr&)>;

class TcpConnection
: public std::enable_shared_from_this<TcpConnection>
, NonCopyable
{
public:
    explicit TcpConnection(int fd);
    ~TcpConnection();
    void send(const string &msg);
    string receive();
    //为了方便调试的函数
    string toString();

    bool isClosed() const;

    void setConnectionCallback(const TcpConnectionCallback & cb);
    void setMessageCallback(const TcpConnectionCallback & cb);
    void setCloseCallback(const TcpConnectionCallback & cb);

    void handleConnectionCallback();
    void handleMessageCallback();
    void handleCloseCallback();

private:
    //获取本端地址与对端地址
    InetAddress getLocalAddr();
    InetAddress getPeerAddr();

private:
    SocketIO _sockIO;

    //为了调试而加入的函数
    Socket _sock;
    InetAddress _localAddr;
    InetAddress _peerAddr;
    //三个回调函数
    TcpConnectionCallback _onConneciton;
    TcpConnectionCallback _onMessage;
    TcpConnectionCallback _onClose;
};

#endif
