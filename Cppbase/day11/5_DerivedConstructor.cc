#include <iostream>

using std::cout;
using std::endl;

class Base
{
public:
    Base()
    : _base(0)
    {
        cout << "Base()" << endl;
    }

    ~Base()
    {
        cout << "~Base()" << endl;
    }
private:
    long _base;
};

class Derived
: public Base
{
public:
    Derived(long derived = 0)
    : Base()
    , _derived(derived)
    {
        cout << "Derived(long = 0)" << endl;
    }

    void print() const
    {
        cout << "Derived:: " << _derived << endl;
    }

    ~Derived()
    {
        cout << "~Derived()" << endl;
    }
private:
    long _derived;
};

void test()
{
    //error,创建派生类对象的时候，“先调用基类的构造函数，然后调用
    //派生类的构造函数”
    //ok,创建派生类对象的时候，会调用派生类的构造函数，但是因为
    //派生类会继承基类，会吸收基类的数据成员，为了完成从基类吸收的
    //数据成员的初始化以及成员函数的吸收，所以借助基类的构造函数,在执行派生类自己数据
    //成员的初始化
    Derived d(10);
    d.print();
}

int main(int argc, char **argv)
{
    test();
    return 0;
}


