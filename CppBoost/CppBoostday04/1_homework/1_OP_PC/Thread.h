#ifndef __THREAD_H__
#define __THREAD_H__

#include "Noncopyable.h"
#include <pthread.h>
#include <functional>

using std::function;


using threadCallback = function<void()> ;
class Thread
{
    //声明回调函数
    /* typedef function<void()> threadCallback; */
public:
    Thread(threadCallback &&cb);
    ~Thread();

    //线程的开始与结束
    void start();
    void stop();

private:
    //线程入口函数
    static void *threadFunc(void *arg);
    //线程需要执行的任务的接口

private:
    pthread_t _thid;//线程id
    bool _isRunning;//标识线程是否在运行
    threadCallback _cb;
};

#endif
