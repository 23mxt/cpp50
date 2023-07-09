#include "Line.h"

class Line::LinePimpl
{
public:
    LinePimpl(int x1, int y1, int x2, int y2)
    :pt1(x1, y1)
    ,pt2(x2, y2)
    {
        cout << "LinePimpl(int, int, int, int)" << endl;
    }

    void printLinePimpl() const
    {
         pt1.printPoint();
         cout << "----->";
         pt2.printPoint();
         cout  << endl;
    }

    ~LinePimpl()
    {
        cout << "~LinePimpl()" << endl;
    }
private:
    class Point
    {
    public:
    Point(int x, int y)
    :_ix(x)
    ,_iy(y)
        {
           cout << "Point (int, int)" << endl; 
        }
    void printPoint() const
    {
        cout << "(" << _ix
            << "," << _iy << ")" ;
    }

    ~Point()
    {
        cout << "~Point()" << endl;
    }
    private:
        int _ix;
        int _iy;
    };

private:
Point pt1;
Point pt2;
};


//通过一个指针将原本有关联的两个类进行解耦，该指针将其所对应的类的实现进行信息隐藏
Line::Line(int x1, int y1, int x2, int y2)
:_pimpl(new LinePimpl(x1, y1, x2, y2))
{
    cout << "Line" << endl;
    
}

void Line::printLine() const//只要不修改数据成员，都加const
{
    cout << "printLine" << endl;
    _pimpl->printLinePimpl();
}

Line::~Line()
{
    cout << "~Line" << endl;

    if(_pimpl)
    {
        delete _pimpl;
        _pimpl = nullptr;
    }
}

