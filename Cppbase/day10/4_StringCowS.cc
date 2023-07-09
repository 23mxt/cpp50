#include <string.h>
#include <iostream>

using std::cout;
using std::endl;

class String
{
public:
    String()
    /* : _pstr(nullptr) */
    : _pstr(new char[5]() + 4)//多加的4个字节存放的是引用计数
    {
        cout << "String()" << endl;
        *(int *)(_pstr - 4) = 1;
    }

    //C
    String(const char *pstr)
    /* : _pstr(pstr)//erro */
    : _pstr(new char[strlen(pstr) + 5]() + 4)
    {
        cout << "String(const char *)" << endl;
        strcpy(_pstr, pstr);
        *(int *)(_pstr - 4) = 1;
    }

    //String s2 = s1;
    //拷贝构造 C++
    String(const String &rhs)
    : _pstr(rhs._pstr)
    {
        cout << "String(const String &)" << endl;
        ++*(int *)(_pstr - 4);//是不是应为1？
    }

    //s2 = s1
    //赋值
    String &operator=(const String &rhs)
    {
        cout << "String &operator=(const String &)" << endl;
        if(this != &rhs)//1、自复制
        /* if(*this != rhs) */
        {
            //2、释放左操作数
            --*(int *)(_pstr - 4);
            if(0 == *(int *)(_pstr - 4))
            {
                delete [] (_pstr - 4);
            }

            //3、浅拷贝
            _pstr = rhs._pstr;//这步会把之前的4B拷贝过来?浅拷贝的是指针
            ++*(int *)(_pstr - 4);
        }

        //4、返回*this
        return *this;
    }

    //s3 = s2 = s1?
    //s3[0] = 'H'
    char &operator[](size_t idx)
    {
        if(idx < size())
        {
            //表明是共享的
            if(getRefCount() > 1)
            {
                //有问题，不管读写，直接深拷贝
                char *ptmp = new char[size() + 5]() + 4;
                strcpy(ptmp, _pstr);
                --*(int *)(_pstr - 4);
                _pstr = ptmp;
                *(int *)(_pstr - 4) = 1;
            }

            return _pstr[idx];
        }
        else
        {
            static char nullchar = '\0';
            return nullchar;
        }
    }

    //析构减计数
    ~String()
    {
        cout << "~String()" << endl;
        --*(int *)(_pstr - 4);
        if(0 == *(int *)(_pstr - 4))
        {
            delete [] (_pstr - 4);
        }
    }

    const char *c_str() const
    {
        return _pstr;
    }

    int getRefCount() const
    {
        return *(int *)(_pstr - 4);
    }

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
    cout << "s3.getRefCount() = " << s3.getRefCount() << endl;
}

int main(int argc, char **argv)
{
    test();
    return 0;
}


