/**
 * Project _PC
 */


#ifndef _MUTEX_H
#define _MUTEX_H

#include <pthread.h>
#include <iostream>
#include "Nocopyable.h"

using std::cout;
using std::endl;

class Mutex 
:private Nocopyable
{
public: 
    
Mutex();
    
~Mutex();
    
void Mutexlock();
    
void MutexTrylock();
    
void MutexUnlock();
    
//如果想要pthread_cond_wait取到_mutex的地址，就必须加一个获取地址的函数
pthread_mutex_t *getMutexptr();

private: 
    pthread_mutex_t _mutex;
};

#endif //_MUTEX_H
