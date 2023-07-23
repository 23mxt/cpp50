#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;
using std::istream_iterator;
using std::ostream_iterator;
using std::vector;
using std::copy;

void test1()
{
    vector<int> vec;
    /* cout << "111" << endl; */
    istream_iterator<int> isi(std::cin);
    /* cout << "222" << endl; */
    //vector中插入元素常用insert或者push_back
    /* copy(isi, istream_iterator<int>(), vec.begin()); */

    copy(isi, istream_iterator<int>(), std::back_inserter(vec));
    /* cout << "333" << endl; */
    copy(vec.begin(), vec.end(),
         ostream_iterator<int>(cout, "  "));
    /* cout << "444" << endl; */
    cout << endl;

}

void test()
{
    vector<int> vec;
    cout << "111" << endl;
    istream_iterator<int> isi(std::cin);
    cout << "222" << endl;
    copy(isi, istream_iterator<int>(), std::back_inserter(vec));
    copy(vec.begin(), vec.end(),
         ostream_iterator<int>(cout, "  "));
    cout << endl;

}

int main(int argc, char *argv[])
{
    test();
    return 0;
}


