#include <assert.h>
#include <string.h>
#include <iostream>
using std::cout;
using std::endl;
using std::string;

template <typename T> 
class Singleton
{
public:
template <typename ...Args>
    static  T *getInstance (Args ...args)
    {
        cout << "getInstance(Args ...args)" << endl;
        if(_pInstance == nullptr)
        {
            _pInstance = new T(args...);
        }
        return _pInstance;
    }

    static void destroy()
    {
        cout << "destroy()" << endl;
        if(_pInstance != nullptr)
        {
            delete _pInstance;
            _pInstance = nullptr;
        }
        return;
    }
private:
    static T* _pInstance;
    Singleton();
    ~Singleton();
};
//static成员变量也要使用模板
//使用饿汉模式
template <typename T>
T *Singleton<T>::_pInstance = nullptr;

class Point
{
    template <typename T>
    friend class Singleton;
private:
    Point(int x, int y)
    :_ix(x)
    ,_iy(y)
    {
        cout << "Point(int, int)" << endl;
    }

    ~Point()
    {
        cout << "~Point()" << endl;
    }
private:
    int _ix;
    int _iy;
};

class Computer
{
    template <typename T>
    friend class Singleton;
private:
    Computer(string brand, int price)
    :_brand(brand)
    ,_price(price)
    {
        cout << "Computer(string, int)" << endl; 
    }

    ~Computer()
    {
        cout << "~Computer()" << endl;
    }
private:
    string _brand;
    int _price;
};

/* Point pt(1,2); */
/* Point pt2(3,4); */

/* Computer com("pc", 1000); */

int main() 
{
    Point *pt1 = Singleton<Point>::getInstance(1, 2); 
    Point *pt2 = Singleton<Point>::getInstance(1, 2); 
    assert(pt1 == pt2);
    /* (Singleton<Point>*)pt1->destroy(); */
    
    Computer *pc1 = Singleton<Computer>::getInstance("Xiaomi", 6666);
    Computer *pc2 = Singleton<Computer>::getInstance("Xiaomi", 6666);
    assert(pc1 == pc2);//判断两者是同一个地址
    return 0;
}

