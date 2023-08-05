#include "ThreadPool.h"
#include "Task.h"
#include <stdlib.h>
#include <time.h>
#include <memory>
#include <iostream>

using namespace std;

class MyTask
:public Task 
{
public:

    virtual void process() 
    {
        ::srand(clock());
        
        int num = rand()%100;
        cout << "num is  " << num << endl;
    }

};

void test()
{
    //创建一个智能指针型的ptask
    unique_ptr<Task> ptask(new MyTask());
    //初始化一个线程池
    ThreadPool threadPool(4, 10);   //创建4个子线程，10个是任务队列的容量
    //开始线程池
    threadPool.start();

    //写一个计数器，王任务队列添加20次任务
    int cnt = 20;
    //在循环内做任务，添加完20个任务，退出循环
    while(cnt--)
    {
        cout << "cnt = " << cnt << endl;
        threadPool.addTask(ptask.get());
    }
    
    //退出线程池
    threadPool.stop();
}

int main() {
    test();
    return 0;
}

