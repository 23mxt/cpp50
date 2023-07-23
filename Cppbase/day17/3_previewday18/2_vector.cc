#include <string.h>
#include <vector>
#include <deque>
#include <list>
#include <iostream>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::deque;
using std::list;

void test()
{
    //直接初始化为空
    /* vector<int> numbers; */
    /* deque<int> numbers; */
    /* list<int> numbers; */
    
    //初始化多个数据
    //默认初始化为0
    vector<int> numbers(10, 2);
    /* deque<int> numbers(10); */
    /* list<int> numbers(10, 2); */

    /* for(auto &elem : numbers) */
    /* { */
    /*     cout << "elem = " << elem << endl; */
    /* } */

    vector<int>::iterator it = numbers.begin();
    for(it = numbers.begin(); it != numbers.end(); ++it)
    {
        cout << "numbers elem = " << *it << endl;
    }

    &numbers;//error,只是获取对象栈上的地址，也就是_M_start的地址

}

int main() {
    test();
    return 0;
}

