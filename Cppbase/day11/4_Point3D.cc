#include <iostream>

using std::cout;
using std::endl;

//1、不管是什么继承方式（public/protected/private），基类中的私有
//成员都不能在派生类的类体中进行访问（体现封装性）
//2、不管是什么继承方式（public/protected/private），基类中的非私有
//成员（public/protected）,都可以在派生类的类体中进行访问
//3、对于派生类对象而言，只能访问公有继承基类中的公有成员，其他都
//派生类对象都不能访问

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
        cout << "(" << _ix << ", "
             << _iy << ")" << endl;
    }

    int getY() const
    {
        return _iy;
    }

    ~Point()
    {
        cout << "~Point()" << endl;
    }

protected:
    int _ix;

private:
    int _iy;
};

class Point3D
: private Point
{
public:
    Point3D(int ix = 0, int iy = 0, int iz = 0)
    : Point(ix, iy)//借助基类的构造函数将吸收过来的数据成员初始化
    , _iz(iz)
    {
        cout << "Point3D(int = 0, int = 0, int = 0)" << endl;
    }

    void show()
    {
        /* print(); */
        cout << "(" << _ix //private
             /* << ", " << _iy//私有的，体现封装性 */
             << ", " << getY() //private
             << ", " << _iz //private
             << " )" << endl;
    }
private:
    int _iz;
};

class Point4D
: private Point3D
{
public:
    void display()
    {
        /* print();//error */
        /* cout << "(" << _ix //error */
             /* << ", " << _iy//私有的，体现封装性 */
             /* << ", " << getY() //error */
             /* << ", " << _iz //error*/
             /* << ", " << _ia //private */
             /* << " )" << endl; */
    }
private:
    int _ia;

};
//继承（吸收）与直接访问是两码事
void test()
{
    cout << "sizeof(Point) = " << sizeof(Point) << endl;
    cout << "sizeof(Point3D) = " << sizeof(Point3D) << endl;
    Point3D pt3d(1, 2, 3);
    pt3d.show();
    /* pt3d._ix;//error */
    /* pt3d._iz;//error */
    /* pt3d.getY();//error */

}

int main(int argc, char **argv)
{
    test();
    return 0;
}


