#ifndef _TcpConnection_H_
#define _TcpConnection_H_

#include "NonCopyable.h"
#include "Socket.h"
#include "InetAddress.h"
#include "SocketIO.h"

#include <functional>
#include <memory>

using std::function;
using std::shared_ptr;

class TcpConnection;
using TcpConnectionPtr = shared_ptr<TcpConnection>;
using TcpConnectionCallback = function<void(const TcpConnectionPtr &)>; //这里不能用右值，否则只能注册一次

class TcpConnection
:NonCopyable
,public std::enable_shared_from_this<TcpConnection>
{
public:
    TcpConnection(int fd);
    ~TcpConnection();
    
    void send(const string &msg);
    int receive();

    string toString();//打印四元组信息

    InetAddress getLocalAddr();
    InetAddress getPeerAddr();
    
    bool isClosed() ;

    void setConnectionCallback(const TcpConnectionCallback &cb);
    void setMessageCallback(const TcpConnectionCallback &cb);
    void setCloseCallback(const TcpConnectionCallback &cb);

    void handleConnectionCallback();
    void handleMessageCallback();
    void handleCloseCallback();
private:
    SocketIO _sockIO;
    Socket _sock;

    InetAddress _localAddr;
    InetAddress _peerAddr;

    TcpConnectionCallback _onConnection;
    TcpConnectionCallback _onMessage;
    TcpConnectionCallback _onClose;
};

#endif 

