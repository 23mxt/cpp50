#include <string.h>
#include <iostream>
using std::cout;
using std::endl;
using std::string;

class A
{
public:
     A() 
	{ 
		cout << "A's cons." << endl; 
	}
	

	virtual 
	~A() 
	{ 
		cout << "A's des." << endl; 
	}
	
	virtual 
	void f() 
	{ 
		cout<<"A's f()."<<endl; 
	}
	
	void g() 
	{ 
		f();
	}

};

class B 
: public A
{
public:
    B() 
	{ 
		f(); 
		cout << "B's cons." << endl; 
	}
	
	~B() 
	{ 
		cout << "B's des." << endl; 
	}

};

class C 
: public B
{
public:
	C() 
	{ 
		cout<<"C's cons."<<endl; 
	}

	~C()
	{ 
		cout<<"C's des."<<endl;
	}
	
	void f() 
	{ 
		cout<<"C's f()."<<endl; 
	}

};

int  main(void)
{  
	A *pa=new C();
    pa->g();
    //A's cons.
    //A's f().
    //B's cons.
    //C's cons.
    //C's f().
    //C's des.
    //B's des.
    //A's des.
    delete pa;
    
    return 0;

}

