/**
 * Project _Thread
 */


#ifndef _MYTHREAD_H
#define _MYTHREAD_H

#include "Thread.h"
#include <unistd.h>
//sleep头文件

class MyThread: public Thread {
public: 
    
void run();
};

#endif //_MYTHREAD_H
