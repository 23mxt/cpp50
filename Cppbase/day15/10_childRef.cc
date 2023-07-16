#include <iostream>
#include <memory>

using std::cout;
using std::endl;
using std::shared_ptr;

class Child;//前向声明

class Parent
{
public:
    Parent()
    {
        cout << "Parent()" << endl;
    }

    ~Parent()
    {
        cout << "~Parent()" << endl;
    }

    shared_ptr<Child> spChild;
};

class Child
{
public:
    Child()
    {
        cout << "Child()" << endl;
    }

    ~Child()
    {
        cout << "~Child()" << endl;
    }

    shared_ptr<Parent> spParent;
};

void test()
{
    shared_ptr<Parent> parentPtr(new Parent());//parentPtr栈对象
    shared_ptr<Child> childPtr(new Child());//childPtr栈对象
    cout << "parentPtr.use_count() = " << parentPtr.use_count() << endl;
    cout << "childPtr.use_count() = " << childPtr.use_count() << endl;

    parentPtr->spChild = childPtr;//sp = sp
    childPtr->spParent = parentPtr;//sp = sp
    cout << "parentPtr.use_count() = " << parentPtr.use_count() << endl;
    cout << "childPtr.use_count() = " << childPtr.use_count() << endl;
}

int main(int argc, char *argv[])
{
    test();
    return 0;
}


