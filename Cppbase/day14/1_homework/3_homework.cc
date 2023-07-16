#include <string.h>
#include <iostream>
using std::cout;
using std::endl;
using std::string;

class Base
{
public:
	Base(int i) 
	{
		b = i;
	}
    Base():b(0){}
    virtual void Print()
    {	cout << "Base 's Print() called." << endl;}
protected:
	int b;
};

class Derived1
:public Base
{
public:
	void Print()
	{
		cout<<"Derive1's Print() called."<<endl;
	}
};

class Derived2
:public Base
{
public:
    void Print()
    {
        cout << "Derive2's Print() called. "<< endl;
    }
};

//Base  * obj
void fun(Base * obj)
{      
	obj->Print();
}

int main(void)
{ 
	/* (5)　　　 */
    Derived1 d1;
    Derived2 d2;
    Base* pbase1 = &d1;
    Base* pbase2 = &d2;
    fun(pbase1);
    fun(pbase2);
	return 0;
}
/* 程序的执行结果如下： */
/* Derive1's Print() called. */
/* Derive2's Print() called. */
