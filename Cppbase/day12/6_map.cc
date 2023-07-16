#include <iostream>
#include <map>
#include <string>
#include <utility>

using std::cout;
using std::endl;
using std::map;
using std::string;
using std::pair;
using std::make_pair;

void test()
{
    //map的特征
    //1、会按照key-value的键值对形式进行存储，key值是唯一的，
    //不能重复,但是value值可以相同也可以不同
    //2、默认会按照key值进行升序排序（从小到大排序）
    map<int, string> number = {
        {1, "hello"},
        {2, "wangdao"},
        pair<int, string>(5, "hello"),
        pair<int, string>(3, "wuhan"),
        make_pair(4, "hubei"),
        make_pair(2, "hubei"),
        make_pair(5, "hello"),
    };

    //迭代器
    map<int, string>::iterator it;
    for(it = number.begin(); it != number.end(); ++it)
    {
        cout << it->first << "  " << it->second << endl;
    }

    cout << endl << "map的查找操作" << endl;
    size_t cnt1 = number.count(5);//  1
    size_t cnt2 = number.count(10);// 0
    cout << "cnt1 = " << cnt1 << endl;
    cout << "cnt2 = " << cnt2 << endl;

    cout << endl;
    /* map<int, string>::iterator it2 = number.find(6); */
    map<int, string>::iterator it2 = number.find(2);
    if(it2 == number.end())//判断迭代器为空的方法
    {
        cout << "该元素不存在map中" << endl;
    }
    else
    {
        cout << "该元素存在map中 "
              << it2->first << "  "
              << it2->second << endl;
    }

    cout << endl << "map的插入操作"<< endl;
    /* pair<map<int, string>::iterator, bool> ret = */
    /*     number.insert({6, "beijing"}); */
    /* auto ret = number.insert({6, "beijing"}); */
    /* auto ret = number.insert(pair<int, string>(6, "beijing")); */
    auto ret = number.insert(make_pair(6, "beijing"));
    if(ret.second)
    {
        cout << "插入成功 " << ret.first->first << "   "
             << ret.first->second << endl;
    }
    else
    {
        cout << "插入失败，该元素存在map中" << endl;
    }

    cout << endl << "map的下标访问" << endl;
    cout << "number[1] = " << number[1] << endl;//查找
    cout << "number[10] = " << number[10] << endl;//插入

    cout << endl << endl;
    for(auto &elemnts : number)//elemnts表示任意元素，叫什么名字都可以
    {
        cout << elemnts.first << "   " << elemnts.second << endl;
    }

    number[10] = "hello";//修改
    /* number[5] = "wangdao";//修改 */
    number.operator[](5).operator=("wangdao");
    //T &operator[](const key &key)

    cout << endl << endl;
    for(auto &elem : number)
    {
        cout << elem.first << "   " << elem.second << endl;
    }

    /* const map<int, string> number2 = {{1,"hello"}}; *///取下标意味着能修改，const表示不能修改，因此加了const的map不能取下标
    /* cout << "number2[1] = " << number2[1] << endl; */
}

int main(int argc, char **argv)
{
    test();
    return 0;
}


