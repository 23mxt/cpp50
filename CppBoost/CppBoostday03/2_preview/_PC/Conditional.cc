/**
 * Project _PC
 */


#include "Conditional.h"

/**
 * Conditional implementation
 */


//引用成员在初始化时确定
Conditional::Conditional(Mutex &mutex)
:_mutex(mutex)
{
    cout << "Conditional(Mutex) " << endl;
    pthread_cond_init(&_cond, nullptr);
    
}

Conditional::~Conditional() 
{
    cout << "~Conditional() " << endl;
    pthread_cond_destroy(&_cond);
}

/**
 * @return void
 */
void Conditional::join() 
{
    cout << "Conditional::join() " << endl;
    //Mutex的数据成员是私有的，需要通过接口实现数据成员取地址
    int ret = pthread_cond_wait(&_cond, _mutex.getMutexptr());
    if(ret)
    {
        perror("pthread_cond_wait");
    }
    return;
}

/**
 * @return void
 */
void Conditional::notify() 
{
    cout << "Conditional::notify() " << endl;
    int ret = pthread_cond_signal(&_cond);
    if(ret)
    {
        perror("pthread_cond_signal");
    }
    return;
}

/**
 * @return void
 */
void Conditional::notifyall() 
{
    cout << "Conditional::notifyall() " << endl;
    int ret = pthread_cond_broadcast(&_cond);
    if(ret)
    {
        perror("pthread_cond_broadcast");
    }
    return;
}
