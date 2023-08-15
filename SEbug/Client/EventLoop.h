#ifndef __EVENTLOOP_H__
#define __EVENTLOOP_H__
#include "Connector.h"
#include<sys/epoll.h>
#include<vector>
#include<unordered_map>
#include<memory>
using std::shared_ptr;
using std::unordered_map;
using std::vector;
class TcpConnection;
class EventLoop{
    using TcpConnectionPtr = shared_ptr<TcpConnection>;
public:
    EventLoop(const string&msg,unsigned short port);
    ~EventLoop();
    void start();
    void stop();
private:
    void epollWait();
    int createEpollFd();
    void addEpollReadFd(int fd);
    void delEpollReadFd(int fd);
private:
    int _epfd;
    bool _isRunning;
    vector<struct epoll_event>_evtList;
    Connector _connector;
    unordered_map<int,TcpConnectionPtr> _conns;
};

#endif