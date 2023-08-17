#include "EventLoop.h"
#include "Acceptor.h"
#include "TcpConnection.h"

#include <head.h>

#define EPOLL_EVENT_SIZE 1024

EventLoop::EventLoop(Acceptor & acceptor)
: _epfd(createEpollFd())
, _acceptor(acceptor)
, _isLooping(true)
, _evtList(EPOLL_EVENT_SIZE)
{
    epollAddReadFd(_acceptor.fd());
}

EventLoop::~EventLoop()
{
    close(_epfd);
}

void EventLoop::loop()
{
    while(_isLooping){
        waitEpollFd();
    }
}

void EventLoop::waitEpollFd()
{

    int nready;
    do {
        nready = epoll_wait(_epfd, &*_evtList.begin(), _evtList.size(), 5000);
    }while(nready == -1 && errno == EINTR);      

    if(nready == -1) {
        perror("epoll_wait");
    } else if(nready == 0) {
        printf("epoll_wait timeout!\n");
    } else {
        //nready > 0  
        if(nready == (int)_evtList.size()) {
            _evtList.resize(2 * nready);//在保留原有数据的基础上扩容
        }

        for(int i = 0; i < nready; ++i) {
            int fd = _evtList[i].data.fd;
            if(fd == _acceptor.fd()) {
                //进行新连接的处理
                handleNewConnection();
            } else {
                //对已经建立好的连接进行处理
                handleMessage(fd);
            }
        }
    }
}

void EventLoop::handleNewConnection()
{
    int peerfd = _acceptor.accept();
    epollAddReadFd(peerfd);
    TcpConnectionPtr conn(new TcpConnection(peerfd));
    //设置回调函数
    conn->setConnectionCallback(_onConnection);
    conn->setMessageCallback(_onMessage);
    conn->setCloseCallback(_onClose);

    //添加到map中进行管理
    _connsMap.insert(std::make_pair(peerfd, conn));
    //调用新连接建立好的回调函数
    conn->handleConnectionCallback();
}

void EventLoop::handleMessage(int fd)
{
    //通过fd查找TcpConnection对象
    auto it = _connsMap.find(fd);
    if(it!= _connsMap.end()) {
        auto conn = it->second;
        //判断该连接是否断开
        if(conn->isClosed()) {//连接断开
            conn->handleCloseCallback();
            epollDelReadFd(fd);
            _connsMap.erase(fd);
        } else {//处理消息
            conn->handleMessageCallback();
        }
    }
}


int EventLoop::createEpollFd()
{
    int fd = ::epoll_create1(0);
    if(fd < 0) {
        perror("epoll_create1");
    }
    return fd;
}

void EventLoop::epollAddReadFd(int fd)
{
    struct epoll_event ev;
    bzero(&ev, sizeof(ev));
    ev.data.fd = fd;
    ev.events = EPOLLIN;
    int ret = epoll_ctl(_epfd, EPOLL_CTL_ADD, fd, &ev);
    if(ret < 0) {
        perror("epoll_ctl");
    }
}

void EventLoop::epollDelReadFd(int fd)
{
    struct epoll_event ev;
    bzero(&ev, sizeof(ev));
    ev.data.fd = fd;
    ev.events = EPOLLIN;
    int ret = epoll_ctl(_epfd, EPOLL_CTL_DEL, fd, &ev);
    if(ret < 0) {
        perror("epoll_ctl");
    }
}
