#include <iostream>

using std::cout;
using std::endl;

class Point
{
public:
    Point(int ix = 0, int iy = 0)
    : _ix(ix)
    , _iy(iy)
    {

    }

    /* template <typename  T> */
    template <typename  T = int>
    T func()
    {
        return (T)_iy;
    }

    ~Point()
    {

    }
private:
    int _ix;
    int _iy;
};

void test()
{
    Point pt(1, 2);
    cout << "pt.func() = " << pt.func<double>() << endl;
}

int main(int argc, char *argv[])
{
    test();
    return 0;
}


