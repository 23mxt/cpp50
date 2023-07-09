#include <string.h>
#include <iostream>
using std::cout;
using std::endl;
using std::string;

class Base
{
public:
    Base(const int num)
    :_num(num)
    {

    }

    friend int operator+(Base &lhs, Base &rhs);
private:
   int  _num;
};

int operator+(Base &lhs,Base &rhs)
{
    if(lhs._num < 3){
        lhs._num = -lhs._num;
    }
    return lhs._num + rhs._num;
}

void test()
{
    int i = 2;
    int j = 7;

    Base x(i);
    Base y(j);
    cout << (x+y == j - i) << endl;
}   

int main() {
    test();
    return 0;
}

