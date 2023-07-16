#include <iostream>

using std::cout;
using std::endl;

//Base是抽象类，声明了纯虚函数的类称为抽象类
//抽象类是不能创建对象的
//抽象类虽然不能创建对象，但是可以创建抽象类的指针或者引用
class Base
{
public:
    virtual void print() = 0;//纯虚函数
    virtual void show() = 0;//纯虚函数
};

class Derived
: public Base
{
public:
    void print() override
    {
        cout << "Derived::print()" << endl;
    }
};

class Derived2
: public Derived
{
public:
    void show() override
    {
        cout << "Derived2::show()" << endl;
    }

};

void test()
{
    /* Base base; */
    /* Derived derived; */
    Derived2 derived2;

    Base *pbase = &derived2;
    Base &ref = derived2;
    pbase->print();
    pbase->show();
    ref.print();
    ref.show();

    Derived *pderived = &derived2;
    Derived &ref2 = derived2;
    pderived->print();//
    pderived->show();
}
int main(int argc, char **argv)
{
    test();
    return 0;
}


