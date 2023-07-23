#include "SingleTon.h"
#include <string.h>
#include <iostream>

using std::cout;
using std::endl;
using std::string;

template <class T>
T * Singleton<T>::_pInstance = nullptr;

template <class T>
typename Singleton<T>::AutoRelease Singleton<T>::_ar;//typename表名是一个类型

class Point
{
public:
	Point(int ix = 0, int iy = 0)
	: _ix(ix)
	, _iy(iy)
	{
        cout << "Point(int = 0,int = 0)" << endl;
    }

	void print() const
	{
		cout << "(" << _ix
			 << ", " << _iy
			 << ")" << endl;
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
public:
    Computer(const char *brand, float price)
    : _brand(new char[strlen(brand) + 1]())
    , _price(price)
    {
        cout << "Computer(const char *, float)" << endl;
        strcpy(_brand, brand);
    }

    void print() const
    {
        if(_brand)
        {
            cout << "brand: " << _brand << endl
                 << "price: " << _price << endl;
        }
    }

    ~Computer()
    {
        cout << "~Computer()" << endl;
        if(_brand)
        {
            delete [] _brand;
            _brand = nullptr;
        }
    }
private:
    char *_brand;
    float _price;
};

void test()
{
	Point *pt1 = Singleton<Point>::getInstance(1, 2);
	Point *pt2 = Singleton<Point>::getInstance(11, 12);
	pt1->print();
	pt2->print();

	cout << "p1 = " << pt1 << endl;
	cout << "p2 = " << pt2 << endl;
}

#if 1
void test2()
{
	Computer *pc1 = Singleton<Computer>::getInstance("xiaomi", 6666);
	/* Computer *pc2 = Singleton<Computer>::getInstance("huawei", 8888); */
	pc1->print();
	/* pc2->print(); */

	cout << "pc1 = " << pc1 << endl;
		 /* << "pc2 = " << pc2 << endl; */
}
#endif
void test3()
{
	int *pt1 = Singleton<int>::getInstance();
	int *pt2 = Singleton<int>::getInstance();

	cout << "p1 = " << pt1 << endl;
	cout << "p2 = " << pt2 << endl;
}

void test4()
{
	double *pt1 = Singleton<double>::getInstance();
	double *pt2 = Singleton<double>::getInstance();

	cout << "p1 = " << pt1 << endl;
	cout << "p2 = " << pt2 << endl;
}
int main()
{
    test();
	return 0;
}

