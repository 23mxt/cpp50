#include <iostream>

using std::cout;
using std::endl;

class A
{
public:
    A()
    {
        cout << "A()" << endl;
    }

    A(int ia)
    : _ia(ia)
    {
        cout << "A(int)" << endl;
    }

    ~A()
    {
        cout <<"~A()" << endl;
    }
protected:
    int _ia;
};

class B
: virtual public A
{
public:
    B()
    {
        cout <<"B()" << endl;
    }

    B(int ia, int ib)
    : A(ia)
    , _ib(ib)
    {
        cout << "B(int, int)" << endl;
    }

    ~B()
    {
        cout << "~B()" << endl;
    }
protected:
    int _ib;
};

class C
: public B
{
public:
    C()
    {
        cout << "C()" << endl;
    }

    C(int ia, int ib, int ic)
    /* : A() */
    //如果继承链上存在虚继承的基类
    : A(ia)//最终的派生类需要完成虚基类中数据成员的构造
    , B(ia, ib)
    , _ic(ic)
    {
        cout << "C(int, int, int)" << endl;
    }

    void print() const
    {
        cout << "_ia = " << _ia << endl
             << "_ib = " << _ib << endl
             << "_ic = " << _ic << endl;
    }

    ~C()
    {
        cout << "~C()" << endl;
    }

private:
    int _ic;
};

int main(int argc, char *argv[])
{
    C c(10, 20, 30);
    c.print();
    return 0;
}


