#include <iostream>

using std::cout;
using std::endl;

class Base
{
public:
    virtual 
    void print(int x)
    {
        cout << "Base::print" << endl;
    }
};


class Derived
: public Base
{
public:
    virtual 
    void print(int y)
    {
        cout << "Derived::print" << endl;
    }
};

int main(int argc, char *argv[])
{
    Derived derived;
    Base* pbase = &derived;
    pbase->print(10);
    return 0;
}


