/**
 * Project _PC
 */


#ifndef _TASKQUEUE_H
#define _TASKQUEUE_H

#include <queue>
#include "Conditional.h"
#include "Mutex.h"

using std::queue;

class TaskQueue 
{
public: 
    
/**
 * @param size
 */
TaskQueue(int size);
    
~TaskQueue();
    
/**
 * @param value
 */
void push(int value);
    
int pop();
    
bool isEmpty();
    
bool isFull();

private: 
    int _queueSize; //队列中的元素数量
    queue<int> _que;    //商品队列
    Mutex _mutex;       //互斥锁
    Conditional _notEmpty;  //消费者用到的条件变量.不空则被唤醒
    Conditional _notFull;   //生产者用到的条件变量。不满则被唤醒
};

#endif //_TASKQUEUE_H
