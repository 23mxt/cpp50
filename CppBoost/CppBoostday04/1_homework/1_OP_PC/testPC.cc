#include "TaskQueue.h"
#include "Thread.h"
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <memory>
#include <functional>

using std::unique_ptr;
using std::bind;
using std::cout;
using std::endl;


class myProducer
{
public:
    void run(TaskQueue &taskQue)
    {
        ::srand(::clock());
        int cnt = 20;
        while(cnt--)
        {
            int number = rand()%100;
            taskQue.push(number);
            cout << "Producer push number = " << number << endl;
            sleep(1);
        }
    }
};

class myConsumer 
{
public:
    void run(TaskQueue &taskQue) 
    {
        int cnt = 20;
        while(cnt--)
        {
            int number = taskQue.pop();
            cout << "Consumer pop number = " << number << endl;
            sleep(1);
        }
    }
};

void func()
{

}
void test()
{
    TaskQueue taskQue(10);
    myProducer p1;
    myConsumer c1;

    //bind 绑定引用的参数时，必须要使用引用包装器
    Thread tP(std::bind(&myProducer::run,&p1, std::ref(taskQue)));
    Thread tC(std::bind(&myConsumer::run,&c1, std::ref(taskQue)));

    tP.start();
    tC.start();

    tP.stop();
    tC.stop();
}

int main(int argc, char *argv[])
{
    test();
    return 0;
}

