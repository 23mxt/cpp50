#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

//2、单例模式自动释放的解决方式2：内部类 + 静态数据成员
//Point
class Point
{
public:
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

//电脑类
class Computer
{
public:
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



template <typename T>
class Singleton
{
public:
    static T *getInstance()
    {
        if(nullptr == _pInstance)
        {
            _pInstance = new Singleton();//堆对象
        }

        return _pInstance;
    }

private:
    class AutoRelease
    {
    public:
        AutoRelease()
        {
            cout << "AutoRelease()" << endl;
        }

        ~AutoRelease()
        {
            cout << "~AutoRelease()" << endl;
            if(_pInstance)
            {
                delete _pInstance;
                _pInstance = nullptr;
            }
        }
    };

private:
    Singleton()
    {
        cout << "Singleton()" << endl;
    }

    ~Singleton()
    {
        cout << "~Singleton()" << endl;
    }

private:
    static T*_pInstance;
    static AutoRelease _ar;//_ar对象
};

/* Singleton *Singleton::_pInstance = nullptr; */
T *Singleton::_pInstance = getInstance();
Singleton::AutoRelease Singleton::_ar;//_ar静态对象


int main(int argc, char **argv)
{
    Computer *pc1 = Singleton<Computer>::getInstance("xiaomi", 6666);

    return 0;
}



