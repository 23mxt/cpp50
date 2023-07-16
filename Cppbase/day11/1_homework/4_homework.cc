#include <string.h>
#include <iostream>
using std::cout;
using std::endl;
using std::string;

class Circle
{
public:
    Circle()
    :_r(0)
    {
        cout << "Circle()" << endl;
    }

    Circle(double r)
    :_r(r)
    {
        cout << "Circle(double)" << endl;
    }

    //获取圆的面积
    double getArea()
    {
        return (3.14*_r*_r);
    }

    //获取圆的周长
    double getPerimeter()
    {
        return (2*3.14*_r);
    }

    //打印圆的半径、周长、面积输出到屏幕
    void show()
    {
        cout << "double r " << _r << "  Perimeter " << getPerimeter() << "   Area " << getArea() << endl;
    }

    ~Circle()
    {
        cout << "~Circle()" << endl;
    }
private:
    double _r;
};


int main() {
    Circle myc(3);
    myc.show();//3 6*3.14 9*3.14
    return 0;
}

