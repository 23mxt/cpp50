#ifndef __SEARCHENGINESERVER_H__
#define __SEARCHENGINESERVER_H__
#include"TcpServer.h"
#include "ThreadPool.h"
#include"WebPageQuery.h"
#include "CacheManager.hpp"

//搜索引擎负责服务器和线程池的创建
class SearchEngineServer{
public:
    SearchEngineServer(const string&ip,unsigned short port);
    ~SearchEngineServer();
    //启动服务器
    void start();
    //关闭服务器
    void stop();
    //连接建立事件 被注册给TcpServer使用 
    void onConnection(const TcpConnectionPtr &conn);
    
    //消息到达事件以及消息发送完毕各半个事件 被注册给TcpServer使用  
    void onMessage(const TcpConnectionPtr &conn);
    //连接断开事件 被注册给TcpServer使用
    void onClose(const TcpConnectionPtr &conn);
private:
    ThreadPool _pool;
    TcpServer _tcpServer;
};

#endif
