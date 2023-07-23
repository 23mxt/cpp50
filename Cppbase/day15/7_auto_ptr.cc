#include <iostream>
#include <memory>

using std::cout;
using std::endl;
using std::auto_ptr;

void test()
{
    //auto_ptr是智能指针
    //pInt是裸指针
    int *pInt = new int(10);
    auto_ptr<int> ap(pInt);
    cout << "*pInt = " << *pInt << endl;//10
    cout << "*ap = " << *ap << endl;//10
    printf("pInt指向的地址 : %p\n", pInt);
    printf("apt托管的空间的地址 : %p\n", ap.get());

    cout << endl;
    //在执行auto_ptr的拷贝构造函数的时候，已经将ap底层的
    //指针置为空了，在置空之前已经将托管的空间的控制权
    //已经交给了ap2,该智能指针存在缺陷（在拷贝操作的时候
    //已经将所有权转移了，并且指针置空了）
    auto_ptr<int>  ap2(ap);
    cout << "*ap2 = " << *ap2 << endl;
    cout << "*ap = " << *ap << endl;
}

int main(int argc, char *argv[])
{
    test();
    return 0;
}


