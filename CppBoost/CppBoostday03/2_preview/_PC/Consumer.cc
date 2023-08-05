/**
 * Project _PC
 */


#include "Consumer.h"
/**
 * Consumer implementation
 */


/**
 * @return void
 */
void Consumer::run() 
{
    int i = 0;
    while(i <= 5)
    {
        int tmp = _TaskQueue.pop();
        cout << "Consumer put " << tmp << endl;
        sleep(2);
        i += 1;
    }

    return;
}

