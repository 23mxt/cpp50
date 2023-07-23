#include <string.h>
#include <vector>
#include <iostream>
using std::cout;
using std::endl;
using std::string;
using std::vector;

void display(vector<int> &rhs)
{
    for(auto &elem : rhs)
    {
        cout << elem << " ";
    }
    cout << endl;
}


void test()
{
    //1、创建无参对象
    vector<int> numbers;
    display(numbers);

    //2、count个value的相同元素
    /* vector<int> numbers(10, 2); */
    /* display(numbers); */

    //3、初始化迭代器范围的元素
    //左闭右开区间
    int arr[5] = {1,3,5,2,5};
    vector<int> numbers2(arr, arr + 5);
    display(numbers2);

    //4、拷贝构造函数（移动构造）
    vector<int> numbers3(numbers2);
    display(numbers3);

    //5、{}
    vector<int> numbers4{2, 4, 6, 8, 0};
    display(numbers4);
}

int main() {
    test();
    return 0;
}

