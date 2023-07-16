#include <iostream>

using std::cout;
using std::endl;

class A
{
public:
    virtual
    void func(int val = 1)//参数在编译的时候就确定了
    {
        cout << "A->" << val << endl;
    }

    virtual void test()
    {
        func();
    }
private:
    long _a;
};

class B
: public A
{
public:
    virtual
    void func(int val = 10)
    {
        cout << "B->" << val << endl;
    }
private:
    long _b;
};
int main(void)
{
    B b;
    A *p1 = (A*)&b;
    B *p2 = &b;
    p1->func();//B->1
    p2->func();//B->10

    return 0;
}

