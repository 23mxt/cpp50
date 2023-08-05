/**
 * Project _PC
 */


#include "TaskQueue.h"

/**
 * TaskQueue implementation
 */


/**
 * @param size
 */
//任务队列 ---》生产者模型 ----》消费者模型 //Linux
//初始化队列有多少商品
TaskQueue::TaskQueue(int size) 
:_queueSize(size)
,_mutex()   //任务队列负责局部的生产和销毁
,_notEmpty(_mutex)  //初始化顺序应与声明顺序保持一致
,_notFull(_mutex)
{
        cout << "TaskQueue(int)" << endl;
}


TaskQueue::~TaskQueue() 
{
    cout << "~TaskQueue()" << endl;
}

/**
 * @param value
 * @return void
 */
void TaskQueue::push(int value) 
{
    //对共享资源的访问，必须加锁
    _mutex.Mutexlock();
    
    //若商品队列已满，则等待消费者消费
    while(isFull())
    {
        //用while防止多线程虚假唤醒
        _notFull.join();    
        //商品队列不满，则生产者被唤醒
    }
    //压入自定义的数字，方便测试
     _que.push(value);

     //唤醒消费者
     _notEmpty.notify();
     //何时all?

    //结束对共享资源的访问，解锁
    _mutex.MutexUnlock();
    return;
}

/**
 * @return void
 */
int TaskQueue::pop() 
{
    //对共享资源的访问，必须加锁
    _mutex.Mutexlock();
    
    //若商品队列为空，则等待生产者生产
    while(isEmpty())
    {
        _notEmpty.join();
    }
    //商品队列不为空，则消费者消费
    //先保存消费的数据
    int tmp = _que.front();   //获取队头元素
    
    //出队
    _que.pop();

    //唤醒生产者
    _notFull.notify();

    //结束对共享资源的访问，解锁
    _mutex.MutexUnlock();
    
    //返回消费的数据
    return tmp;
}

/**
 * @return bool
 */
bool TaskQueue::isEmpty() 
{
    //对共享资源的访问，必须加锁
    _mutex.Mutexlock();
    
    if(_que.empty())
    {
    //消费者不能再消费
        return true;
    }
    
    //结束对共享资源的访问，解锁
    _mutex.MutexUnlock();
    return false;
}

/**
 * @return bool
 */
bool TaskQueue::isFull() 
{
    //对共享资源的访问，必须加锁
    _mutex.Mutexlock();

    if(_que.size() == _queueSize)
    {
    //生产者不能再生产
        return true;
    }
    
    //结束对共享资源的访问，解锁
    _mutex.MutexUnlock();
    return false;
}
