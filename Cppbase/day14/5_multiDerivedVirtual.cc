#include <iostream>

using std::cout;
using std::endl;

class A
{
public:
    virtual
    void a()
    {
        cout << "A::a()" << endl;
    }

    virtual
    void b()
    {
        cout << "A::b()" << endl;
    }

    virtual
    void c()
    {
        cout << "A::c()" << endl;
    }
};

class B
{
public:
    virtual
    void a()
    {
        cout << "B::a()" << endl;
    }

    virtual
    void b()
    {
        cout << "B::b()" << endl;
    }

    void c()
    {
        cout << "B::c()" << endl;
    }

    void d()
    {
        cout << "B::d()" << endl;
    }
};

class C
: public A
, public B
{
public:
    virtual
        //覆盖
    void a()
    {
        cout << "C::a()" << endl;
    }

    void c()
    {
        cout << "C::c()" << endl;
    }

    //隐藏
    void d()
    {
        cout << "C::d()" << endl;
    }
};

class D
: public C
{
public:
    void c() //C是虚函数的证明
    {
        cout << "D::c()" << endl;
    }
};

void test()
{
    cout << "sizeof(A) = " << sizeof(A) << endl;//8
    cout << "sizeof(B) = " << sizeof(B) << endl;//8
    cout << "sizeof(C) = " << sizeof(C) << endl;//16

#if 1
    cout << endl;
    C c;
    printf("C的地址: %p\n", &c);

    A *pa = &c;
    printf("pa指向的地址: %p\n", pa);
    pa->a();//C::a()
    pa->b();//A::b()
    pa->c();//C::c()

    cout << endl;
    B *pb = &c;
    printf("pb指向的地址: %p\n", pb);
    pb->a();//C::a()
    pb->b();//B::b()
    pb->c();//B::c()
    pb->d();//B::d()

    cout << endl;
    C *pc = &c;
    printf("pc指向的地址: %p\n", pc);
    pc->a();//C::a()
    /* pc->b();//二义性 */
    pc->A::b();//A::b
    pc->B::b();//B::b
    pc->c();//C::c()
    pc->d();//C::d()

    cout << endl;
    D d;
    pc = &d;
    pc->c();
#endif
}

int main(int argc, char *argv[])
{
    test();
    return 0;
}


