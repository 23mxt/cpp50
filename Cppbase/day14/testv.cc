#include <string.h>
#include <iostream>
using std::cout;
using std::endl;
using std::string;

class A
{
public:
    A(){
        cout << "A()" << endl;
    }
    A(int ia)
    :_ia(ia)
    {
        cout << "A(int)" << endl;
    }

    void f()
    {
        cout << "A::f()" << endl;
    }
protected:
    int _ia;
};

class B
:virtual public A
{
public:
    B()
    {
        cout << "B()" << endl;
    }

    B(int ia, int ib)
    :A(ia)
    ,_ib(ib)
    {
        cout << "B(int, int)" << endl;
    }

protected:
    int _ib;
};

class C
:public B
{
public:
    C(int ia, int ib, int ic)
    :A(ia)//虚继承链的末尾负责虚基类的构造
    ,B(ia, ib)//已构造过的，不会再次构造
    ,_ic(ic)
    {
        cout << "C(int, int, int)" << endl;
    }

    void show() const
    {
        cout << "_ia" << _ia << endl
            << "_ib" << _ib << endl
            << "_ic" << _ic << endl;
    }
private:
    int _ic;
};

int main() {
    C c(10, 20, 30);
    c.show();
    return 0;
}

