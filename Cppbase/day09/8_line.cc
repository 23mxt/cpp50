#include <iostream>

using std::cout;
using std::endl;

//内部类
class Line
{
public:
    Line(int x1, int y1, int x2, int y2)
    : _pt1(x1, y1)
    , _pt2(x2, y2)
    {
        cout << "Line(int, int, int, int)" << endl;
    }

    void printLine() const
    {
        _pt1.print();
        cout << "---->";
        _pt2.print();
        cout << endl;
    }


    ~Line()
    {
        cout << "~Line()" << endl;
    }

private:
    class Point
    {
    public:
        Point(int ix = 0, int iy = 0)
        : _ix(ix)
        , _iy(iy)
        {
            cout << "Point(int = 0, int = 0)" << endl;
        }

        void print() const
        {
            cout << "("
                 << _ix << ", "
                 << _iy
                 << " )";
        }

        ~Point()
        {
            cout << "~Point() " << endl;
        }

    private:
        int _ix;
        int _iy;
    };
private:
    Point _pt1;
    Point _pt2;
};

void test()
{
    Line line(1, 2, 3, 4);
    line.printLine();
}

int main(int argc, char **argv)
{
    test();
    return 0;
}


