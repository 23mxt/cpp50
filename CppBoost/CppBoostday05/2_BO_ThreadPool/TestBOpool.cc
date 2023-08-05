#include "ThreadPool.h"
#include "Thread.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <memory>

using namespace std;

//先写一个普通类及其成员函数或一个普通函数
class MyTask
{
public:
    void process()
    {
        ::srand(clock());
        int num = rand()%100;
        cout << "BO_num = " << num << endl;
    }
};

void test()
{
    //用uniqueptr获取该成员函数的智能指针，用bind改变函数的形态
    unique_ptr<MyTask> ptask(new MyTask());
    //创建线程池
    ThreadPool threadPool(4, 10);   //创建4个子线程，10个是任务队列的容量
    //开始线程池
    threadPool.start();
    
    //设置计数器
    int cnt = 20;
    //向任务队列中添加20个任务，计数器减为0才退出循环
    while(cnt--)
    {
        cout << "cnt = " << cnt << endl;
        threadPool.addTask(bind(&MyTask::process, ptask.get()));
    }
    
    //执行完任务后，关闭线程池
    threadPool.stop();
}

int main()
{
    test();
    return 0;
}
