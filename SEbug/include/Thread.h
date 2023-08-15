#ifndef __THREAD_H__
#define __THREAD_H__

#include "NonCopyable.h"
#include <pthread.h>
#include<functional>
#include<unistd.h>
#include<string>
#include "CacheManager.hpp"
using std::string;
namespace current_thread{
    extern __thread const char* name;
}
class Thread
: NonCopyable
{
    using ThreadCallback = std::function<void()>;
public:
    Thread(ThreadCallback&&cb,string name);
    ~Thread();

    //线程运行与停止的函数
    void start();
    void join();

private:
    //线程入口函数
    static void *threadFunc(void *arg);
    //线程执行的任务
private:
    pthread_t _thid;//线程id
    string _name;//线程名字
    bool _isRunning;//标识线程是否在运行
    ThreadCallback _cb;
    LRUCache _cache;
};

#endif