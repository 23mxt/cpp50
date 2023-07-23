#include <math.h>
#include <iostream>
#include <unordered_set>

using std::cout;
using std::endl;
using std::unordered_set;

template <typename Container>
void display(const Container &con)
{
    for(auto &elem : con)
    {
        cout << elem << "  ";
    }
    cout << endl;
}

void test()
{
    //unordered_set的特征
    //1、存放的是key值，key值是唯一的，不能重复
    //2、key值是没有顺序的
    //3、底层使用的是哈希
    unordered_set<int> number = {1, 6, 9, 8, 4, 2, 7, 9, 1, 4};
    display(number);
}

class Point
{
public:
    Point(int ix = 0, int iy = 0)
    : _ix(ix)
    , _iy(iy)
    {
    }

    double getDistance() const
    {
        return hypot(_ix, _iy);
    }

    int getX() const
    {
        return _ix;
    }

    int getY() const
    {
        return _iy;
    }

    ~Point()
    {
    }

    friend std::ostream &operator<<(std::ostream &os, const Point &rhs);
private:
    int _ix;
    int _iy;
};

std::ostream &operator<<(std::ostream &os, const Point &rhs)
{
    os << "(" << rhs._ix
       << ", " << rhs._iy
       << ")";

    return os;
}

//命名空间是可以进行扩展的
namespace  std
{

template <>//模板的特化
struct hash<Point>
{
    size_t operator()(const Point &lhs) const
    {
        cout << "struct hash<Point>" << endl;
        return (lhs.getX() << 1)^(lhs.getY() << 2);
    }
};

}//end of namespace std

//函数对象的形式
struct HashPoint
{
    size_t operator()(const Point &lhs) const
    {
        cout << "struct HashPoint" << endl;
        return (lhs.getX() << 1)^(lhs.getY() << 2);
    }

};

bool operator==(const Point &lhs, const Point &rhs)
{
    cout << "bool operator==(const, const)" << endl;
    return (lhs.getX() == rhs.getX()) && (lhs.getY() == rhs.getY());
}

namespace std
{
template <>
struct equal_to<Point>
{
    bool operator()(const Point &lhs, const Point &rhs) const
    {
        cout << "struct equal_to<Point>" << endl;
        return (lhs.getX() == rhs.getX()) && (lhs.getY() == rhs.getY());
    }

};//end of equal_to

}//end of namespace std

struct EqualToPoint
{
    bool operator()(const Point &lhs, const Point &rhs) const
    {
        cout << "struct EqualToPoint" << endl;
        return (lhs.getX() == rhs.getX()) && (lhs.getY() == rhs.getY());
    }

};

void test2()
{
    /* unordered_set<Point> number = { */
    unordered_set<Point, HashPoint> number = {
    /* unordered_set<Point, HashPoint, EqualToPoint> number = { */
        Point(1, 2),
        Point(10, 30),
        Point(1, -2),
        Point(1, 2),
        Point(-1, 2),
        Point(1, -2),
        Point(4, 2),
    };
    display(number);
}

int main(int argc, char *argv[])
{
    test2();
    return 0;
}


