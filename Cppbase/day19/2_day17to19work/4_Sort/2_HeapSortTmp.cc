#include <math.h>
#include <iostream>
#include <vector>
#include <ostream>

using std::cout;
using std::cin;
using std::endl;
using std::vector;

template<typename T>
void swap(T &lhs, T &rhs)
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
       << ", " <<rhs._iy
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

//函数对象
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

template <typename T, typename Compare = std::less<T>>
class HeapSort
{
public:
    HeapSort(T *arr, size_t size,Compare);
    void heapAdjust(size_t ,size_t ,Compare&);
    void sort(Compare&);
    void print();

private:
    vector<T> vec;
};

template <typename T, typename Compare >
HeapSort<T, Compare>::HeapSort(T *arr, size_t size, Compare com)
{
    for (size_t i = 0; i < size; i++)
    {
        vec.push_back(arr[i]);
    }
    for (int i = size/2 - 1; i >= 0; i--)
    {
        heapAdjust(i, size,com);
    }
    swap(arr[0], arr[size - 1]);
    sort(com);
}

template <typename T, typename Compare >
void HeapSort<T, Compare>::heapAdjust(size_t adjustpos, size_t arrlen, Compare& com)
{
    size_t dad = adjustpos;
    size_t son= 2 * dad + 1;

    while(son < arrlen)
    {
        if(son + 1 < arrlen && com(vec[son], vec[son + 1]))
        {
            ++son;
        }
        //若左操作数小于右操作数，那么交换两者位置，构造出来的是大根堆
        if(com(vec[dad], vec[son]))
        {
            swap(vec[dad], vec[son]);
            dad = son;
            son= 2 * dad + 1;
        }
        else
        {
            break;
        }
    }
}

template <typename T, typename Compare >
void HeapSort<T, Compare>::sort(Compare& com)
{
    size_t size = vec.size();
    for (size_t i = size; i > 1; i--)
    {
        heapAdjust(0, i, com);
        swap(vec[0], vec[i - 1]);
    }
}

template <typename T, typename Compare>
void HeapSort<T,Compare>::print()
{
    for(auto &elem : vec)
    {
        cout<< elem << "  ";
    }
    cout << endl;
}

int main(int argc, char **argv)
{
    //排序如果使用std::less作为比较方式的话，那么小于就会返回true,true就会交换两者的位置，即把大的交换到堆顶
    //这样最后得到的就是大根堆
    //经过循环后得到的就是升序排列的结果了
    int arr[10] = {1, 2, 6, 3, 4, 8, 5, 7, 9, 10};
    HeapSort<int> hs(arr, 10, std::less<int>());
    hs.print();
    cout << endl;
    Point par[5] = {{1,2}, {3,4}, {-1,2}, {4,5}, {2,5}};

    HeapSort<Point> hsPt(par, 5, std::less<Point>());
    hsPt.print();

    return 0;
}

