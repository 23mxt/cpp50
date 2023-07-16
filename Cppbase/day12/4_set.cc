#include <iostream>
#include <set>
#include <vector>
#include <utility>

using std::cout;
using std::endl;
using std::set;
using std::vector;
using std::pair;

void test()
{
    //set的特征
    //1、元素是唯一的，不能重复
    //2、默认会按照key值进行升序排列（从小到大排序）
    //set<int> number;//无参对象
    set<int> number = {1, 3, 6, 9, 7, 5, 2, 3, 3};

    //迭代器（看成是指针，广义的指针）
    //迭代器具备指针的功能，但是不能完全等价与指针
    set<int>::iterator it;
    for(it = number.begin(); it != number.end(); ++it)
    {
        cout << *it << "  ";
    }
    cout << endl;

    cout << endl << "set的查找操作" << endl;
    size_t cnt1 = number.count(7);
    size_t cnt2 = number.count(10);
    cout << "cnt1 = " << cnt1 << endl;
    cout << "cnt2 = " << cnt2 << endl;

    cout << endl;
    set<int>::iterator it2 = number.find(6);
    if(it2 == number.end())//判断迭代器为空的方法
    {
        cout << "该元素不存在set中" << endl;
    }
    else
    {
        cout << "该元素存在set中 " << *it2 << endl;
    }

    cout << endl << "set的插入操作" << endl;
    pair<set<int>::iterator, bool> ret = number.insert(8);
    if(ret.second)
    {
        cout << "插入成功了 " << *ret.first << endl;
    }
    else
    {
        cout << "插入失败，该元素存在set中" << endl;
    }

    vector<int> vec = {1, 3, 7, 11, 19, 4, 2, 3};
    number.insert(vec.begin(), vec.end());
    for(auto &elemn : number)
    {
        cout << elemn << "  ";
    }
    cout << endl;

    cout << endl << "set的删除" << endl;
    it = number.end();
    --it;
    number.erase(it);
    for(auto &elem : number)
    {
        cout << elem << "  ";
    }
    cout << endl;

    /* cout << "number[1] = " << number[1] << endl;//error */

    cout << endl;
    it = number.begin();
    cout << "*it = " << *it << endl;
    /* *it = 100;//error */
}

int main(int argc, char **argv)
{
    test();
    return 0;
}


