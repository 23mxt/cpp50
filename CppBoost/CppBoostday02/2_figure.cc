#include <math.h>
#include <iostream>
#include <memory>
#include <string>

using std::cout;
using std::endl;
using std::unique_ptr;
using std::string;

//面向对象的设计原则：开放闭合原则
//对扩展开放，对修改关闭
//
//抽象类，作为接口使用
class Figure
{
public:
    //纯虚函数
    virtual void display() const = 0;
    virtual double area() const = 0;
    virtual ~Figure() {}
};

class Rectangle
: public Figure
{
public:
    Rectangle(double length = 0, double width = 0)
    : _length(length)
    , _width(width)
    {
        cout << "Rectangle(double = 0, double = 0)" << endl;
    }

    void display() const override
    {
        cout << "Rectangle";
    }

    double area() const override
    {
        return _length * _width;
    }

    ~Rectangle()
    {
        cout << "~Rectangle()" << endl;
    }
private:
    double _length;
    double _width;
};

class Circle
: public Figure
{
public:
    Circle(double radius = 0)
    : _radius(radius)
    {
        cout << "Circle(double = 0)" << endl;
    }

    void display() const override
    {
        cout << "Circle";
    }

    double area() const override
    {
        return 3.14 * _radius *_radius;;
    }

    ~Circle()
    {
        cout << "~Circle()" << endl;
    }
private:
    double _radius;
};

class Triangle
: public Figure
{
public:
    Triangle(double a = 0, double b = 0, double c = 0)
    : _a(a)
    , _b(b)
    , _c(c)
    {
        cout << "Triangle(double = 0, double = 0, double = 0)" << endl;
    }

    void display() const override
    {
        cout << "Triangle";
    }

    double area() const override
    {
        //海伦公式
        double tmp = (_a + _b + _c)/2;

        return sqrt(tmp * (tmp - _a) * (tmp - _b) * (tmp - _c));
    }

    ~Triangle()
    {
        cout << "~Triangle()" << endl;
    }
private:
    double _a;
    double _b;
    double _c;
};

void func(Figure *pfig)
{
    pfig->display();
    cout << "的面积 : " << pfig->area() << endl;
}

//优点
//1、满足单一职责原则
//2、满足开放闭合原则
//3、满足依赖倒置原则
//
//缺点：
//1、工厂的个数与产品的个数对应,产品增加之后，工厂的数量会
//急剧上升
class Factory
{
public:
    virtual Figure *create() = 0;
    virtual ~Factory() {}
};

class RectangleFactory
: public Factory
{
public:
    virtual Figure *create() 
    {
        //数据是从配置文件中读取出来的
        //读取配置文件（xml、txt、conf）
        //读取配置文件的过程
        //获取配置文件中的参数
        //x , y
        Rectangle *prec = new Rectangle(10, 20);
    
        return prec;
    }
};

class CircleFactory
: public Factory
{
public:
    virtual Figure *create() 
    {
        //数据是从配置文件中读取出来的
        //读取配置文件（xml、txt、conf）
        //读取配置文件的过程
        //获取配置文件中的参数
        //r
        Circle *pcir = new Circle(10);
        return pcir;
    }
};

class TriangleFactory
: public Factory
{
public:
    virtual Figure *create() 
    {
        //数据是从配置文件中读取出来的
        //读取配置文件（xml、txt、conf）
        //读取配置文件的过程
        //获取配置文件中的参数
        //x , y, z
        Triangle *ptri = new Triangle(3, 4, 5);
    
        return ptri;
    }
};

void test()
{
    unique_ptr<Rectangle*> prec(RectangleFactory::create());
    unique_ptr<Rectangle*> pcir(RectangleFactory::create());
    unique_ptr<Rectangle*> ptri(RectangleFactory::create());
    
}

int main(int argc, char **argv)
{
    test();
    return 0;
}

