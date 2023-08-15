#include "../include/SearchEngineServer.h"
#include "../include/TcpConnection.h"
#include "../include/Thread.h"
#include <iostream>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <nlohmann/json.hpp>
#include "../include/KeyRecommander.hpp"
#include "../include/mylogger.hpp"

//网页查询和关键字推荐都使用了全局变量
WebPageQuery Globalwebpagequery;
KeyRecommander GlobalkeyRecommander;

using json = nlohmann::json;
using std::cout;
using std::endl;


class MyTask{
public:
    MyTask(const string&msg,const TcpConnectionPtr& conn)
    :_msg(msg)
    ,_conn(conn){}
    
    void process(){
        //处理 msg
        LogDebug("current_thread name :%s",current_thread::name);
        
        //先偏移，再强转得到服务类型
        char * signal = &*_msg.begin()+4;
        int ID = *(int*)signal;
        
        char* querymsg = (char*)&*(_msg.begin()+8); //用户查询的内容 
        string processedMsg;
        switch(ID)
        {
            case 1:
            {
            //创造一个cache，用来实现lru缓存，提高关键字推荐的效率
            CacheManager* pInstance = CacheManager::createInstance();
            auto cache = pInstance->getcache(atoi(current_thread::name)+1);
            //服务端要返回给客户端的关键字推荐
            string sendMsg = GlobalkeyRecommander.response(querymsg,cache);
            LogInfo("KEYRECOMMAND : sendMsg : %s\n",sendMsg.c_str());
            int length = sendMsg.size();
            int ID=100; //服务端发送给客户端的消息id
            char buf[10] = {0};
            memcpy(buf,&length,sizeof(length));
            memcpy(buf+4,&ID,sizeof(ID));
            //服务端要发送的消息头部
            std::copy(buf,buf+8,std::back_inserter(processedMsg));
            processedMsg.append(sendMsg);
            }
            break;
            case 2:
            {
            //网页查询结果
            //未分页
            cout << "debug position1" << endl;
            string sendMsg = Globalwebpagequery.doQuery(querymsg);
            cout << "debug position2" << endl;
            cout << "sendMsg" << sendMsg << endl;
            //为什么这里要warn，因为发不了
            /* LogWarn("WEBPAGEQUERY : sendMsg : %s\n",sendMsg.c_str()); */
            int length = sendMsg.size();
            int ID =200;
            char buf[10]={0};
            memcpy(buf,&length,sizeof(length));
            memcpy(buf+4,&ID,sizeof(ID));
            std::copy(buf,buf+8,std::back_inserter(processedMsg));
            processedMsg.append(sendMsg);
            }
            break;
        default:
            std::cerr<<"client send msg is wrong" << endl;
            return;
        }

        //消息发送
        cout << "sendInloop" << endl;
        _conn->sendInLoop(processedMsg);
    }
private:
    string _msg;
    TcpConnectionPtr _conn;
};

//构造函数
SearchEngineServer::SearchEngineServer(const string&ip,unsigned short port)
:_pool(4,10)
,_tcpServer(ip,port)
{
    
}
//析构函数
SearchEngineServer::~SearchEngineServer(){

}

//启动服务器
void SearchEngineServer::start(){
    //先启动线程池 让slave线程阻塞 master线程继续执行
    //让读写线程阻塞 IO线程继续执行
    _pool.start();
    LogDebug("threadpool start\n");
    
    //设置三个半事件 = 注册三个回调函数
    //为什么注册回调函数叫做设置半个事件
    _tcpServer.setAllCallback(std::bind(&SearchEngineServer::onConnection,this,std::placeholders::_1)
    ,std::bind(&SearchEngineServer::onMessage,this,std::placeholders::_1)
    ,std::bind(&SearchEngineServer::onClose,this,std::placeholders::_1)
    ); //因为是方法所以要传个对象的地址(this),
    
    //因为形参类型为TcpConnectionCallback = std::function<void(const TcpConnectionPtr&)>
    //方法的形参为2个 ，使用this指针绑定了第一个形参，将方法的形态改成了一个形参,还需要占位符再占一个
    //占位符的数值表示实参的位置
    LogDebug("TcpServer begin\n");
    _tcpServer.start();
}

//关闭服务器
void SearchEngineServer::stop(){
    //回收slave线程
    //回收读写线程
    _pool.stop();
    //终止tcpServer服务器
    _tcpServer.stop();
}

//三个回调函数
//连接建立事件 被注册给TcpServer使用 
void SearchEngineServer::onConnection(const TcpConnectionPtr &conn){
    std::cout << conn->toString() << " has connected!" << std::endl;
}

//消息到达事件以及消息发送完毕半个事件 被注册给TcpServer使用  
void SearchEngineServer::onMessage(const TcpConnectionPtr &conn){
    string msg = conn->receive();//接收客户端的数据
    LogInfo(">>recv msg from client :\nlength = %d\nID = %d\nbuf = %s\n"
    ,*(int*)&*msg.begin(),  //迭代器返回的不是指针，而是元素本身，不能
                            //直接解引用，要通过取地址在解引用实现读取
    *(int*)&*(msg.begin()+4),
    (char*)&*(msg.begin()+8));

    /* cout << "what happened 149?" << endl; */
    //接收到客户端的msg之后，是可以进行业务逻辑的处理
    MyTask task(msg, conn);
    //添加了Task，添加到了线程池里面去了,执行了_taskQue的push
    _pool.addTask(std::bind(&MyTask::process, task));
    /* cout << "what happened 153?" << endl; */
}

//连接断开事件 被注册给TcpServer使用
void SearchEngineServer::onClose(const TcpConnectionPtr &conn){
    std::cout << conn->toString() << " has closed!" << std::endl;
}
