#include "Producer.h"
#include "Consumer.h"
#include "TaskQueue.h"
#include "Thread.h"
#include <string>
#include <iostream>
#include <memory>

using std::cout;
using std::endl;
using std::unique_ptr;//RAII

void test()
{
    //创建一个任务队列，并初始化任务队列的容量。判满用
    TaskQueue myQueue(5);

    //在堆上创建生产者和消费者,传入引用类型的任务队列进行初始化
    /* Producer *myProducer = new Producer(myQueue); */
    /* Consumer *myConsumer = new Consumer(myQueue); */
    unique_ptr<Thread> myProducer(new Producer(myQueue));
    unique_ptr<Thread> myConsumer(new Consumer(myQueue));

    //开始生产者和消费者进程
    myProducer->start();
    myConsumer->start();
    
    //等待生产者和消费者进程结束
    myProducer->join();
    myConsumer->join();
      
    //delete生产者和消费者
    /* delete myProducer; */
    /* delete myConsumer; */
}

int main() 
{
    test();
    return 0;
}

