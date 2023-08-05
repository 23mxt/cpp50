#include "WorkThread.h"

void WorkThread::run() 
{
    _threadpool.doTask();
}//WorkThread属于线程池的一部分，是线程池的工作单元，由线程池负责销毁 
                         
