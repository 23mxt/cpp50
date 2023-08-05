#include "ThreadPool.h"
#include "WorkThread.h"
#include <unistd.h>

ThreadPool::ThreadPool(size_t threadNum, size_t queSize)
: _threadNum(threadNum)
, _queSize(queSize)
, _taskQue(_queSize)
, _isExit(false)
{
    //预留空间，避免频繁扩容
    _threads.reserve(_threadNum);
}

ThreadPool::~ThreadPool()
{

}

//线程池的开始与结束
void ThreadPool::start()
{
    //1、需要将工作线程创建出来
    for(size_t idx = 0; idx < _threadNum; ++idx)
    {
        unique_ptr<Thread> up(new WorkThread(*this));
        _threads.push_back(std::move(up));//unique_ptr不能复制或者赋值
    }
    //2、让工作线程运行起来
    for(auto &th : _threads)
    {
        //让工作线程运行起来，等待着去获取并且执行“任务”
        th->start();
    }
}

void ThreadPool::stop()
{
    //需要判断任务队列中的任务是不是执行完毕，
    //如果没有执行完毕，就不能让线程池退出
    while(!_taskQue.empty())
    {
        sleep(1);
    }
    //线程池退出的标志位设置true
    _isExit = true;

    //将所有等待在_notEmpty条件变量上的
    //线程全部唤醒，从而进行回收退出
    _taskQue.wakeup();

    //让工作线程停止
    for(auto &th : _threads)
    {
        th->stop();
    }
}

//存储任务与获取任务
void ThreadPool::addTask(Task *ptask)
{
    if(ptask)
    {
        _taskQue.push(ptask);
    }
}

Task* ThreadPool::getTask()
{
    return _taskQue.pop();
}

//线程池交给工作线程执行的具体任务
void ThreadPool::doTask()
{
    //线程池之所有不能退出，是因为不能保证_isExit
    //被设置为true在while循环之前。
    //如果线程池中的子线程在获取任务，也就是执行
    //getTask之后，然后执行任务process，如果process
    //执行的速度非常慢，那么就有足够的时间将_isExit
    //设置为true，那么就不会再进入到while循环中。
    //但是如果process执行的速率非常快，还没有来得及
    //将_isExit设置为true，就已经进入到while循环中
    //执行getTask,而现在任务队列是空的,所以就会执行
    //TaskQueue中的pop，而该函数中，如果任务队列是
    //空的，那么工作线程就会睡眠
    while(!_isExit)
    {
        Task *ptask = getTask();
        if(ptask)
        {
            ptask->process();//体现多态
        }
    }
}

