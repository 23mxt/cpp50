#include <iostream>

using std::cout;
using std::endl;

//如果将一个类的构造函数设置为protected，那么该类也是抽象类
//抽象类也是不能创建对象
//注意：与将构造函数设置为私有的是不一样的，将构造函数设置为
//私有的，确实在类外不能创建对象，但是不能被派生类直接访问
class Base
{
/* private: */
protected:
    Base()
    {
        cout << "Base()" << endl;
    }
};

class Derived
: public Base
{
public:
    Derived()
    : Base()
    {
        cout << "Derived()" << endl;
    }

};

void test()
{
    /* Base base;//error */
    Derived derived;//ok
}
int main(int argc, char **argv)
{
    test();
    return 0;
}


