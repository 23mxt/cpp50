#ifndef __WD_EventLoop_HPP__ 
#define __WD_EventLoop_HPP__ 

#include "TcpConnection.h"

#include <map>
#include <vector>
#include <memory>
using std::map;
using std::vector;
using std::shared_ptr;


class Acceptor;//类的前向声明

class TcpConnection;
using TcpConnectionPtr = shared_ptr<TcpConnection>;

class EventLoop
{
public:
    EventLoop(Acceptor & acceptor);
    ~EventLoop();

    void loop();
    void unloop() { _isLooping = false; }
    void setAllCallbacks(TcpConnectionCallback && cb1,
                         TcpConnectionCallback && cb2,
                         TcpConnectionCallback && cb3)
    {
        _onConnection = std::move(cb1);
        _onMessage = std::move(cb2);
        _onClose = std::move(cb3);
    }
private:
    void waitEpollFd();
    void handleNewConnection();
    void handleMessage(int );

    int createEpollFd();
    void epollAddReadFd(int fd);
    void epollDelReadFd(int fd);

private:
    int _epfd;
    Acceptor & _acceptor;
    bool _isLooping;
    vector<struct epoll_event> _evtList;
    map<int, TcpConnectionPtr> _connsMap;

    TcpConnectionCallback _onConnection;
    TcpConnectionCallback _onMessage;
    TcpConnectionCallback _onClose;
};

#endif

