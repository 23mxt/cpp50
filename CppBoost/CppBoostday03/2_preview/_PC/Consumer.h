/**
 * Project _PC
 */


#ifndef _CONSUMER_H
#define _CONSUMER_H

#include "Thread.h"
#include "TaskQueue.h"
#include <unistd.h>


class Consumer: public Thread {
public: 
Consumer(TaskQueue &taskqueue)
:_TaskQueue(taskqueue)
{}

~Consumer(){}
void run();
    
private: 
    TaskQueue & _TaskQueue;
};

#endif //_CONSUMER_H
