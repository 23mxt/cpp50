#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

void test()
{
    string s1("hello");
    cout << "s1 = " << s1 << endl;
    printf("s1'saddress : %p\n", s1.c_str());

    cout << endl;
    string s2 = s1;
    cout << "s1 = " << s1 << endl;
    cout << "s2 = " << s2 << endl;
    printf("s1'saddress : %p\n", s1.c_str());
    printf("s2'saddress : %p\n", s2.c_str());

    cout << endl;
    string s3("world");
    cout << "s3 = " << s3 << endl;
    printf("s3'saddress : %p\n", s3.c_str());

    cout << endl;
    s3 = s1;
    cout << "s1 = " << s1 << endl;
    cout << "s2 = " << s2 << endl;
    cout << "s3 = " << s3 << endl;
    printf("s1'saddress : %p\n", s1.c_str());
    printf("s2'saddress : %p\n", s2.c_str());
    printf("s3'saddress : %p\n", s3.c_str());

    cout << endl << "对s3[0]执行写操作" << endl;
    s3[0] = 'H';
    cout << "s1 = " << s1 << endl;
    cout << "s2 = " << s2 << endl;
    cout << "s3 = " << s3 << endl;
    printf("s1'saddress : %p\n", s1.c_str());
    printf("s2'saddress : %p\n", s2.c_str());
    printf("s3'saddress : %p\n", s3.c_str());

    cout << "sizeof(s1) = " << sizeof(s1) << endl;
}

int main(int argc, char **argv)
{
    test();
    return 0;
}


