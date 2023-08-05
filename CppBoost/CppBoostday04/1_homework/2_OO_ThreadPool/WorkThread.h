#ifndef _WORKTHREAD_H_
#define _WORKTHREAD_H_

#include "ThreadPool.h"
#include "Thread.h"

class WorkThread
:public Thread
{
public:
    WorkThread(ThreadPool &threadpool) 
    :_threadpool(threadpool)
    {}

    ~WorkThread() {}

    void run(); //WorkThread属于线程池的一部分，是线程池的工作单元，由线程池负责销毁 

private:
    //需要从线程池取任务
    ThreadPool &_threadpool;    
};

#endif 
