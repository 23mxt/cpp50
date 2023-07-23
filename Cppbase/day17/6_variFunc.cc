#include <iostream>

using std::cout;
using std::endl;

int sum()
{
    return 0;
}

template <typename T, typename ...Args>
int sum(T t, Args ...args)
{
    return t + sum(args...);
}

int main(int argc, char *argv[])
{
    //除了for循环，求sum还可以用函数模板实现
    cout << "sum(1, 2, 3, 4, 5, 6, 7, 8, 9, 10) = "
         << sum(1, 2, 3, 4, 5, 6, 7, 8, 9, 10) << endl;
    return 0;
}


