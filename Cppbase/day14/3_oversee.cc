#include <iostream>

using std::cout;
using std::endl;

class Base
{
public:
    Base(int number = 0)
    : _number(number)
    {

    }

    virtual
    void print()
    {
        cout << "Base::_number = " << _number << endl;
    }

protected:
    int _number;
};


class Derived
: public Base
{
public:
    Derived(int number1 = 0, int number2 = 0)
    : Base(number1)
    , _number(number2)
    {

    }

    //函数名相同，不管是不是虚函数，隐藏
    void print(int value)
    /* void print() */
    {
        cout << "Derived::print()" << endl;
        /* cout << "value = " << value << endl; */
        cout << "_number = " << Base::_number << endl;
        cout << "_number = " << _number << endl;
    }
protected:
    int _number;
};
int main(int argc, char *argv[])
{
    Derived d(10, 20);
    d.print(100);
    Base* pbase = &d;
    pbase->print();//即便隐藏，不会触发多态，虚函数才会触发多态
    /* d.Base::print();//破解隐藏，类名+作用域限定符 */
    /* d.print(); */
    return 0;
}


