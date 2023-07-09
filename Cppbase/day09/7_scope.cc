#include <iostream>

using std::cout;
using std::endl;

int number = 1;

namespace wd
{
int number = 20;

class Test
{
public:
    Test(int value = 0)
    : number(value)
    {

    }

    void print(int number) const
    {
        cout << "number = " << number << endl;
        cout << "数据成员number = " << this->number << endl;
        cout << "数据成员number = " << Test::number << endl;
        cout << "命名空间中的number = " << wd::number << endl;
        cout << "全局变量number = " << ::number << endl;

    }
private:
    int number;
};//end of class Test

}//end of namespace wd

int main(int argc, char **argv)
{
    wd::Test tst(300);
    tst.print(4000);
    return 0;
}


