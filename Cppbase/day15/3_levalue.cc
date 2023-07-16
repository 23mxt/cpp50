#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

void test()
{
    int a = 10;//栈上
    int b = 20;//栈上
    int *pflag = &a;
    string s1("hello");
    string s2 = "wolrd";

    &a;//ok,左值
    &b;//ok,左值
    /* &(a + b);//error,右值 */
    &pflag;//ok,左值
    &*pflag;//ok,左值
    *&pflag;

    &s1;//ok,左值
    &s2;//ok,左值
    /* &(s1 + s2);//error,右值 */

    int number = 10;
    int &ref = number;
    &number;//ok,左值
    &ref;//ok,左值
    /* int &ref2 = 10;//error，非const左值引用不能绑定到右值 */
    const int &ref2 = 10;//ok，const左值引用可以绑定到右值
    const int &ref3 = number;//ok，const左值引用可以绑定到左值
    //const左值引用既可以绑定到左值，也可以绑定到右值
    //
    //C++98的语法特性，无法区别传递的是左值还是右值
    //C++11提出来了右值引用
    //右值引用的特点：可以绑定到右值，但是不能绑定到左值
    //也就是：可以识别右值，不能识别左值
    int &&rref = 10;//右值引用可以绑定到右值
    /* int &&rref2 = number;//error, 右值引用不能绑定到左值 */
    &rref;//在此处，右值引用本身是一个左值
}
int main(int argc, char *argv[])
{
    test();
    return 0;
}


