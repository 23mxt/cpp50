#include "ThreadPool.h"
#include <unistd.h>
#include <functional>

using std::bind;

//开启所有线程
void ThreadPool::start()
{
    for(int i = 0; i < _threadNum; ++i)
    {
        //将所有线程以智能指针的形式加入vector
        //工作线程要绑定doTask,参数要传this
        unique_ptr<Thread> pthread(new Thread(bind(&ThreadPool::doTask, this)));  //  工作线程需要从线程池取任务
        _threads.push_back(std::move(pthread));    //vector 不能赋值或复制
    }

    //遍历vector，启动所有子线程，等待去任务做任务
    for(auto &pt : _threads)
    {
        //pt作为智能指针
        pt->start();
    }        

}

//等待所有线程任务做完进行关闭
void ThreadPool::stop()
{
    //确保任务都做完再设置标志位
    //这里对任务队列不加锁会有bug
    while(!_taskQueue.empty())
    {
        sleep(1);
    }
    
    //将标志位置为true
    _isExit = true;
    
    //唤醒所有在睡眠的线程
    _taskQueue.wakeup(); 
    //遍历vector,所有线程依次退出
    for(auto &pt : _threads)
    {
        pt->stop();
    }
}

//添加任务到任务队列
//传入的是bind出来的临时对象，要用右值引用
void ThreadPool::addTask(ElemType &&task)
{
   if(task)
   {
       _taskQueue.push(std::move(task));
   }
}

//从任务队列获取任务
ElemType ThreadPool::getTask()
{
    return _taskQueue.pop();
}

//做任务
void ThreadPool::doTask()
{
    //只要退出标志位不为true，子线程就不能退出
    //子线程只有在任务队列为空时才能睡
    //任务队列为空时？即pop时任务队列若没有元素，工作线程就会睡眠
    while(!_isExit)
    {   
        ElemType task = getTask();
        
        if(task)
        {
            task(); //执行回调函数
        }

    }
}
