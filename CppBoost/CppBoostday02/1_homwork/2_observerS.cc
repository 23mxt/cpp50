#include <string>
#include <vector>
#include <list>
#include <iostream>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::list;

class Observer;

class Subject
{
public:
    virtual ~Subject() {}
    //只提供功能的接口，具体实现交给派生类，Subject是抽象基类
    //增加粉丝
    virtual void addattch(Observer *) = 0; 
    //减少粉丝
    virtual void deattch(Observer *) = 0;
    //通知粉丝当前状态
    virtual void notify() = 0;
private:
    int _status;
    list<Observer *> _obList;
};

class SubjectLdh
:public Subject
{
public:
    ~SubjectLdh() 
    {
        cout << "~SubjectLdh" << endl;
    }
    //增加粉丝
    virtual void addattch(Observer *) override;  //不知道observer的实现，这里没法实现该函数
    //减少粉丝
    virtual void deattch(Observer *) override;
    //通知粉丝当前状态
    virtual void notify() override;

    //设置状态
    void setStatus(const int state)
    {
        _status = state;
    }
    //获取状态
    int getStatus()
    {
        return _status;
    }
private:
    int _status;
    list<Observer *> _obList;
};

class Observer
{
public:
virtual ~Observer() {}
virtual void update(const int value) const = 0;    //更新信息后要做什么交给派生类
};

class ObserverA
:public Observer
{
public:
    //构造函数给姓名初始化
    ObserverA(const string &name)
    :_name(name)
    {
        cout << "ObserverA(const string &)" << endl;
    }

    //update函数具体实现
    void update(const int value) const
    {
        cout << "ObserverA name: " << _name << " getValue " << value << endl; 
    }

    //析构函数打印姓名
    ~ObserverA()
    {
        cout << "~ObserverA"<< endl;
    }
private:
    //姓名
    string _name;
};

    //增加粉丝
void SubjectLdh::addattch(Observer * obs) //不知道observer的实现，这里没法实现该函数
{
    if(obs)
    {
        _obList.push_back(obs);
    }
}
    //减少粉丝
void SubjectLdh::deattch(Observer * obs) 
{
    //找到要删的粉丝，remove
    //怎么一次删一大段?
    for(auto it =  _obList.begin(); it != _obList.end(); ++it)
    {
        if(*it == obs)
        {
            _obList.remove(*it);
            break;
        }
    }       
}

//通知粉丝当前状态
void SubjectLdh::notify() 
{
    for(auto &ob : _obList)
    {
        ob->update(_status);
    }
}

void test()
{

}

int main() {
    test();
    return 0;
}

