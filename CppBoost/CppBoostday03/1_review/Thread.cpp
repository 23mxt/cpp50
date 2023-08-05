/**
 * Project _Thread
 */


#include "Thread.h"

/**
 * Thread implementation
 */


Thread::Thread() 
:_thid(0)
,_isRunning(false)
{
    cout << "Thread()" << endl;
}

Thread::~Thread() {
    cout << "~Thread()" << endl;
}

/**
 * @return void
 */
void Thread::start() 
{
    _isRunning = true;
    pthread_create(&_thid, nullptr, threadFunc, this);
    
    return;
}

/**
 * @return void
 */
void Thread::join() 
{
    pthread_join(_thid, nullptr);
    return;
}

/**
 * @return void
 */

/**
 * @return void
 */
void* Thread::threadFunc(void *arg) 
{
    Thread* pth = static_cast<Thread*>(arg);
    pth->run();
    return nullptr;
}
