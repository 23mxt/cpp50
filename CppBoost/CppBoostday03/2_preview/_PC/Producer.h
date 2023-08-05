/**
 * Project _PC
 */


#ifndef _PRODUCER_H
#define _PRODUCER_H

#include "Thread.h"
#include "TaskQueue.h"
#include <unistd.h>


class Producer: public Thread {
public: 
Producer(TaskQueue &taskqueue)
:_TaskQueue(taskqueue)
{
    cout << "Producer(TaskQueue &)" << endl;
}

~Producer(){}
void run();
private: 
    TaskQueue & _TaskQueue;
};

#endif //_PRODUCER_H
