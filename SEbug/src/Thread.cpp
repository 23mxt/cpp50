#include <stdio.h>
#include "../include/Thread.h"
namespace current_thread{
    __thread const char *name;
}
Thread::Thread(ThreadCallback&&cb,string name)
: _thid(0)
,_name(name)
, _isRunning(false)
,_cb(std::move(cb))
,_cache(1000)
{
    CacheManager* pInstance=CacheManager::createInstance();
    pInstance->_cachelist.push_back(&_cache);
}   
Thread::~Thread()
{

}

//线程运行与停止的函数
void Thread::start()
{
    //跳转的时候，可以使用n shift + k
    //threadFunc作为成员函数的时候，在第一个参数的位置会隐含一个
    //this指针，而pthread_create的第三个参数形态是固定的，所以
    //需要消除this的影响，就需要将threadFunc设置为静态
    /* int ret = pthread_create(&_thid, nullptr, threadFunc, nullptr); */
    int ret = pthread_create(&_thid, nullptr, threadFunc, this);
    if(ret)
    {
        perror("pthread_create");
        return;
    }

    _isRunning = true;
}

void Thread::join()
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
    /* arg->run();//error */
    Thread *pth = static_cast<Thread *>(arg);
    if(pth)
    {
        //执行任务
        current_thread::name = pth->_name.c_str();
        pth->_cb();
    }
    else
    {
        printf("hello\n");
    }

    pthread_exit(nullptr);
    /* return nullptr; */
}
