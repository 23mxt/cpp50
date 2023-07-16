#include <string.h>
#include <iostream>

using std::cout;
using std::endl;

class String
{
public:
    String()
    : _pstr(nullptr)
    {
        cout << "String()" << endl;
    }

    String(const char *pstr)
    : _pstr(new char[strlen(pstr) + 1]())
    {
        cout << "String(const char *)" << endl;
        strcpy(_pstr, pstr);
    }

    //将拷贝构造函数与赋值运算符函数称为具有拷贝控制语义的函数
    //拷贝（复制）构造函数
    String(const String &rhs)
    : _pstr(new char[strlen(rhs._pstr) + 1]())
    {
        cout << "String(const String &)" << endl;
        strcpy(_pstr, rhs._pstr);
    }

    String &operator=(const String &rhs)
    {
        cout << "String &operator=(const String &)" << endl;

        if(this != &rhs)
        {
            delete [] _pstr;
            _pstr = nullptr;

            _pstr = new char[strlen(rhs._pstr) + 1]();
            strcpy(_pstr, rhs._pstr);
        }

        return *this;
    }

    //将移动构造函数与移动赋值运算符函数称为具有移动语义的函数
    //移动构造函数
    //String s1 = String("hello");
    String(String &&rhs)
    : _pstr(rhs._pstr)
    {
        cout << "String(String &&)" << endl;
        rhs._pstr = nullptr;
    }

    //移动赋值(运算符)函数
    //String &&rhs = std::move(s3);
    String &operator=(String &&rhs)
    {
        cout << "String &operator=(String &&)" << endl;

        if(this != &rhs)//1、自移动
        {
            delete [] _pstr;//2、释放左操作数
            _pstr = nullptr;

            _pstr = rhs._pstr;//3、浅拷贝
            rhs._pstr = nullptr;
        }

        return *this;//4、返回*this
    }

    ~String()
    {
        cout << "~String()" << endl;
        if(_pstr)
        {
            delete [] _pstr;
            _pstr = nullptr;
        }
    }

    friend std::ostream &operator<<(std::ostream &os, const String &rhs);
private:
    char *_pstr;
};

std::ostream &operator<<(std::ostream &os, const String &rhs)
{
    if(rhs._pstr)
    {
        os << rhs._pstr;
    }

    return os;
}

void test()
{
    String s1("hello");
    cout << "s1 = " << s1 << endl;

    cout << endl;
    String s2 = s1;
    cout << "s1 = " << s1 << endl;
    cout << "s2 = " << s2 << endl;

    cout << endl;
    //"world"，字符串常量，位于文字常量区，是左值
    //String("world"),String的临时对象，是右值
    //"world" ==> String("world")
    String s3 = "world";
    cout << "s3 = " << s3 << endl;

    cout << endl;
    s3 = s1;
    cout << "s1 = " << s1 << endl;
    cout << "s3 = " << s3 << endl;

    cout << endl;
    s3 = String("wangdao");
    cout << "s3 = " << s3 << endl;

    cout << endl << "s3 = std::move(s3) " << endl;
    /* String("wuhan") = String("wuhan");//ok */
    //std::move可以将左值转换成右值,并不能移动任何东西
    //底层就是做了强制转换，static_cast<T &&>(lvalue)
    /* &std::move(s3);//error */
    s3 = std::move(s3);
    cout << "s3 = " << s3 << endl;

    cout << endl;
    s1 = std::move(s2);
    cout << "s2 = " << s2 << endl;
}

int main(int argc, char *argv[])
{
    test();
    return 0;
}


