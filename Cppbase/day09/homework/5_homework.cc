#include <iostream>
#include <string.h>

using std::cin;
using std::cout;
using std::endl;
using std::string;

//实现以下String类的各个函数，并给出相应的测试用例
class String
{
public:
	String()
    {
        cout << "String" << endl;
    }

    //C
	String(const char * cstr)
    {
        cout << "String(const char *)" << endl;
        if(cstr == nullptr)
        {
            _pstr = new char[1];
            *_pstr = '\0';
        }
        else
        {
            _pstr = new char[strlen(cstr)+1](); 
            strcpy(_pstr, cstr);
        }
    }

	
    //C++
    String(const String &str)
    {
        cout << "String(const String&)" << endl;
        _pstr = new char[str.size()+1]();
        strcpy(_pstr, str.c_str());
    }
	
    ~String()
    {
        cout << "~String" << endl;
        /* if(_pstr != nullptr) */
        /* { */
        /*     delete  [] _pstr; */
        /*     _pstr = nullptr; */
        /* } */
    }

    //C++
	String &operator=(const String &rhs)
    {
        cout << "String& operator=(const String &)" << endl;
        this->_pstr = rhs._pstr;
        return (*this);
    }
	//C
    String &operator=(const char *cstr)
    {
        cout << "String& operator=(const char *)" << endl;
            _pstr = new char[strlen(cstr)+1](); 
            strcpy(_pstr, cstr);
            return *this;
    }


	String &operator+=(const String &rhs)
    {
        strcat(this->_pstr, rhs._pstr);
        return *this;
    }
    String &operator+=(const char *rhs)
    {
        strcat(this->_pstr, rhs);
        return *this;
    }

	char &operator[](std::size_t index)
    {
        return _pstr[index];
    }

    //和上一个的区别,基本没有
	const char &operator[](std::size_t index) const
    {
        return _pstr[index];
    }

    //String的底层就是cstr，char *
	std::size_t size() const
    {
        return strlen(this->_pstr);
    }

	const char* c_str() const
    {
        return _pstr;
    }

    //不改变本身的二元运算符，用友元函数进行重载
	friend bool operator==(const String &, const String &);
	friend bool operator!=(const String &, const String &);

	friend bool operator<(const String &, const String &);
	friend bool operator>(const String &, const String &);
	friend bool operator<=(const String &, const String &);
	friend bool operator>=(const String &, const String &);

	friend std::ostream &operator<<(std::ostream &os, const String &s);
	friend std::istream &operator>>(std::istream &is, String &s);
    

private:
	char * _pstr;
};

//-------------------字符串拼接----------------------------
String operator+(const String &lhs, const String &rhs)
{
    cout << "String operator+(const String &, const String &)" << endl;
    char* lhs_cp = new char[strlen(lhs.c_str())+strlen(rhs.c_str())+1]();
    char* rhs_cp = new char[strlen(rhs.c_str())+1]();
    strcat(lhs_cp, lhs.c_str());
    strcat(rhs_cp, rhs.c_str());
    strcat(lhs_cp, rhs_cp);
    
    String strtmp(lhs_cp);
    return strtmp;
}

String operator+(const String &lhs, const char *rhs)
{
    cout << "String operator+(const String &, const char*)" << endl;
    char* lhs_cp = new char[strlen(lhs.c_str())+strlen(rhs)+1]();
    char* rhs_cp = new char[strlen(rhs)+1]();
    strcat(lhs_cp, lhs.c_str());
    strcat(rhs_cp, rhs);
    strcat(lhs_cp, rhs_cp);
    
    String strtmp(lhs_cp);
    return strtmp;

}

String operator+(const char *lhs, const String &rhs)
{
    cout << "String operator+(const char*, const String &)" << endl;
    char* lhs_cp = new char[strlen(lhs)+strlen(rhs.c_str())+1]();
    char* rhs_cp = new char[strlen(rhs.c_str())+1]();
    strcat(lhs_cp, lhs);
    strcat(rhs_cp, rhs.c_str());
    strcat(lhs_cp, rhs_cp);
    
    String strtmp(lhs_cp);
    return strtmp;

}


