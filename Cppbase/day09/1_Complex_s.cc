#include <string.h>
#include <iostream>
using std::cout;
using std::endl;
using std::string;

class Complex
{
public:
    Complex(double dreal = 0.0, double dimg = 0.0)
    :_dreal(dreal)
    ,_dimg(dimg)
    {
        cout << "Complex(double, double)" << endl;
    }

    //重载+=运算符
    Complex& operator+=(const Complex& rhs)
    {
        cout << "operator+=(const Complex&)" << endl;
        _dreal += rhs._dreal;
        _dimg += rhs._dimg;
        return *this;
    }

    //重载前置++
    Complex& operator++()
    {
        cout << "operator++" << endl;
        ++_dreal;
        ++_dimg;
        return *this; 
    }

    //重载后置++
    Complex operator++(int)
    {
        cout << "operator++(int)" << endl;
        Complex tmp(*this);
        _dreal++;
        _dimg++;
        return tmp;
    }
    //重载输入输出流运算符，打印信息
    
    ~Complex()
    {
        cout << "~Complex()" << endl;
    }
private:
    double _dreal;
    double _dimg;
};

void test()
{
    Complex c1(1, 2);
    //test
    /* c1 += (1,2); */
    (++c1);
    (c1++);

}

int main() {
    test();
    return 0;
}

