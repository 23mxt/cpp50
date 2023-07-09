#include <iostream>
#include <limits>

using std::cout;
using std::endl;
using std::cin;
using std::cerr;

class Complex
{
public:
    Complex(double dreal = 0.0, double dimag = 0.0)
    : _dreal(dreal)
    , _dimag(dimag)
    {
        cout << "Complex(double = 0.0, double = 0.0)" << endl;
    }

    Complex &operator+=(const Complex &rhs)
    {
        cout << "Complex &operator+=(const Complex &)" << endl;
        _dreal += rhs._dreal;
        _dimag += rhs._dimag;

        return *this;
    }

    Complex &operator++()
    {
        cout << "Complex &operator++()" << endl;
        ++_dreal;
        ++_dimag;

        return *this;
    }

    Complex operator++(int)//int在此处只是起到标识作用，没有传参含义
    {
        cout << "Complex operator++(int)" << endl;
        Complex tmp(*this);
        _dreal++;
        _dimag++;

        return tmp;
    }

    void print() const
    {
        /* cout << _dreal << " + " << _dimag << "i" << endl; */
        if(0 == _dreal && 0 == _dimag)
        {
            cout << 0 << endl;
        }
        else if(0 == _dreal)
        {
            cout << _dimag << "i" << endl;
        }
        else
        {
            cout << _dreal;
            if(_dimag > 0)
            {
                cout << " + " << _dimag << "i" << endl;
            }
            else if(0 == _dimag)
            {
                cout << endl;
            }
            else
            {
                cout << " - " << (-1) *_dimag << "i" << endl;
            }
        }
    }

    double getReal() const
    {
        return _dreal;
    }

    double getImag() const
    {
        return _dimag;
    }

    ~Complex()
    {
        cout << "~Complex()" << endl;
    }

    //如果将输出流运算符函数以成员函数进行重载，那么形式上就会有
    //三个参数，所以需要将rhs去掉，但是会导致使用this指针指向对象
    //而this指针在非静态成员函数的第一个参数的位置，这样会改变
    //操作数的顺序，不满足运算符重载的规则,所以不建议使用成员函数
    //进行重载，但是又要访问私有成员，所以最终选择友元函数的形式
    /* std::ostream &operator<<(std::ostream &os); */
    friend std::ostream &operator<<(std::ostream &os, const Complex &rhs);
    friend std::istream &operator>>(std::istream &is, Complex &rhs);

    //友元函数
    friend Complex operator+(const Complex &lhs, const Complex &rhs);

private:
    double _dreal;
    double _dimag;
};

//3、运算符重载之友元函数的形式
Complex operator+(const Complex &lhs, const Complex &rhs)
{
    cout << "friend Complex operator+(const Complex &, const Complex &)" << endl;
    return Complex(lhs._dreal + rhs._dreal,
                   lhs._dimag + rhs._dimag);
}

//流对象不能复制或者赋值
std::ostream &operator<<(std::ostream &os, const Complex &rhs)
{
    cout << "std::ostream &operator<<(std::ostream &, const Complex &)" << endl;
    if(0 == rhs._dreal && 0 == rhs._dimag)
    {
        os << 0 << endl;
    }
    else if(0 == rhs._dreal)
    {
        os << rhs._dimag << "i" << endl;
    }
    else
    {
        os << rhs._dreal;
        if(rhs._dimag > 0)
        {
            os << " + " << rhs._dimag << "i" << endl;
        }
        else if(0 == rhs._dimag)
        {
            os << endl;
        }
        else
        {
            os << " - " << (-1) *rhs._dimag << "i" << endl;
        }
    }

    return os;
}

void readDouble(std::istream &is, double &number)
{
    while(is >> number, !is.eof())
    {
        if(is.bad())
        {
            cerr << "istream is bad" << endl;
            return;
        }
        else if(is.fail())
        {
            is.clear();//重置流的状态
            //清空缓冲区
            is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "pls input double data" << endl;
        }
        else
        {
            cout << "number = " << number << endl;
            break;
        }
    }
}

std::istream &operator>>(std::istream &is, Complex &rhs)
{
    cout << "istream &operator>>(std::istream &, Complex &)" << endl;
    /* is >> rhs._dreal >> rhs._dimag; */
    readDouble(is, rhs._dreal);
    readDouble(is, rhs._dimag);
    return is;
}

void test()
{
    Complex c1(1, -2);
    cout << "c1 = " << c1 << endl; //链式编程
    /* operator<<(cout, "c1 = "); */
    /* operator<<(operator<<(cout, "c1 = "), c1); */
    /* cout.operator<<(endl); */
    /* operator<<(operator<<(cout, "c1 = "), c1).operator<<(endl); */

    cout << endl;
    Complex c2;
    cin >> c2;
    cout << "c2 = " << c2 << endl; //链式编程

}

int main(int argc, char **argv)
{
    test();
    return 0;
}




