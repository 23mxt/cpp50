#include "MyThread.h"

using std::cout;
using std::endl;

void test()
{
    MyThread mthread;
    mthread.start();
    mthread.join();
    
}

int main() {
    test();
    return 0;
}

