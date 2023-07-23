#include <string.h>
#include <iostream>
using std::cout;
using std::endl;
using std::string;

template <typename... Args>
void print(Args... args)
{
    cour << "sizeof...(Args) = " << sizeof...(Args) << endl;
    cour << "sizeof...(args) = " << sizeof...(args) << endl;
}

void print() const 
{

}

void test0()
{
    string s1 = "hello";


}

int main() {

    return 0;
}

