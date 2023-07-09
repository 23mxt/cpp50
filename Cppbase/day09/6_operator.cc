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
        cout << "Point(int = 0, int = 0)" << endl;
    }

    ~Point()
    {
        cout << "~Point() " << endl;
    }

    operator int()
    {
        cout << "operator int()" << endl;
        return _ix + _iy;
    }

#if 0
    operator double()
    {
        cout << "operator double()" << endl;
        if(0 != _iy)
        {
            return (static_cast<double>(_ix)/_iy);
        }
        else
        {
            return 0.0;
        }
    }
#endif
private:
    int _ix;
    int _iy;
};

void test()
{
    Point pt(1, 2);
    cout << "pt = " << pt << endl;//Point---->int
}

int main(int argc, char **argv)
{
    test();
    return 0;
}


