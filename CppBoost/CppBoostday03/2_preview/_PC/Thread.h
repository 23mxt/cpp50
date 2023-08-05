#include <pthread.h>
#include <iostream>

/* using namespace::std; */
using std::cout;
using std::endl;
/**
 * Project _Thread
 */


#ifndef _THREAD_H
#define _THREAD_H

#include "Nocopyable.h"

class Thread 
:private Nocopyable
{
public: 
    
Thread();
    
~Thread();
    
void start();
    
void join();
    
virtual void run() = 0;

private: 
    pthread_t _thid;
    bool _isRunning;
    
//用static消除this指针影响
static void *threadFunc(void* arg);
};

#endif //_THREAD_H
