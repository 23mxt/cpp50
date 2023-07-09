#include <iostream>

using std::cout;
using std::endl;

//引用计数应该存在内存的哪个位置:
//1、栈区,error
//2、全局静态区,error，静态数据成员是被类中的所有对象共享的
//3、文字常量区,error，只读
//4、程序代码区,error，只读
//5、堆区,可以在堆区的任何位置，但是为了能更好获取，将其放在
//数据的前面

class String
{
public:
    String()
    {

    }

    //
    String(const String &rhs)
    : _pstr(rhs._pstr)
    {
        /* ++_RefCount; */
    }
private:
    char *_pstr;
    static int _RefCount;
};

void test()
{
    String s1;
    String s2 = s1;//2

    String s3;//1 error
}

int main(int argc, char **argv)
{
    test();
    return 0;
}


