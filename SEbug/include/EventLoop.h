#ifndef __EVENTLOOP_H__
#define __EVENTLOOP_H__
#include"sys/eventfd.h"
#include<unordered_map>
#include<memory>
#include<vector>
#include<functional>
#include"MutexLock.h"
#include "CacheManager.hpp"
#include <sys/timerfd.h>
using std::vector;
using std::shared_ptr;
using std::unordered_map;
class Acceptor;
class TcpConnection;
using TcpConnectionPtr = shared_ptr<TcpConnection>;
using TcpConnectionCallback = std::function<void(const TcpConnectionPtr&)>;
class EventLoop{
    using Functors = std::function<void()>;
public:
    EventLoop(Acceptor& acceptor);
    ~EventLoop();
    void loop();
    void unloop();
    void setNewConnectionCallback(TcpConnectionCallback&& onNewConnection);
    void setMessageCallback(TcpConnectionCallback&& onMessage);
    void setCloseCallback(TcpConnectionCallback&& onClose);
    void runInLoop(Functors&& functor);
private:
    void waitEpollFd();
    void handleNewConnection();
    void handleMessage(int fd);
    int createEpollFd();
    void addEpollReadFd(int fd);
    void delEpollReadFd(int fd);
    void handleEventRead();
    void wakeup();
    int createEventFd();
    void doPengdingFunctor();
    int createTimerfd();
    void timer_start();
    void timer_stop();
private:
    int _epfd;
    int _evfd;
    bool _isLooping;
    vector<Functors> _pendings;
    Acceptor& _acceptor;
    vector<struct epoll_event> _evtList;
    unordered_map<int,TcpConnectionPtr> _conns;
    TcpConnectionCallback _onNewConnection;
    TcpConnectionCallback _onMessage;
    TcpConnectionCallback _onClose;
    MutexLock _mutex;
    CacheManager* _cachemanager;
    int _timerfd;
};
#endif