/**
 * Project _PC
 */


#include "Mutex.h"

/**
 * Mutex implementation
 */


//构造函数初始化锁
Mutex::Mutex() 
:_mutex()
{
    cout << "Mutex()" << endl;    
    int ret = pthread_mutex_init(&_mutex, nullptr);
    if(ret)
    {
        perror("pthread_mutex_init");
    }
}

//析构函数销毁锁
Mutex::~Mutex() 
{
    cout << "~Mutex()" << endl;
    int ret = pthread_mutex_destroy(&_mutex);
    if(ret)
    {
        perror("pthread_mutex_destroy");
    }
}

/**
 * @return void
 */
void Mutex::Mutexlock() 
{
    cout << "Mutexlock()" << endl; 
    int ret = pthread_mutex_lock(&_mutex);
    if(ret)
    {
        perror("pthread_mutex_lock");
    }
    return;
}

/**
 * @return void
 */
void Mutex::MutexTrylock() 
{
    cout << "MutexTrylock()" << endl;
    int ret = pthread_mutex_trylock(&_mutex);
    if(ret)
    {
        perror("pthread_mutex_trylock");
    }
    return;
}

/**
 * @return void
 */
void Mutex::MutexUnlock() 
{
    cout << "Mutexunlock()" << endl;
    int ret = pthread_mutex_unlock(&_mutex);
    if(ret)
    {
        perror("pthread_mutex_unlock");
    }
    return;
}

/**
 * @return void
 */
pthread_mutex_t *Mutex::getMutexptr()
{
    return &_mutex;
}
