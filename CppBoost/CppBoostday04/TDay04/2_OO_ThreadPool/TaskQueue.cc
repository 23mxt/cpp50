#include "TaskQueue.h"

TaskQueue::TaskQueue(size_t queSize)
: _queSize(queSize)
, _que()
, _mutex()
, _notEmpty(_mutex)
, _notFull(_mutex)
, _flag(true)
{

}

TaskQueue::~TaskQueue()
{

}

//向任务队列中存数据
void TaskQueue::push(ElemType ptask)
{
    MutexLockGuard autoLock(_mutex);//autoLock是栈对象

    while(full())
    {
        _notFull.wait();//生产者就睡眠
    }

    _que.push(ptask);

    _notEmpty.notify();
}

//从任务队列中取数据
ElemType TaskQueue::pop()
{
    MutexLockGuard autoLock(_mutex);//autoLock是栈对象

    while(empty() && _flag)
    {
        _notEmpty.wait();
    }

    if(_flag)
    {
        ElemType ptask = _que.front();
        _que.pop();

        _notFull.notify();

        return ptask;
    }
    else
    {
        return nullptr;
    }
}

void TaskQueue::wakeup()
{
    _flag = false;
    _notEmpty.notifyAll();
}

//判断任务队列是空还是满
bool TaskQueue::empty() const
{
    return  0 == _que.size() ;
}

bool TaskQueue::full() const
{
    return _que.size() == _queSize;
}
