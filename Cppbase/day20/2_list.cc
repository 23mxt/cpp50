#include <iostream>
#include <list>

using std::cout;
using std::endl;
using std::list;

template <typename Container>
void display(const Container &con)
{
    for(auto &elem : con)
    {
        cout << elem << "  ";
    }
    cout << endl;
}

template <typename T>
struct CompareList
{
    bool operator()(const T &lhs, const T&rhs) const
    {
        cout << "bool CompareList::operator()" << endl;
        return lhs < rhs;
    }
};

void test()
{
    list<int> number = {1, 3, 9, 8, 4, 6, 8, 2};
    list<int> number2 = {11, 33, 66, 7};
    display(number);
    display(number2);

    cout << endl;
    auto it = number.begin();
    ++it;
    number.splice(it, number2);
    display(number);
    display(number2);
#if  1
    cout << endl;
    list<int> number3 = {100, 300, 600, 700, 500};
    it = number.begin();
    ++it;
    cout << "*it = " << *it << endl;
    auto it2 = number3.end();
    --it2;
    cout << "*it2 = " << *it2 << endl;
    number.splice(it, number3, it2);
    display(number);
    display(number3);
#endif
#if 1
    cout << endl;
    it2 = number3.begin();
    auto it3 = number3.end();
    --it3;
    cout << "*it2 = " << *it2 << endl;
    cout << "*it3 = " << *it3 << endl;
    number.splice(it, number3, it2, it3);
    display(number);
    display(number3);
    //splice转移区间是左闭右开
#endif
#if 1
    cout << endl << endl;
    auto it4 = number.begin();
    ++it4;
    ++it4;
    cout << "*it4 = " << *it4 << endl;
    auto it5 = number.end();
    --it5;
    --it5;
    cout << "*it5 = " << *it5 << endl;
    number.splice(it4, number, it5);
    display(number);
#endif

    cout << endl << endl;
    cout << "移动交叉区间的元素" << endl;
    it = number.begin();
    ++it;
    ++it;
    it2 = number.begin();
    it5 = number.end();
    number.splice(it, number, it2, it5);
    display(number);
}

int main(int argc, char *argv[])
{
    test();
    return 0;
}


