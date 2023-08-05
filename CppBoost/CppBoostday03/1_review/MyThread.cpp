/**
 * Project _Thread
 */


#include "MyThread.h"

/**
 * MyThread implementation
 */


/**
 * @return void
 */
void MyThread::run() 
{
    while(true)
    {
        cout << "MyThread is running" << endl;
        sleep(1);
    }

    return;
}
