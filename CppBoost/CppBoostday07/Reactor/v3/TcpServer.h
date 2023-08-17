#ifndef __WD_TcpServer_HPP__ 
#define __WD_TcpServer_HPP__ 

#include "Acceptor.h"
#include "TcpConnection.h"
#include "EventLoop.h"

class TcpServer
{
public:
    TcpServer(const string & ip, unsigned short port);
    ~TcpServer(){}
    void start();
    void stop();
    void setAllCallbacks(TcpConnectionCallback && cb1,
                        TcpConnectionCallback && cb2,
                        TcpConnectionCallback && cb3)
    {
        _loop.setAllCallbacks(std::move(cb1), std::move(cb2), std::move(cb3));
    }

private:
    Acceptor _acceptor;
    EventLoop _loop;
};

#endif

