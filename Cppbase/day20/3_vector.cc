#include <iostream>
#include <vector>

using std::cout;
using std::endl;
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


template <typename Container>
void printContainerCapacity(const Container &con)
{
    cout << "con.size() = " << con.size() << endl;
    cout << "con.capacity() = " << con.capacity() << endl;
}

void test()
{
    vector<int> number = {1, 3, 5, 7, 9, 8, 6, 4, 2};
    display(number);
    printContainerCapacity(number);

    cout << endl << "在vector的尾部进行插入与删除" << endl;
    number.push_back(100);
    number.push_back(200);
    display(number);
    printContainerCapacity(number);

    cout << endl << "在vector的中间进行插入" << endl;
    auto it = number.begin();
    ++it;
    ++it;
    cout << "*it = " << *it << endl;
    number.insert(it, 888);
    display(number);
    cout << "*it = " << *it << endl;
    printContainerCapacity(number);

    //vector的insert扩容原理
    //将元素的个数size()= m, 容量的大小capacity() = n,
    //将待插入的元素的个数设置为t
    //1、当t < n - m,此时就不会扩容
    //2、当 n - m < t < m,此时会按照2 * m进行扩容
    //3、当n - m < t, m < t < n,此时会按照 t + m进行扩容
    //4、当n - m < t, t > n,此时会按照 t + m进行扩容
    cout << endl;
    it = number.begin();
    ++it;
    ++it;
    cout << "*it = " << *it << endl;
    number.insert(it, 100, 666);
    display(number);
    cout << "*it = " << *it << endl;
    printContainerCapacity(number);

    cout << endl;
    vector<int> vec = {11, 33, 55, 22};
    it = number.begin();
    ++it;
    ++it;
    cout << "*it = " << *it << endl;
    number.insert(it, vec.begin(), vec.end());
    display(number);
    cout << "*it = " << *it << endl;
    printContainerCapacity(number);
}

int main(int argc, char *argv[])
{
    test();
    return 0;
}


