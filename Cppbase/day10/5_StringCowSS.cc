#include <string.h>
#include <iostream>

using std::cout;
using std::endl;

class BracketProxy;
class String
{
public:
    String()
    /* : _pstr(nullptr) */
    : _pstr(new char[5]() + 4)//多加的4个字节存放的是引用计数
    {
        cout << "String()" << endl;
        initRefcount();
    }

    //C
    String(const char *pstr)
    /* : _pstr(pstr)//erro */
    : _pstr(new char[strlen(pstr) + 5]() + 4)
    {
        cout << "String(const char *)" << endl;
        strcpy(_pstr, pstr);
        initRefcount();
    }

    //String s2 = s1;
    //拷贝构造 C++
    String(const String &rhs)
    : _pstr(rhs._pstr)
    {
        cout << "String(const String &)" << endl;
        increaRefcount();
    }

    //s2 = s1
    //赋值
    String &operator=(const String &rhs)
    {
        cout << "String &operator=(const String &)" << endl;
        if(this != &rhs)//1、自复制
        /* if(*this != rhs) 可重载 */
        {
            //2、释放左操作数
            decreRefcount();
            deleteRefcount();

            //3、浅拷贝
            _pstr = rhs._pstr;
            increaRefcount();
        }

        //4、返回*this
        return *this;
    }


private:
class BracketProxy
{
public:
    BracketProxy(String &self, size_t idx)
    :_self(self) //对不完全的类用拷贝构造，拷贝完会立马析构
    ,_idx(idx)
    {

    }
    
    //利用类型转换打印字符
    //不用重载<<运算符
    operator char()
    {
        return _self._pstr[_idx];
    }

    //重载=运算符
    char operator=(const char &rhs)
    {
        if(_idx < _self.size())
        {
            //说明在共享
            if(_self.getRefCount() > 1)
            {
                char* _newstr = new char[_self.size() + 5]() + 4;
                strcpy(_newstr, _self._pstr);//先复制一份新的
                _self.decreRefcount();
                _self._pstr = _newstr;
                _self.initRefcount();
            }

            //引用计数为1，直接改
            //真正修改
            _self._pstr[_idx] = rhs;
            return _self._pstr[_idx];
        }
        else
        {
            static char nullchar = '\0';
            return nullchar;
        }
    }
private:
    String &_self;//创建一个不完整的类，可以用引用声明
    size_t _idx;
};

public:
    //s3 = s2 = s1?
    //s3[0] = 'H'
    //因为要重载=，BracketProxy不能用右值
    BracketProxy operator[](size_t idx)
    {
        return BracketProxy(*this, idx);
    }
    //析构减计数
    ~String()
    {
        cout << "~String()" << endl;
        decreRefcount();
        deleteRefcount();
    }

    const char *c_str() const
    {
        return _pstr;
    }

    int getRefCount() const
    {
        return *(int *)(_pstr - 4);
    }

    void initRefcount() 
    {
        *(int *)(_pstr - 4) = 1;
    }

    void increaRefcount()
    {
        ++*(int *)(_pstr - 4);
    }

    void decreRefcount()
    {
        --*(int *)(_pstr - 4);
    }

    void deleteRefcount()
    {
        if(0 == *(int *)(_pstr - 4))
        {
            delete [] (_pstr - 4);
        }
    }
private:
    size_t size() const
    {
        return strlen(_pstr);
    }

    friend std::ostream &operator<<(std::ostream &os, const String &rhs);

private:
    char *_pstr;
};

std::ostream &operator<<(std::ostream &os, const String &rhs)
{
    //判空
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
    printf("s1's address：%p\n", s1.c_str());
    cout << "s1.getRefCount() = " << s1.getRefCount() << endl;

    cout << endl;
    String s2 = s1;
    /* String s2(s1); */
    cout << "s1 = " << s1 << endl;
    cout << "s2 = " << s2 << endl;
    printf("s1's address：%p\n", s1.c_str());
    printf("s2's address：%p\n", s2.c_str());
    cout << "s1.getRefCount() = " << s1.getRefCount() << endl;
    cout << "s2.getRefCount() = " << s2.getRefCount() << endl;

    cout << endl;
    String s3("world");
    cout << "s3 = " << s3 << endl;
    printf("s3's address：%p\n", s3.c_str());
    cout << "s3.getRefCount() = " << s3.getRefCount() << endl;

    cout << endl;
    s3 = s1;
    cout << "s1 = " << s1 << endl;
    cout << "s2 = " << s2 << endl;
    cout << "s3 = " << s3 << endl;
    printf("s1's address：%p\n", s1.c_str());
    printf("s2's address：%p\n", s2.c_str());
    printf("s3's address：%p\n", s3.c_str());
    cout << "s1.getRefCount() = " << s1.getRefCount() << endl;
    cout << "s2.getRefCount() = " << s2.getRefCount() << endl;
    cout << "s3.getRefCount() = " << s3.getRefCount() << endl;


    cout << endl << "对s3[0]执行读操作" << endl;
    cout << "s3[0] = " << s3[0] << endl;
    cout << "s1 = " << s1 << endl;
    cout << "s2 = " << s2 << endl;
    cout << "s3 = " << s3 << endl;
    printf("s1's address：%p\n", s1.c_str());
    printf("s2's address：%p\n", s2.c_str());
    printf("s3's address：%p\n", s3.c_str());
    cout << "s1.getRefCount() = " << s1.getRefCount() << endl;
    cout << "s2.getRefCount() = " << s2.getRefCount() << endl;
    cout << "s3.getRefCount() = " << s3.getRefCount() << endl;

    cout << endl << "对s3[0]执行写操作" << endl;
    s3[0] = 'H';
    cout << "s1 = " << s1 << endl;
    cout << "s2 = " << s2 << endl;
    cout << "s3 = " << s3 << endl;
    printf("s1's address：%p\n", s1.c_str());
    printf("s2's address：%p\n", s2.c_str());
    printf("s3's address：%p\n", s3.c_str());
    cout << "s1.getRefCount() = " << s1.getRefCount() << endl;
    cout << "s2.getRefCount() = " << s2.getRefCount() << endl;
    cout << "s5.getRefCount() = " << s3.getRefCount() << endl;
}

int main(int argc, char **argv)
{
    test();
    return 0;
}
