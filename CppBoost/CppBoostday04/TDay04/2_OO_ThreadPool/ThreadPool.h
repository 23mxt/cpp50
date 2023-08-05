#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

#include "TaskQueue.h"
#include "Task.h"
#include <vector>
#include <memory>

using std::vector;
using std::unique_ptr;

class Thread;

class ThreadPool
{
    friend class WorkThread;
public:
    ThreadPool(size_t threadNum, size_t queSize);
    ~ThreadPool();

    //线程池的开始与结束
    void start();
    void stop();

    //存储任务与获取任务
    void addTask(Task *ptask);
private:
    Task *getTask();
    //线程池交给工作线程执行的具体任务
    void doTask();

private:
    size_t _threadNum;//子线程的数目
    size_t _queSize;//任务队列的大小
    vector<unique_ptr<Thread>> _threads;//存放子线程的数据结构
    TaskQueue _taskQue;//任务队列
    bool _isExit;//表示线程池是否退出的标志

};

#endif
