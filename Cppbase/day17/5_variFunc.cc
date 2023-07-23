#include <iostream>

using std::cout;
using std::endl;

template <typename ...Args>//模板参数包Args,...位于Args的左边称为打包
/* template <typename  T1, typename  T2, typename  T3, typename  T4> */
/* void display(T1 x, T2 y, T3 z, T4 a, T2 b) */
void display(Args ...args)//函数参数包args,...位于args左边表示打包
{
    cout << "sizeof...(Args) = " << sizeof...(Args) << endl;
    cout << "sizeof...(args) = " << sizeof...(args) << endl;
    /* cout << "...Args" << ...Args << endl; //error*/
    /* cout << "...Args" << Args... << endl;//error */
}

//template <typename T1, typename T2, typename T3>
//void display(T1 x, T2 y, T3 s1)
//void display(int x, double y, string s1)
void test()
{
    display();

    display(1, 2.2, "hello");
}

void print()
{
    cout << endl;
}

template <typename  T, typename  ...Args>
void print(T t, Args ...args)
{
    cout << t << "  ";
    print(args...);//...位于args的右边的时候，称为解包
                   //解包是实参，打包是形参
}

void test2()
{
    print();

    //T推导成int类型，t = 1
    //cout << 1 << "  ";
    //print("hello", 3.3, true)
    //   T推导成string,t = "hello"
    //     cout << "hello" << " ";
    //     print(3.3, true);
    //      T推导成double类型，t = 3.3
    //      cout << 3.3 << " ";
    //      print(true);
    //          T推导成bool，t = true
    //            cout << 1 << " ";
    //              print();
    //              cout << endl;
    print(1, "hello", 3.3, true);
}

int main(int argc, char *argv[])
{
    test2();
    return 0;
}


