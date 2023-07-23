#include <math.h>
#include <iostream>
#include <set>
#include <vector>

using std::cout;
using std::endl;
using std::set;
using std::vector;
using std::less;

template <typename Container>
void display(const Container &con)
{
    for(auto &elem : con)
    {
        cout << elem << "  ";
    }
    cout << endl;
}

class Point
{
public:
    Point(int ix = 0, int iy = 0)
    : _ix(ix)
    , _iy(iy)
    {
        /* cout << "Point(int = 0, int = 0)" << endl; */
    }

    double getDistance() const
    {
        return hypot(_ix, _iy);
        /* sqrt(pow(_ix, 2) + pow(_iy, 2)); */
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
        /* cout << "~Point()" << endl; */
    }

    friend std::ostream &operator<<(std::ostream &os, const Point &rhs);
    friend bool operator<(const Point &lhs, const Point &rhs);
    friend struct ComparePoint;
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

//重载小于符号
bool operator<(const Point &lhs, const Point &rhs)
{
    if(lhs.getDistance() < rhs.getDistance())
    {
        return true;
    }
    else if(lhs.getDistance() == rhs.getDistance())
    {
        if(lhs._ix < rhs._ix)
        {
            return true;
        }
        else if(lhs._ix == rhs._ix)
        {
            if(lhs._iy < rhs._iy)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

//函数对象的形式
#if 0
struct ComparePoint
{
    bool operator()(const Point &lhs, const Point &rhs) const
    {
        cout << "struct ComparePoint" << endl;
        if(lhs.getDistance() < rhs.getDistance())
        {
            return true;
        }
        else if(lhs.getDistance() == rhs.getDistance())
        {
            if(lhs._ix < rhs._ix)
            {
                return true;
            }
            else if(lhs._ix == rhs._ix)
            {
                if(lhs._iy < rhs._iy)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
};
#endif

#if 0
namespace  std
{
template <>//模板的特化
struct less<Point>
{
    bool operator()(const Point &lhs, const Point &rhs) const
    {
        cout << "struct less<Point>" << endl;
        if(lhs.getDistance() < rhs.getDistance())
        {
            return true;
        }
        else if(lhs.getDistance() == rhs.getDistance())
        {
            if(lhs.getX() < rhs.getX())
            {
                return true;
            }
            else if(lhs.getX() == rhs.getX())
            {
                if(lhs.getY() < rhs.getY())
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
};

}//end of namespace std
#endif

namespace std
{
//模板的特化
template <>
struct less<Point>
{
public:
    //重载成员访问运算1符
    bool operator()(const Point &lhs, const Point &rhs)  const
    {
        cout << "struct less<Point>" << endl;
        if(lhs.getDistance() < rhs.getDistance())
        {
            return true;
        }
        else if(lhs.getDistance() == rhs.getDistance())
        {
            if(lhs.getX() < rhs.getX())
            {
                return true;
            }
            else if(lhs.getX() == rhs.getX())
            {
                if(lhs.getY() < rhs.getY())
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
};
}//end of namespace std 
 
///函数对象
struct ComparePoint
{
    bool operator()(const Point &lhs, const Point &rhs) const
    {
        cout << "ComparePoint " << endl;
        if(lhs.getDistance() < rhs.getDistance())
        {
            return true;
        }
        else if(lhs.getDistance() == rhs.getDistance())
        {
            if(lhs.getX() < rhs.getX())
            {
                return true;
            }
            else if(lhs.getX() == rhs.getX())
            {
                if(lhs.getY() < rhs.getY())
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }      
};

void test()
{
    /* set<Point> number = { */
        //set默认就是用less进行比较的，有了less的特化，就不会再走小于号的重载了
    set<Point, ComparePoint> number = {
        Point(1, 2),
        Point(3, 12),
        Point(-1, 2),
        Point(1, 2),
        Point(-1, -2),
        Point(1, -2),
        Point(2, 2),
    };
    display(number);
}


int main(int argc, char *argv[])
{
    test();
    return 0;
}


