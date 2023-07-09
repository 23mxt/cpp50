#include <string.h>
#include <iostream>
using std::cout;
using std::endl;
using std::string;

class String
{
public:
    //无参构造
	String()
    {
         _pstr = "";
        cout << "String" << endl;
    }

    //有参构造
	String(const char *pstr)
    :_pstr(new char[strlen(pstr)+1]())
    {
        strcpy(_pstr, pstr);
        cout << "String(const char*)" << endl;
    }

	String(const String &rhs)
    :_pstr(new char[strlen(rhs._pstr)+1]())
    {
        strcpy(_pstr, rhs._pstr);
        cout << "String(const String &)" << endl;
    }

    //重载赋值运算符函数
	String &operator=(const String &rhs)
    {
        //自拷贝
        if(this != &rhs) {
            //释放原来的空间
            delete [] this->_pstr;
            this->_pstr = nullptr;
            //申请新的空间并拷贝
            _pstr = new char[strlen(rhs._pstr)+1]();
            strcpy(_pstr, rhs._pstr);
        }
        cout << "String &operator=(const String &)" << endl;
        return *this;
    }
	
    /* void destroy() */
    /* { */
    /*     if(this->_pstr != nullptr) { */
    /*         delete this; */
    /*         this->_pstr = nullptr; */
    /*     } */
    /* } */
    ~String()
    {
        if(_pstr != nullptr) {
            delete [] _pstr;
            _pstr = nullptr;
        }
        cout << "~String" << endl;
    }

	void print()
    {
        cout << _pstr << endl;
    }

    size_t length() const;
    const char * c_str() const;

private:
	char * _pstr;
};

int main()
{
	String str1;
	str1.print();
	

	String str2 = "Hello,world";
	String str3("wangdao");
	
	str2.print();		
	str3.print();	
	
	String str4 = str3;
	str4.print();
	
	str4 = str2;
	str4.print();
	
	return 0;
}

