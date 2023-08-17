#ifndef _EventLoop_H_
#define _EventLoop_H_

#include "TcpConnection.h"
#include <functional>
#include <memory>
#include <vector>
#include <map>

using std::shared_ptr;
using std::function;
using std::vector;
using std::map;

class Acceptor;
class TcpConnection;
using TcpConnectionPtr = shared_ptr<TcpConnection>;
using TcpConnectionCallback = fuction<void(const TcpConnectionPtr &)>;

class EventLoop
{
public:
    explicit EventLoop(int fd);
    ~EventLoop();

    void loop();
    void unloop() {_isLooping = false;}
    
    //*
    void waitEpollFd();
    void handleNewConnection();
    void handleMessage();

    void createEpollFd();
    void EpollAddFd();
    void EpollDelFd();

private:
    int _epfd;
    Acceptor &_acceptor;
    bool _isLooping;
    vector<struct epoll_event> _EvList;
    map<int, TcpConnectionPtr> _connsMap;

    TcpConnectionCallback _onConnection;
    TcpConnectionCallback _onMessage;
    TcpConnectionCallback _onClose;
};

#endif 

