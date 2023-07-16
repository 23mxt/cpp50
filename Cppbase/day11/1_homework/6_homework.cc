#include <string.h>
#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;
using std::string;

class Person
{
public:
    Person(string name, int age)
    :_name(name)
     ,_age(age)
    {
        cout << "Person(string, int)" << endl;
    }

    void display()
    {
        cout << "Person's name: " << _name
            << "  Person's age: " << _age << endl;
    }

private:
    string _name;
    int _age;
};

class Empolyee
:public Person
{
public:
    Empolyee(string name, int age, string department, double salary)
    :Person(name, age)
    ,_department(department)
    ,_salary(salary)
    {
        cout << "Empolyee(string name, int age, string department, double salary)" << endl;
    }

    void display()
    {
        Person::display();
        cout << "Empolyee's department: " << _department
            << "  Empolyee's _salary: " << _salary << endl;
    }


    string _department;
    double _salary;
};

//计算平均工资
double averpay(vector<Empolyee> &empset)
{
    double totalpay = 0;
    for(int i = 0; i < 3; ++i)
    {
        totalpay += empset.at(i)._salary;   
    }

    return (totalpay / 3);
}

int main() {
    Empolyee emp1("xiaoming", 19, "sell", 5000);
    Empolyee emp2("xiaoqiang", 20, "takeout", 8000);
    Empolyee emp3("xiaohong", 20, "librian", 8000);

    emp1.display();
    emp2.display();
    emp3.display();

    
    vector<Empolyee> empset;
    empset.push_back(emp1);
    empset.push_back(emp2);
    empset.push_back(emp3);
    cout << "averpay is " << averpay(empset) << endl;
    return 0;
}

