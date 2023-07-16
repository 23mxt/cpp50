#include <string.h>
#include <iostream>
using std::cout;
using std::endl;
using std::string;

class A
{
public:
    A(long lx = 0)
    : _lx(lx)
    {
        cout << "A(long = 0)" << endl;
    }

    void print() const
    {
        cout << "A::_lx = " << A::_lx << endl;
    }

    void setX(long lx)
    {
        _lx = lx;
    }

    ~A()
    {
        cout << "~A()" << endl;
    }
private:
    long _lx;
};

//虚拟继承（virtual继承）之后，在派生类对象的存储布局
//的前面多了一个虚基指针
class B
: virtual public A
{
public:
    B()
    {
        cout << "B()" << endl;
    }

    ~B()
    {
        cout << "~B()" << endl;
    }
};

class C
: virtual public A
{
public:
    C()
    {
        cout << "C()" << endl;
    }

    ~C()
    {
        cout << "~C()" << endl;
    }

};

class D
: public B
, public C
{
public:
    D()
    {
        cout << "D()" << endl;
    }

    ~D()
    {
        cout << "~D()" << endl;
    }

};

int main(int argc, char **argv)
{
    cout << "sizeof(A) = " << sizeof(A) << endl;
    cout << "sizeof(B) = " << sizeof(B) << endl;
    cout << "sizeof(C) = " << sizeof(C) << endl;
    cout << "sizeof(D) = " << sizeof(D) << endl;

    cout << endl;
    D d;
    A *pa = &d; 

    return 0;
}