//--------------------字符串比较---------------------------
bool operator==(const String &lhs, const String &rhs)
{
    if(strcmp(lhs._pstr, rhs._pstr) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool operator!=(const String &lhs, const String &rhs)
{
    if(strcmp(lhs._pstr, rhs._pstr) != 0)
    {
        return true;
    }
    else
    {
        return false;
    }

}

//lhs < rhs 
bool operator<(const String &lhs, const String &rhs)
{
    if(strcmp(lhs._pstr, rhs._pstr) < 0)
    {
        return true;
    }
    else
    {
        return false;
    }
    
}

//lhs > rhs 
bool operator>(const String &lhs, const String &rhs)
{
    if(strcmp(lhs._pstr, rhs._pstr) > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//lhs <= rhs 
bool operator<=(const String &lhs, const String &rhs)
{
    if(strcmp(lhs._pstr, rhs._pstr) == 0)
    {
        return true;
    }

    if(strcmp(lhs._pstr, rhs._pstr) < 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//lhs >= rhs 
bool operator>=(const String &lhs, const String &rhs)
{
    if(strcmp(lhs._pstr, rhs._pstr) == 0)
    {
        return true;
    }

    if(strcmp(lhs._pstr, rhs._pstr) > 0)
    {
        return true;
    }
    else
    {
        return false;
    }

}
//-------------------------<<----------------------------

std::ostream& operator<<(std::ostream &os, const String &s)
{
    if(s._pstr != nullptr)
    {
    os << s._pstr;
    }
    return os;
}

//------------------------->>----------------------------
std::istream &operator>>(std::istream &is, String &s)
{
    is >> s._pstr;

    return is;
}
//------------------------test-------------------------------
void test0()
{
    String s1;
    String s2("hello");
    cout << "s2=" << s2 << endl;
    
    String s3(s2);
    cout << "s3=" << s3 << endl;

    String s4;
    s4 = s3;
    cout << "s4=" << s4 << endl;

    String s5;
    s5 = "world";
    cout << "s5=" << s5 << endl;

    cout << "--------字符串拼接----------------" << endl;
    s2 += s5;
    cout << "s2=" << s2 << endl;

    s3 += "world";
    cout << "s3=" << s3 << endl;

    cout << "--------字符串读取----------------" << endl;
    cout << "s3[0]" << s3[0] << endl;
    cout << "s3[1]" << s3[1] << endl;

    cout << "--------字符串比较----------------" << endl;
    if(s4 == s2)
    {
        cout << "s4 == s2" << endl;
    }
    else
    {
        cout << "s4 != s2" << endl;
    }

    if(s5 != s2)
    {
        cout << "s5 != s2" << endl;
    }
    else
    {
        cout << "s5 == s2" << endl;
    }

    if(s5 > s2)
    {
        cout << "s5 > s2" << endl;
    }
    else
    {
        cout << "s5 <= s2" << endl;
    }

    if(s5 >= s2)
    {
        cout << "s5 >= s2" << endl;
    }
    else
    {
        cout << "s5 < s2" << endl;
    }

    if(s4 <= s5)
    {
        cout << "s4 <= s5" << endl;
    }
    else
    {
        cout << "s5 > s4" << endl;
    }

    cout << "--------字符串用+拼接----------------" << endl;
    String s6;
    s6 = (s2 + s5);
    cout << "s6 = " << s6 << endl;

    String s7;
    s7 = (s6 + "hellowuhan");
    cout << "s7 = " << s7 << endl;

    String s8;
    s8 = ("hellowangdao" + s2);
    cout << "s8 = " << s8 << endl;

    cout << "--------字符串输入流----------------" << endl;
    String s9;
    cin >> s9;
    cout << "s9 = " << s9 << endl;

}


int main()
{
    test0();

    return 0;
}
