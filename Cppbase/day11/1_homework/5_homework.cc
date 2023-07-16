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
        cout << "double r " << _r
            << "   Area " << getArea()
            <<"  Perimeter " << getPerimeter() << endl;
    }

    ~Circle()
    {
        cout << "~Circle()" << endl;
    }
private:
    double _r;
};

class Cylinder
:public Circle
{
public:
    Cylinder(double r,double h)
    :Circle(r)
    ,_h(h)
    {
        cout << "Cylinder(double, double)" << endl;
    }
    
    //获取圆柱体的体积
    
    double getVolume()
    {
        return (getArea() * _h);
    }

    void showVolume()
    {
        cout << "showVolume " << getVolume() << endl;
    }

    //
    ~Cylinder()
    {
        cout << "~Cylinder()" << endl;
    }
private:
    double _h;
};

int main() {
    Circle mycir(3);
    mycir.show();//3 9*3.14 6*3.14

    Cylinder mycyli(3, 2);
    mycyli.showVolume();
    return 0;
}

