#include <iostream>
#include <queue>
#include <vector>

using std::cout;
using std::endl;
using std::priority_queue;
using std::vector;

void test()
{

    //优先级队列底层使用的是堆排序（默认情况是一个大根/顶堆）
    //原理：当插入元素的时候，会将堆顶与新插入的元素进行比较，如果
    //堆顶比新插入的元素要小，也就是满足std::less,那就新插入的元素
    //会成为新的堆顶；如果堆顶比新插入的元素要大，不满足std::less
    //就不会用新的元素作为堆顶，上一次堆顶依旧是本次堆顶
    vector<int> vec = {1, 3, 6, 7, 9, 5, 3, 2};
    /* priority_queue<int> pque(vec.begin(), vec.end()); */
    priority_queue<int> pque;
    /* priority_queue<int, std::vector<int>, std::greater<int>> pque; */
    /* priority_queue<int, std::deque<int>, std::greater<int>> pque; */

    for(size_t idx = 0; idx != vec.size(); ++idx)
    {
        pque.push(vec[idx]);
        cout << "优先级最高的元素 : " << pque.top() << endl;
    }

    //遍历的方法
    while(!pque.empty())
    {
        cout << pque.top() << "  ";
        pque.pop();
    }
    cout << endl;
}

int main(int argc, char *argv[])
{
    test();
    return 0;
}


