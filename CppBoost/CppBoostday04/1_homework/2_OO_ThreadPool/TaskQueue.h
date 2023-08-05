#ifndef __TASKQUEUE_H__
#define __TASKQUEUE_H__

#include "MutexLock.h"
#include "Condition.h"
#include "Task.h"
#include <queue>

using std::queue;

using ElemType = Task*;

class TaskQueue
{
public:
    TaskQueue(size_t queSize);
    ~TaskQueue();   //摆个架子

    //向任务队列中放任务
    void push(const ElemType &ptask);
    //从任务队列中取任务
    ElemType pop();

    //判断任务队列是空还是满
    bool empty() const;
    bool full() const;

    //关闭子线程前唤醒子线程
    void wakeup() ;

private:
    size_t _queSize;//任务队列的大小
    queue<ElemType> _que;//存放任务的数据结构
    MutexLock _mutex;//共享资源需要上锁 //mutex的销毁用到RAII
    Condition _notEmpty;//让消费者在该条件变量上排队    //condition的销毁？
    Condition _notFull;//让生产者在该条件变量上排队
    bool _flag;     //防止多线程睡眠无法退出
};

#endif
