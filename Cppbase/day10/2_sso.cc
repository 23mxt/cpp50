#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

void test()
{
    int *pInt = new int(10);
    string s1 = "hello";
    string s2 = "wuhanwangdaohub";
    /* string s3 = "welcometowuhanwangdao"; */
    string s3 = "wuhanwangdaohubt";

    cout << "s1 = " << s1 << endl;
    cout << "s2 = " << s2 << endl;
    cout << "s3 = " << s3 << endl;
    printf("s1'saddress : %p\n", s1.c_str());
    printf("s2'saddress : %p\n", s2.c_str());
    printf("s3'saddress : %p\n", s3.c_str());
    printf("pInt's address : %p\n", &pInt);
    printf("pInt's  Pointer address : %p\n", pInt);


    delete pInt;
}

int main(int argc, char **argv)
{
    test();
    return 0;
}


