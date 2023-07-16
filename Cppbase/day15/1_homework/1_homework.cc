#include <string.h>
#include <iostream>
using std::cout;
using std::endl;
using std::string;
using std::ostream;

class String
{
public:
    String(const char* pstr)
    :_pstr(new char[strlen(pstr)+1]())
    {
        cout << "String(const char*)" << endl;
        strcpy(_pstr, pstr);
    }
    
    //移动构造
    String(String &&rhs)
    {
        cout << "String(String &&)" << endl;
        _pstr = rhs._pstr;
        rhs._pstr = nullptr;
    }
    
    //移动赋值运算符
    String &operator=(String &&rhs)
    {
        cout << "String& operator=(String &&)" << endl;
        if(this != &rhs) //自移动
        {
            delete [] _pstr;//释放左操作数
            _pstr = nullptr;

            _pstr = rhs._pstr;//浅拷贝
            rhs._pstr = nullptr;
        }
        return *this;
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

friend ostream &operator<<(ostream& os, const String &rhs);
private:
    char* _pstr;
};

ostream &operator<<(ostream& os, const String &rhs)
{
    if(rhs._pstr)
    {
        os << rhs._pstr;
    }

    os << endl;
    return os;
}

void test()
{
    String s1("hello");
    cout << "s1 = " << s1 << endl;

    String s2("world");
    cout << "s2 = " << s2 << endl;
    /* s2 = "hello"; */
    s2 = std::move(s1);
    cout << "s1 = " << s1 << endl;
    cout << "s2 = " << s2 << endl;
}

int main() {
    test();
    return 0;
}

