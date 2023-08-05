#include "Consumer.h"
#include "TaskQueue.h"
#include <unistd.h>
#include <iostream>

using std::cout;
using std::endl;

Consumer::Consumer(TaskQueue &taskQue)
: _taskQue(taskQue)
{

}

Consumer::~Consumer()
{

}

void Consumer::run() 
{
    int cnt = 20;
    while(cnt--)
    {
        int number = _taskQue.pop();
        cout << "Consumer pop number = " << number << endl;
        sleep(1);
    }
}
