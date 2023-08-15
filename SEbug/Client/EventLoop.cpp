#include "EventLoop.h"
#include<unistd.h>
#include<strings.h>
#include"TcpConnection.h"
#include <unistd.h>
#include <strings.h>
#include "TcpConnection.h"
#include "train.h"
#include <string.h>
EventLoop::EventLoop(const string &msg, unsigned short port)
    : _epfd(createEpollFd())
    , _isRunning(false)
    , _evtList(2)
    , _connector(msg, port)
{
    addEpollReadFd(_connector.fd());
    addEpollReadFd(STDIN_FILENO);
}
EventLoop::~EventLoop()
{
}
void EventLoop::start()
{
    _connector.connect();
    TcpConnectionPtr _conn(new TcpConnection(_connector.fd()));
    _conns.insert(std::make_pair(_connector.fd(), _conn));
    TcpConnectionPtr _conn2(new TcpConnection(STDIN_FILENO));
    _conns.insert(std::make_pair(STDIN_FILENO,_conn2));
    _isRunning = true;
    while (_isRunning)
    {
        epollWait();
    }
}
void EventLoop::stop()
{
}
void EventLoop::epollWait()
{
    int nready = 0;
    do
    {
        nready = ::epoll_wait(_epfd, &_evtList.front(), _evtList.size(), -1);
    } while (nready == -1 && errno == EINTR);
    if (nready == -1||nready==0)
    {
        ::perror("epollwait");
        _isRunning = false;
        return;
    }
    else
    {
        for (int i = 0; i < nready; i++)
        {
            if (_evtList[i].data.fd == _connector.fd())
            {
                auto conn = _conns[_connector.fd()];
                conn->receive();
            }
            else
            {
                Train train;
                memset(&train,0,sizeof(train));
                //读取ID  ID为1 为关键字推荐  ID为2 为网页搜索
                char ch;
                ::read(STDIN_FILENO, &ch, sizeof(ch));
                train._id = atoi(&ch);
                ::read(STDIN_FILENO,&ch,sizeof(ch));
                //读取内容
                char buf[4096] = {0};
                ::read(STDIN_FILENO, &buf, sizeof(buf));
                memcpy(train._buf,buf,strlen(buf)-1);
                train._length=strlen(train._buf);
                auto conn = _conns[_connector.fd()];
                conn->send(train);
            }
        }
    }
}
int EventLoop::createEpollFd()
{
    return ::epoll_create(1);
}
void EventLoop::addEpollReadFd(int fd)
{
    struct epoll_event evt;
    bzero(&evt, sizeof(evt));
    evt.data.fd = fd;
    evt.events = EPOLLIN;
    int ret = ::epoll_ctl(_epfd, EPOLL_CTL_ADD, fd, &evt);
    if (ret == -1)
    {
        ::perror("addEpollReadFd");
    }
}
void EventLoop::delEpollReadFd(int fd)
{
    struct epoll_event evt;
    bzero(&evt, sizeof(evt));
    evt.data.fd = fd;
    evt.events = EPOLLIN;
    ::epoll_ctl(_epfd, EPOLL_CTL_DEL, fd, &evt);
}
