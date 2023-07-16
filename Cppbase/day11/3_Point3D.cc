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
: protected Point
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
        cout << "(" << _ix //protected
             /* << ", " << _iy//私有的，体现封装性 */
             << ", " << getY() //protected
             << ", " << _iz //private
             << " )" << endl;
    }
private:
    int _iz;
};

class Point4D
: protected Point3D
{
public:
    void display()
    {
        print();
        cout << "(" << _ix //protected
             /* << ", " << _iy//私有的，体现封装性 */
             << ", " << getY() //protected
             /* << ", " << _iz //private */
             << ", " << _ia //private
             << " )" << endl;
    }
private:
    int _ia;

};

//继承（吸收）与直接访问是两码事
void test()
{
    cout << "sizeof(Point) = " << sizeof(Point) << endl;// 8
    cout << "sizeof(Point3D) = " << sizeof(Point3D) << endl;// 12
    cout << "sizeof(Point4D) = " << sizeof(Point4D) << endl;// 16
    Point3D pt3d(1, 2, 3);
    /* pt3d._ix;//error */
    /* pt3d._iz;//error */
    /* pt3d.getY();//error */

}

int main(int argc, char **argv)
{
    test();
    return 0;
}


