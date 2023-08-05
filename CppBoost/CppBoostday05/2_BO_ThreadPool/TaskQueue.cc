#include "TaskQueue.h"

TaskQueue::TaskQueue(size_t queSize)
    : _queSize(queSize)
    , _que()
    , _mutex()
    , _notEmpty(_mutex)
    , _notFull(_mutex)
      ,_flag(true)    //当消费者已经做完所有任务时，把flag设为法拉瑟，并唤醒所有工作线程
{

}

TaskQueue::~TaskQueue()
{

}

//向任务队列中存数据
void TaskQueue::push(const ElemType &ptask)
{
    //锁使用不当会出现死锁的问题，
    //所以可以使用RAII的思想
    //1、先上锁
    /* _mutex.lock(); */
    MutexLockGuard autoLock(_mutex);//autoLock是栈对象

    //2、如果任务队列是满的，生产者就不能生产数据
    /* if(full()) */
    while(full())
    {
        _notFull.wait();//生产者就睡眠
    }

    //3、生产数据
    _que.push(ptask);

    //4、唤醒消费者
    _notEmpty.notify();

    //5、最后解锁
    /* _mutex.unLock(); */

}
//从任务队列中取数据
ElemType TaskQueue::pop()
{
    //1、先上锁
    /* _mutex.lock(); */
    MutexLockGuard autoLock(_mutex);//autoLock是栈对象

    //2、如果任务队列是空的，那么消费者就需要睡眠
    //若事件不空或_flag为false，均应跳出循环
    while(empty() && _flag)
    {
        _notEmpty.wait();
    }

    if(_flag)
    {
        //3、获取数据
        ElemType tmp = _que.front();
        _que.pop();

        //4、发通知
        _notFull.notify();

        //5、最后解锁
        /* _mutex.unLock(); */
        return tmp;
    }
    else
    {
        return nullptr;
    }
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

void TaskQueue::wakeup() 
{
    _flag = false;
    _notEmpty.notifyAll();
}
