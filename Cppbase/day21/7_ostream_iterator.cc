#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;
using std::ostream_iterator;
using std::vector;
using std::copy;

//operator<<
void test()
{
    /* cout << 1 << endl << 3 << endl; */
    vector<int> vec = {1, 3, 9, 7, 5};
    ostream_iterator<int> osi(cout, "\n");
    copy(vec.begin(), vec.end(), osi);
}

void test2()
{
    vector<int> vec = {1, 3, 9, 7, 5};
    copy(vec.begin(), vec.end(),
         ostream_iterator<int>(cout, "  "));
    cout << endl;
}

int main(int argc, char *argv[])
{
    test2();
    return 0;
}



