#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <iostream>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::map;
using std::unordered_map;

//先实现抽象的产品类
class Product
{
public:
    virtual void show() = 0;    //纯虚函数实现抽象类
    virtual ~Product() {};  //虚析构函数防止内存泄露
};

class ProductA
:public Product
{
public:
    ProductA()
    {
        cout << "ProductA" << endl;
    }

    virtual void show()
    {
        cout << "ProductA::show()" << endl;
    }

    virtual ~ProductA() 
    {
        cout << "~ProductA" << endl;
    }
};


class ProductB
:public Product
{
public:
    ProductB()
    {
        cout << "ProductB" << endl;
    }

    virtual void show()
    {
        cout << "ProductB::show()" << endl;
    }

    virtual ~ProductB() 
    {
        cout << "~ProductB" << endl;
    }
};

//实现工厂类
class Factory
{
public:
   virtual Product *createProduct() = 0;
   virtual ~Factory() {};
};

class FactoryA
:public Factory 
{
public:
    FactoryA()
    {
        cout << "FactoryA" << endl;
    }

    virtual Product *createProduct()
    {
        return new ProductA();
    }

   ~FactoryA()
   {
        cout << "~FactoryA" << endl;
   }
};

class FactoryB
:public Factory 
{
public:
    FactoryB()
    {
        cout << "FactoryB" << endl;
    }

    virtual Product *createProduct()
    {
        return new ProductB();
    }

   ~FactoryB()
   {
        cout << "~FactoryB" << endl;
   }
};

//每类产品都交由一个专门的工厂，展示结果
void func(Factory *fac)
{
    cout << "show A or B?" << endl;
    fac->createProduct()->show();
}

void test()
{
    FactoryA facA;
    FactoryB facB;
    
    func(&facA);
    func(&facB);
}

int main() {
    test();
    return 0;
}

