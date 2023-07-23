#include <iostream>
#include <set>
#include <vector>

using std::cout;
using std::endl;
using std::set;
using std::vector;

template <typename Container>
void display(const Container &con)
{
    for(auto &elem : con)
    {
        cout << elem << "  ";
    }
    cout << endl;
}

void test()
{
    //set的特征
    //1、存放的是key值，key值是唯一的，不能重复
    //2、默认会按照key值升序排列
    //3、底层使用的是红黑树的数据结构
    set<int> number = {1, 3, 5, 8, 6, 4, 2, 5, 9};
    /* set<int, std::greater<int>> number = {1, 3, 5, 8, 6, 4, 2, 5, 9}; */
    display(number);

    cout << endl << "set的查找操作" << endl;
    size_t cnt = number.count(5);
    cout << "cnt = " << cnt << endl;

    set<int>::iterator it = number.find(7);
    if(it != number.end())
    {
        cout << "该元素存在set中 ：" << *it << endl;
    }
    else
    {
        cout << "该元素不存在set中" << endl;
    }

    cout << endl << "set的insert操作"  << endl;
    std::pair<set<int>::iterator, bool> ret = number.insert(7);
    if(ret.second)
    {
        cout << "插入成功 " << *ret.first << endl;
    }
    else
    {
        cout << "插入失败，该元素存在set中"  << endl;
    }

    cout << endl;
    vector<int> vec = {19, 39, 48, 12, 8, 9};
    number.insert(vec.begin(), vec.end());
    display(number);

    cout << endl;
    number.insert({1, 10, 50, 13});
    display(number);

    cout << endl;
    //不支持下标
    /* cout << "number[1] = " << number[1] << endl; */

    cout << endl;
    it = number.begin();
    cout << "*it = " << *it << endl;
    /* *it = 300;//error,不支持修改，为了维持红黑树的稳定性 */
}

int main(int argc, char *argv[])
{
    test();
    return 0;
}


