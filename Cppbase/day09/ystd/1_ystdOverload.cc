#include <iostream>

using std::cout;
using std::endl;

#ifdef __cplusplus
extern "C"
{
#endif

int add(int x, int y)
{
    return x + y;
}

#ifdef __cplusplus
}//end of extern "C"
#endif

int main(int argc, char **argv)
{
    int a = 3;
    int b = 4;
    int res = add(a, b);
    cout << res << endl;

    return 0;
}

