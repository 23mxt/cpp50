#include <string.h>
#include <iostream>
using std::cout;
using std::endl;
using std::string;

class Point
{
public:
    Point(int ix, int iy)
    :_ix(ix)
    ,_iy(iy)
    {
        cout << "Point(int, int)" << endl;
    }
    //()chongzai
    Point& operator()(int x, int y)
    {   
        _ix += x;
        _iy += y;
        return (*this);
    }

    void print()
    {
        cout << "print()" << endl;
        cout << "(" << _ix
            << "," << _iy << ")" << endl;
    }
private:
    int _ix;
    int _iy;
};

void test()
{
    Point pt1(1, 2);
    pt1.print();
    cout << "pt1()overload" << endl;
    pt1(1,2);
    pt1.print();

    cout << endl;
    Point* pt2 = new Point(7, 8);
    pt2->print();
    cout << "not overload ->" << endl;
}

void test2()
{
    auto a = 1;
    cout << "a = " << a << endl;
}

int main() {
    /* test(); */
    test2();
    return 0;
}

