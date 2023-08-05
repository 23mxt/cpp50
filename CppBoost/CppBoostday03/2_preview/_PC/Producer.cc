/**
 * Project _PC
 */


#include "Producer.h"


/**
 * Producer implementation
 */


/**
 * @return void
 */
void Producer::run() 
{
    int i = 0;
    int data = 100;
    while(i <= 5)
    {
        _TaskQueue.push(data);
        cout << "Producer put " << data << endl;
        sleep(1);
        data += 100;
        i += 1;
    }
    return;
}
