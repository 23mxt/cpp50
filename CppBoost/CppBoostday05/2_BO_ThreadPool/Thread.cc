#include "Thread.h"
#include <stdio.h>

Thread::Thread(ThreadCallback &&cb)
: _thid(0)
, _isRunning(false)
,_cb(cb)
{

}

Thread::~Thread()
{
    pthread_detach(_thid);
}

//线程的开始与结束
//谁调用了start函数，那么this就指向谁
void Thread::start()
{
    //shift + k
    //threadFunc必须是静态成员函数，为了消除this的影响
    /* int ret = pthread_create(&_thid, nullptr, threadFunc, nullptr); */
    //this指针指向的是类外的new MyThread()对象
    int ret = pthread_create(&_thid, nullptr, threadFunc, this);
    if(ret)
    {
        //n + shift + k (n代表的是第几卷)
        perror("pthread_create");
        return;
    }

    _isRunning = true;
}

void Thread::stop()
{
    if(_isRunning)
    {
        int ret = pthread_join(_thid, nullptr);
        if(ret)
        {
            perror("pthread_join");
            return;
        }

        _isRunning = false;
    }
}

//线程入口函数
void *Thread::threadFunc(void *arg)
{
    //让线程执行对应的任务
    //pth1,pth,this都指向的是堆对象new MyThread()
    Thread *pth1 = static_cast<Thread *>(arg);
    if(pth1)
    {
        pth1->_cb();    //执行回调函数
    }
    else
    {
        printf("pth == nullptr\n");
    }

    /* return nullptr; */
    pthread_exit(nullptr);//线程退出函数
}

