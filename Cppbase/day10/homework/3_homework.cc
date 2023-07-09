#include <string.h>
#include <iostream>
using std::cout;
using std::endl;
using std::string;

class String
{
public:
    String()
    :_pstr(new char[5]() + 4)
    {
        cout << "String()" << endl;
        initRefcount();
    }

    //C拷贝构造
    String(const char* cstr)
    {
        cout << "String(const char *)" << endl;
        if(cstr == nullptr)
        {
            _pstr = new char[5]();
            _pstr[4] = '\0';
            initRefcount();
        }
        else
        {
            _pstr = new char[strlen(cstr) + 5]() + 4;
            strcpy(_pstr, cstr);
            initRefcount();
        }
    }

    //C++拷贝构造
    String(const String &rhs)
    {
        cout << "String(const String &)" << endl;
        _pstr = new char[strlen(rhs._pstr) + 5]() + 4;
        _pstr = rhs._pstr;
        increaRefcount();
    }

    //C
    /* String &operator=(const char* cstr) */
    /* { */
    /*      strcpy(_pstr, cstr); */
    /*      ++*(int *)(_pstr - 4); */
    /* } */

    //C++
    String &operator=(const String &rhs)
    {
        cout << "String &operator=(const String &)" << endl;
        //1、自复制
        if(this != &rhs)
        {
            //2、释放左操作数
            deleteRefcount();
            
            //3、浅拷贝
            _pstr = new char[rhs.size() + 5]() + 4;
            _pstr = rhs._pstr;
            increaRefcount();
        }

        return *this;
    }
    

    //重载[]
    char &operator[](size_t idx)
    {
        if(idx < this->size())
        {
            //不分读写
            class delim dl;
            dl.operator<<(idx);
        }
        else
        {
            static char nullchar = '\0';
            return nullchar;
        
        }

    }

private:
class delim
{
public:
    char &operator<<(const size_t idx)
    {
        return _pstr(idx);
    }       

};

public:
    const char* c_str() const 
    {
        return _pstr;
    }
    
    ~String()
    {
        cout << "~String()" << endl;
        deleteRefcount();
    }

    void initRefcount()
    {
        *(int *)(_pstr - 4) = 1;
    }

    int getRefcount()
    {
        return *(int *)(_pstr -4);
    }
    void increaRefcount()
    {
        ++*(int *)(_pstr -4);
    }
    void decreatRefcount()
    {
        --*(int *)(_pstr -4);
    }
    void deleteRefcount()
    {
        --*(int *)(_pstr - 4);
        if(*(int *)(_pstr - 4) == 0)
        {
            delete [] (_pstr - 4);
            _pstr = nullptr;
        }
    }
private:
    size_t size() const
    {
        return strlen(_pstr);
    }


    //重载输出流运算符
    friend std::ostream &operator<<(std::ostream &os, const String &rhs);
private:
    char* _pstr;
};

std::ostream &operator<<(std::ostream &os, const String &rhs)
{
    cout << "operator<<" << endl;
    if(rhs._pstr != nullptr)
    {
        os << rhs._pstr;
    }
    return os;
}

void test0()
{
    String s1("hello");
    cout << "s1 = " << s1 << endl;
    cout << "s1's Refcount = " << s1.getRefcount() << endl;
    printf("s1's address :%p\n", s1.c_str());

    String s2(s1);
    cout << "s2 = " << s2 << endl;
    cout << "s1's Refcount = " << s1.getRefcount() << endl;
    cout << "s2's Refcount = " << s2.getRefcount() << endl;
    printf("s1's address :%p\n", s1.c_str());
    printf("s2's address :%p\n", s2.c_str());

    String s3("world");
    cout << "s3 = " << s3 << endl;
    printf("s1's address :%p\n", s1.c_str());
    printf("s2's address :%p\n", s2.c_str());
    printf("s3's address :%p\n", s3.c_str());
    cout << "s1's Refcount = " << s1.getRefcount() << endl;
    cout << "s2's Refcount = " << s2.getRefcount() << endl;
    cout << "s3's Refcount = " << s3.getRefcount() << endl;
    
    s3 = s1;
    cout << "s3 = " << s3 << endl;
    cout << "s1's Refcount = " << s1.getRefcount() << endl;
    cout << "s2's Refcount = " << s2.getRefcount() << endl;
    cout << "s3's Refcount = " << s3.getRefcount() << endl;
    printf("s1's address :%p\n", s1.c_str());
    printf("s2's address :%p\n", s2.c_str());
    printf("s3's address :%p\n", s3.c_str());

}

int main() {
    test0();
    return 0;
}

