/**
 * Project _PC
 */


#ifndef _CONDITIONAL_H
#define _CONDITIONAL_H

#include "Mutex.h"
#include "Nocopyable.h"

class Conditional 
:private Nocopyable
{
public: 
    
//引用成员必须在构造函数初始化
Conditional(Mutex &mutex);
    
~Conditional();
    
void join();
    
void notify();
    
void notifyall();
private: 
    Mutex & _mutex;
    pthread_cond_t _cond;
};

#endif //_CONDITIONAL_H
