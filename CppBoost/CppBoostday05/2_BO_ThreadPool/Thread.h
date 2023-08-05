#ifndef __THREAD_H__
#define __THREAD_H__

#include "Nocopyable.h"
#include <pthread.h>
#include <functional>

using std::function;

using ThreadCallback =  function<void()>; 

class Thread
:public Nocopyable
{
public:
    Thread(ThreadCallback &&cb);
    ~Thread();

    //线程的开始与结束
    void start();
    void stop();

private:
    //线程入口函数
    static void *threadFunc(void *arg);
private:
    pthread_t _thid;//线程id
    bool _isRunning;//标识线程是否在运行
    ThreadCallback _cb; //注册回调函数
};

#endif
