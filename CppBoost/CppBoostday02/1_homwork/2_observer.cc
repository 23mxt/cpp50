#include <string>
#include <memory>
#include <vector>
#include <map>
#include <list>
#include <unordered_map>
#include <iostream>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::list;
using std::map;
using std::unique_ptr;
using std::unordered_map;
class Observer;

class Subject
{
public:
   virtual ~Subject(){}
   virtual void attach(Observer *) = 0;
   virtual void detach(Observer *) = 0;
   virtual void notify() = 0;
};


class Subjectcxk
:public Subject
{
public:
    ~Subjectcxk()
    {
        cout << "~Subjectcxk" << endl;
    }

    //还不知道粉丝是什么样子，没法实现attach etc 
   virtual void attach(Observer *) ;

   virtual void detach(Observer *) ;

   virtual void notify() ;

   void setStatus(const int stat)
   {
        _status = stat;
   }

   int getStatus()
   {
        return _status;
   }
private:
   //存储粉丝列表
   list<Observer *> _list;
    int _status;
};

class Observer
{
public:
    virtual ~Observer() {}
    virtual void accept() = 0; //怎么接收新消息，怎么观察，交给具体实现
};

class ObserverA
:public Observer
{
public:
    ~ObserverA()
    {
        cout << "~ObserverA" << endl;
    }

    ObserverA(const string &name)
    :_name(name)
    {
        cout << "ObserverA(const string &)" << endl;
    }

    void accept(const int _value) 
    {
        cout << "Observer name" << _name << "getvalue" << _value << endl;
    }

private:
    string _name;
    int _value;
};

//添加新粉丝
void Subjectcxk::attach(Observer * obs) 
{
    _list.push_back(obs);//此处或许应该更新该粉丝的accept
}

//与旧粉丝断开链接
void Subjectcxk::detach(Observer * obs)
{
    _list.remove(obs);
}


//发布通知
void Subjectcxk::notify()
{
    for(auto &obs : _list)
    {
        obs->accept(_status);
    }
}

void test()
{
    unique_ptr<Subject> pcxk(new Subjectcxk());
    unique_ptr<Observer> pobs1(new ObserverA("lili"));
    unique_ptr<Observer> pobs2(new ObserverA("luck"));

    pcxk->setStatus(2);

    //绑定粉丝，通知
    pcxk->attach(pobs1);
    pcxk->attach(pobs2);
    pcxk->notify();

    

}

int main() {
    test();
    return 0;
}

