#include "WorkThread.h"
#include "ThreadPool.h"

WorkThread::WorkThread(ThreadPool &pool)
: _pool(pool)
{

}

WorkThread::~WorkThread()
{

}

void WorkThread::run()
{
    //线程池交给工作线程做的任务
    _pool.doTask();
}
