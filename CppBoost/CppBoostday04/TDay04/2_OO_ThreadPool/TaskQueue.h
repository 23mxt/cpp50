#ifndef __TASKQUEUE_H__
#define  __TASKQUEUE_H__

#include "MutexLock.h"
#include "Condition.h"
#include "Task.h"
#include <queue>

using std::queue;

using ElemType = Task *;

class TaskQueue
{
public:
    TaskQueue(size_t queSize);
    ~TaskQueue();

    //向任务队列中存数据
    void push(ElemType ptask);
    //从任务队列中取数据
    ElemType pop();

    //唤醒所有等待在条件变量_notEmpty
    //上的线程
    void wakeup();

    //判断任务队列是空还是满
    bool empty() const;
    bool full() const;

private:
    size_t _queSize;//任务队列的大小
    queue<ElemType> _que;//存放数据的数据结构
    MutexLock _mutex;//共享资源需要上锁
    Condition _notEmpty;//让消费者在该条件变量上排队
    Condition _notFull;//让生产者在该条件变量上排队
    bool _flag;//标志位

};

#endif
