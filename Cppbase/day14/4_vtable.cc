#include <iostream>

using std::cout;
using std::endl;

class Base
{
public:
    Base(long base = 0)
    : _base(base)
    {
        cout << "Base(long = 0)" << endl;
    }

    virtual
    void func()
    {
        cout << "void Base::func()" << endl;
    }

    virtual
    void gunc()
    {
        cout << "void Base::gunc()" << endl;
    }

    virtual
    void hunc()
    {
        cout << "void Base::hunc()" << endl;
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
    Derived(long base = 0, long derived = 0)
    : Base(base)
    , _derived(derived)
    {
        cout << "Derived(long = 0, long = 0)" << endl;
    }

    virtual
    void func()
    {
        cout << "void Derived::func()" << endl;
    }

    virtual
    void gunc()
    {
        cout << "void Derived::gunc()" << endl;
    }

    virtual
    void hunc()
    {
        cout << "void Derived::hunc()" << endl;
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
    //间接的证明虚表是存在的,对于普通的单继承而言，虚表只有一个
    //被该类的所有对象共享,虚表存在于只读段
    Derived derived(100, 200);
    printf("派生类对象derived的地址 : %p\n", &derived);
    printf("派生类对象的虚函数指针的地址 : %p\n", &derived);
    printf("派生类对象的虚函数指针的地址 : %p\n", (long *)&derived);
    printf("派生类虚表的地址: %p\n",
           (long *)*(long *)&derived);
    printf("第一个虚函数的入口地址: %p\n",
           (long *)*(long *)*(long *)&derived);
           /* **&derived); */

    /* typedef int B;//给变量或者类型取别名 */
    /* typedef void (*)()  pFunc; */
    /* void (*pFunc)(); */
    typedef void (*pFunc)(); //本质就是函数指针
    pFunc f  = (pFunc)*(long *)*(long *)&derived;
    printf("第一个虚函数的入口地址 : %p\n", f);
    f();

    pFunc f2 = (pFunc)*((long *)*(long *)&derived + 1);
    printf("第二个虚函数的入口地址 : %p\n", f2);
    f2();

    pFunc f3 = (pFunc)*((long *)*(long *)&derived + 2);
    printf("第三个虚函数的入口地址 : %p\n", f3);
    f3();

#if 1
    cout <<endl <<endl;
    static int a = 0;
    printf("static a的地址：%p\n", &a);
    Derived derived2(111, 222);
    printf("派生类对象derived2的地址 : %p\n", &derived2);
    printf("派生类对象的虚函数指针的地址 : %p\n", &derived2);
    printf("派生类对象的虚函数指针的地址 : %p\n", (long *)&derived2);
    printf("派生类虚表的地址: %p\n",
           (long *)*(long *)&derived2);
    //结论：虚表存于只读段
    printf("第一个虚函数的入口地址: %p\n",
           (long *)*(long *)*(long *)&derived2);

    cout << endl << "打印数据成员的值" << endl;
    cout << "_base = " << (long )*((long *)&derived + 1) << endl;
    cout << "_derived = " << (long )*((long *)&derived + 2) << endl;
#endif
}
int main(int argc, char *argv[])
{
    test();
    return 0;
}


