#include"../include/EventLoop.h"
#include<unistd.h>
#include <sys/epoll.h>
#include<errno.h>
#include<iostream>
#include"../include/Acceptor.h"
#include"../include/TcpConnection.h"
#include<utility>
#include<string>
#include<cstring>
#include<iostream>
using std::cout;
using std::endl;
EventLoop::EventLoop(Acceptor& acceptor):
_epfd(createEpollFd())
,_evfd(createEventFd())
,_isLooping(false)
,_acceptor(acceptor)
,_evtList(1024)
,_mutex()
,_timerfd(createTimerfd())
{
    _cachemanager=CacheManager::createInstance();
    addEpollReadFd(_acceptor.fd());
    addEpollReadFd(_evfd);
    addEpollReadFd(_timerfd);
}
EventLoop::~EventLoop(){
    close(_epfd);
}
void EventLoop::loop(){
    _isLooping = true;
    timer_start();
    while(_isLooping){
        waitEpollFd();
    }
}
void EventLoop::unloop(){
    _isLooping = false;
}

void EventLoop::runInLoop(Functors &&functor){
    {   
        MutexLockGuard autolock(_mutex);
        if(functor)
            _pendings.push_back(std::move(functor));
    }
    wakeup();
}

void EventLoop::setNewConnectionCallback(TcpConnectionCallback&& onNewConnection){
    _onNewConnection = std::move(onNewConnection);
}
void EventLoop::setMessageCallback(TcpConnectionCallback&& onMessage){
    _onMessage = std::move(onMessage);
}
void EventLoop::setCloseCallback(TcpConnectionCallback&& onClose){
    _onClose = std::move(onClose);
}

void EventLoop::waitEpollFd(){
    int nready;
    do{
        nready = epoll_wait(_epfd,&*_evtList.begin(),_evtList.size(),5000);
    }while(nready==-1&&errno==EINTR);
    if(nready == -1){
        perror("nready = -1");
        return ;
    }else if(nready ==0){
        std::cout<<"epollwait timeout"<<std::endl;
    }else {
        if(nready == (int)_evtList.size()){
            _evtList.resize(_evtList.capacity()<<1);
        }
        for(int i = 0;i<nready;i++){
            if(_evtList[i].data.fd == _acceptor.fd()){
                handleNewConnection();
            }else if(_evtList[i].data.fd == _evfd){
                handleEventRead();
                
                doPengdingFunctor();
            }else if(_evtList[i].data.fd == _timerfd)
            {
                printf("timer ready\n");
                uint64_t tmp;
                read(_timerfd,&tmp,sizeof(tmp));
                _cachemanager->periodicupdatecaches();
            }
            else {
                handleMessage(_evtList[i].data.fd);
            }
        }
    }
}
void EventLoop::handleNewConnection(){
    int connfd = _acceptor.accept();

    addEpollReadFd(connfd);
    TcpConnectionPtr pconnd(new TcpConnection(connfd,this));
    pconnd->setNewConnectionCallback(_onNewConnection);
    pconnd->setMessageCallback(_onMessage);
    pconnd->setCloseCallback(_onClose);
    _conns.insert(std::make_pair(connfd,pconnd));

    pconnd->handleNewConnectionCallback();

}
void EventLoop::handleMessage(int fd){
    auto it = _conns.find(fd);
    if(it != _conns.end()){
        if(it->second->isClosed()){
            it->second->handleCloseCallback();
            delEpollReadFd(fd);
            _conns.erase(it);
        }else{
            it->second->handleMessageCallback();
        }
    }else{
        std::cerr<<"no "<<fd<<std::endl;
    }
}
int EventLoop::createEpollFd(){
    return epoll_create(1);
}
int EventLoop::createTimerfd()
{
    return timerfd_create(CLOCK_MONOTONIC,0);
}
void EventLoop::timer_start()
{
    struct itimerspec timerSpec;
    timerSpec.it_interval.tv_sec=6;
    timerSpec.it_interval.tv_nsec=0;
    timerSpec.it_value.tv_sec=1;
    timerSpec.it_value.tv_nsec=0;
    timerfd_settime(_timerfd,0,&timerSpec,nullptr);
}
void EventLoop::timer_stop()
{
    close(_timerfd);
}
void EventLoop::addEpollReadFd(int fd){
    struct epoll_event event;
    bzero(&event,sizeof(epoll_event));
    event.data.fd = fd;
    event.events = EPOLLIN;
    int ret =epoll_ctl(_epfd,EPOLL_CTL_ADD,fd,&event);
    if(ret){
        perror("addEpollReadFd");
        return ;
    }
}
void EventLoop::delEpollReadFd(int fd){
    struct epoll_event event;
    bzero(&event,sizeof(epoll_event));
    event.data.fd = fd;
    event.events = EPOLLIN;
    epoll_ctl(_epfd,EPOLL_CTL_DEL,fd,&event);
}
int EventLoop::createEventFd(){
    return eventfd(0,0);
}
void EventLoop::handleEventRead(){
    uint64_t one = 1;
    read(_evfd,&one,sizeof(uint64_t)); 
}
void EventLoop::wakeup(){
    uint64_t one = 1;
    write(_evfd,&one,sizeof(uint64_t));
}
void EventLoop::doPengdingFunctor(){
    vector<Functors> tmp;
    {
        MutexLockGuard autolock(_mutex);
        tmp.swap(_pendings);
    }
    for(auto &cb:tmp){
        cb();
    }
}
