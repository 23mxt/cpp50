#include "ThreadPool.h"
#include "Task.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <memory>

using std::cout;
using std::endl;
using std::unique_ptr;

class MyTask
: public Task
{
public:
    void process() override
    {
        //
        ::srand(::clock());
        int number = ::rand()%100;
        cout << "MyTask number = " << number << endl;
    }
};

void test()
{
    unique_ptr<Task> ptask(new MyTask());
    ThreadPool pool(4, 10);
    pool.start();

    int cnt = 20;
    while(cnt--)
    {
        cout << "cnt = " << cnt << endl;
        pool.addTask(ptask.get());
    }

    pool.stop();
}

int main(int argc, char *argv[])
{
    test();
    return 0;
}

