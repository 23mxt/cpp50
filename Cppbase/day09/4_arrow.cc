#include <iostream>

using std::cout;
using std::endl;

class Data
{
public:
    Data(int data = 0)
    : _data(data)
    {
        cout << "Data(int = 0)" << endl;
    }

    int getData() const
    {
        return _data;
    }

    ~Data()
    {
        cout << "~Data()" << endl;
    }

private:
    int _data;
};

class SecondLayer
{
public:
    SecondLayer(Data *pdata)
    : _pdata(pdata)
    {
        cout << "SecondLayer(Data *)" << endl;
    }

    Data *operator->()
    {
        return _pdata;
    }

    Data &operator*()
    {
        return *_pdata;
    }

    ~SecondLayer()
    {
        cout << "~SecondLayer()" << endl;
        if(_pdata)
        {
            delete _pdata;
            _pdata = nullptr;
        }
    }
private:
    Data *_pdata;
};

class ThirdLayer
{
public:
    ThirdLayer(SecondLayer *psl)
    : _psl(psl)
    {
        cout << "ThirdLayer(SecondLayer *)" << endl;
    }

    SecondLayer &operator->()
    {
        return *_psl;
    }

    ~ThirdLayer()
    {
        cout << "~ThirdLayer()" << endl;
        if(_psl)
        {
            delete _psl;
            _psl = nullptr;
        }
    }
private:
    SecondLayer *_psl;
};

void test()
{
    //sl虽然不是指针，但是具备指针的功能，同时可以托管堆空间，
    //但是不同管空间的回收，将其称为智能指针
    //利用了栈对象的生命周期管理资源
    SecondLayer sl(new Data(10));//sl是栈对象
    /* sl.operator->()->getData(); */
    cout << "sl->getData() = " << sl->getData() << endl;
    /* sl.operator*().getData(); */
    cout << "(*sl).getData() = " << (*sl).getData() << endl;

    /* ThirdLayer tl(new SecondLayer(new Data(20)));//tl也是栈对象 */
    /* tl.operator->().operator->()->getData(); */
    /* cout << "tl->getData() = " << tl->getData() << endl; */
}

int main(int argc, char **argv)
{
    test();
    return 0;
}


