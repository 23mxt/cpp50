#include <string.h>
#include <iostream>

using std::cout;
using std::endl;

class Base
{
public:
    Base(const char *pbase)
    : _pbase(new char[strlen(pbase) + 1]())
    {
        cout << "Base(const char *)" << endl;
        strcpy(_pbase, pbase);
    }

    virtual
    void print() const
    {
        if(_pbase)
        {
            cout << "Base::_pbase = " << _pbase << endl;
        }
    }

    //将基类的析构函数设置为虚函数之后，派生类的析构函数会自动
    //成为虚函数
    //
    //为什么可以体现多态呢，因为有重写，但是重写的时候，基类
    //与派生类的析构函数的名字不一样，但是对于编译器而言，都
    //认为每个类的析构函数都称为destructor，所以对于编译器而言
    //就是重写
    //为什么编译器可以对于析构函数有这种重写？
    //因为对于任何一个类而言，析构函数只有一个，具有唯一性
    virtual
    ~Base()
    {
        cout <<"~Base()" << endl;
        if(_pbase)
        {
            delete [] _pbase;
            _pbase = nullptr;
        }
    }

private:
    char *_pbase;
};

class Derived
: public Base
{
public:
    Derived(const char *pbase, const char *pderived)
    : Base(pbase)
    , _pderived(new char[strlen(pderived) + 1]())
    {
        cout << "Derived(const char *, const char *)" <<endl;
        strcpy(_pderived, pderived);
    }

    void print() const
    {
        if(_pderived)
        {
            cout << "Derived::_pderived = " << _pderived << endl;
        }
    }

    ~Derived()
    {
        cout << "~Derived()" << endl;
        if(_pderived)
        {
            delete [] _pderived;
            _pderived = nullptr;
        }
    }

private:
    char *_pderived;
};

//会有内存泄漏
int main(int argc, char **argv)
{
    Base *pbase = new Derived("hello", "world");//堆对象
    pbase->print();//多态

    /* delete dynamic_cast<Derived *>(pbase); */

    //destructor()
    //pbase->~destructor()
    //1、执行析构函数,pbase->~Base();
    //2、执行operator delete
    delete pbase;
    pbase = nullptr;

    return 0;
}


