#include <math.h>
#include <iostream>
#include <vector>
#include <ostream>

using std::cout;
using std::cin;
using std::endl;
using std::vector;

template<typename T>
void swap(T &lhs,T &rhs)
{
    auto temp = lhs;
    lhs = rhs;
    rhs = temp;
}

class Point
{
public:
    Point(int ix = 0, int iy = 0)
    : _ix(ix)
    , _iy(iy)
    {
    }

    ~Point()
    {
    }

    void print() const
    {
        cout << "(" << _ix
             << ", " << _iy
             << ")" << endl;
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

    friend std::ostream & operator<<(std::ostream &os, const Point &rhs);

private:
    int _ix;
    int _iy;
};

std::ostream & operator<<(std::ostream &os,const Point &rhs)
{
    os << "(" << rhs._ix
       << ", " << rhs._iy
       << ")";

    return os;
}


namespace std
{
//std命名空间中的less的特化，注意模板的特化
template<>
struct less<Point>
{
    bool operator()(const Point &lhs,const Point &rhs) const
    {
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

//用less需要重载小括号
bool operator<(const Point &lhs, const Point &rhs)
{
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

//用自定义com需要函数对象
struct Comparetion
{
    bool operator()(const Point &lhs,const Point &rhs) const
    {
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

namespace std
{
//std命名空间中的less的特化，注意模板的特化
template<>
struct greater<Point>
{
    bool operator()(const Point &lhs,const Point &rhs) const
    {
        if(lhs.getDistance() > rhs.getDistance())
        {
            return true;
        }
        else if(lhs.getDistance() == rhs.getDistance())
        {
            if(lhs.getX() > rhs.getX())
            {
                return true;
            }
            else if(lhs.getX() == rhs.getX())
            {
                if(lhs.getY() > rhs.getY())
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

bool operator>(const Point &lhs, const Point &rhs)
{
    if(lhs.getDistance() > rhs.getDistance())
    {
        return true;
    }
    else if(lhs.getDistance() == rhs.getDistance())
    {
        if(lhs.getX() > rhs.getX())
        {
            return true;
        }
        else if(lhs.getX() == rhs.getX())
        {
            if(lhs.getY() > rhs.getY())
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

template<typename T,typename Compare = std::less<T>>
class MyQsort
{
public:
    MyQsort(T *arr, size_t size, Compare );//if(a < b)  if(com(a, b))
    void quick(int left, int right, Compare &);
    int partition(int left, int right, Compare &);
    void print();
private:
    vector<T> _vec;
};

template <typename T, typename Compare>
void MyQsort<T,Compare>::print()
{
    for(auto &elem : _vec)
    {
        cout << elem << "  ";
    }
    cout << endl;
}

template<typename T,typename Compare>
MyQsort<T,Compare>::MyQsort(T * arr, size_t size, Compare com)
{
    for(size_t i = 0; i < size; i++)
    {
        _vec.push_back(arr[i]);
    }

    quick(0, _vec.size() - 1, com);
}

template<typename T,typename Compare>
void MyQsort<T,Compare>::quick(int left, int right, Compare &com)
{
    int pivot;
    if(left < right)
    {
        pivot = partition(left, right, com);
        quick(left, pivot - 1, com);//左边递归调用
        quick(pivot + 1, right, com);//右边递归调用
    }
}

template<typename T, typename Compare>
int MyQsort<T, Compare>::partition(int left, int right, Compare &com)
{
    int indexi, indexk;
    for(indexi = left, indexk = left; indexi < right; ++indexi)
    {
        if(com(_vec[indexi], _vec[right]))
        {
            swap(_vec[indexi], _vec[indexk]);
            ++indexk;
        }

    }
    swap(_vec[indexk], _vec[right]);

    return indexk;
}

int main(int argc,char **argv)
{
    int arr[10] = {1, 2, 4, 5, 8, 6, 3, 7, 10, 9} ;
    MyQsort<int> mqInt(arr, 10, std::less<int>());
    /* MyQsort<int, std::greater<int>> mqInt1(arr, 10, std::greater<int>()); */

    mqInt.print();

    Point par[5] = {Point(1,2), Point(3,4), Point(-1,2), Point(4,5), Point(2,5)};
    MyQsort<Point> mqPt(par,5,std::less<Point>());
    mqPt.print();

    return 0;
}

