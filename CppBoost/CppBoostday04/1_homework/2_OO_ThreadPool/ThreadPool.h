#ifndef _THREADPOLL_H__
#define _THREADPOLL_H__

#include "Task.h"
#include "Thread.h"
#include "TaskQueue.h"
#include <stdio.h>
#include <memory>
#include <vector>

using namespace std;

using std::vector;

class ThreadPool
{
    friend class WorkThread;
public:

    ThreadPool(size_t threadNum, size_t queueSize) 
    :_threadNum(threadNum)
    ,_queueSize(queueSize)  //可能queueSize不用再设置，可以优化
    ,_taskQueue(_queueSize)
    ,_isExit(false) //初始化退出标志位为false,这样线程做任务时可以进入while循环
    {
        //给线程预留空间
        _threads.reserve(threadNum);
    }

    ~ThreadPool() {}    //摆个架子

    //开启所有线程
    void start();
    //等待所有线程任务做完进行关闭
    void stop();

    //添加任务到任务队列
    void addTask(Task* ptask);

    //从任务队列获取任务
    Task *getTask();

    //做任务
    void doTask();

private:
    size_t _threadNum;   //线程的数量
    size_t _queueSize;   //任务队列的容量，用来爬满
    TaskQueue _taskQueue;   //任务队列
    //线程队列,初始化可以预留线程数量的空间，防止vector扩容导致的问题
    vector<unique_ptr<Thread>> _threads; 
    //当任务做完时，即任务队列为空时，可以设置退出标志位为true
    bool _isExit;
};

#endif
