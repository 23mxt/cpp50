/**
 * Project _Thread
 */


#include "Thread.h"

//静态成员变量初始化必须和头文件在一起，因为编译头文件时必须知道数据成员
//静态成员函数初始化可以放在实现文件
/**
 * Thread implementation
 */


Thread::Thread() 
:_thid(0)
,_isRunning(false)
{
    cout << "Thread()" << endl;
}

Thread::~Thread() 
{
    cout << "~Thread()" << endl;
}

/**
 * @return void
 */
void Thread::start() 
{
    pthread_create(&_thid, nullptr, threadFunc, this);
   _isRunning = true;
    
    return;
}

/**
 * @return void
 */
void Thread::join() 
{
    //有线程在运行，才会等待结束
    if(_isRunning == true)
    {
        pthread_join(_thid, nullptr);
    }

    return;
}

/**
 * @return void
 */

/**
 * @return void
 */
void* Thread::threadFunc(void *arg) 
{
    Thread* pth = static_cast<Thread*>(arg);
    //pth不为空才会进行线程的执行
    if(pth != nullptr)
    {
        //这里实现生产者和消费者的多态
        pth->run();
    }
    return nullptr;
}
