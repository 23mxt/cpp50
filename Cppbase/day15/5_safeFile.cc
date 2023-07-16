#include <stdio.h>
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

class SafeFile
{
public:
    //1、在构造函数初始化资源（托管资源）
    SafeFile(FILE *fp)
    : _fp(fp)
    {
        cout << "SafeFile(FILE *)" << endl;
        if(_fp == nullptr)
        {
            cout << "_fp == nullptr" << endl;
        }
    }

    //4、提供若干访问资源的方法
    void write(const string &msg)
    {
        fwrite(msg.c_str(), 1, msg.size(), _fp);
    }

    //2、在析构函数中释放资源
    ~SafeFile()
    {
        cout << "~SafeFile()" << endl;
        if(_fp)
        {
            fclose(_fp);
            cout << "flcose(_fp)" << endl;
        }
    }

    SafeFile(const SafeFile &rhs) = delete;
    SafeFile &operator=(SafeFile &rhs) = delete;
private:
    FILE *_fp;
};

void test()
{
    string msg = "hello,world\n";
    SafeFile sf(fopen("wd.txt", "a+"));//sf是栈对象
    SafeFile sc(fopen("wc.txt", "a+"));//sf是栈对象
    sf.write(msg);
}

int main(int argc, char *argv[])
{
    test();
    return 0;
}


