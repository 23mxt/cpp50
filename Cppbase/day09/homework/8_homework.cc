#include <stdlib.h>
#include <iostream>
using std::cout;
using std::endl;

//stdlib 
//atexit（进程结束时执行注册的函数func） + 饱汉模式（多线程安全）

class Singleton
{
public:
    static Singleton* getInstance()
    {
        if(_pInstance == nullptr)
        {
            _pInstance = new Singleton();
            atexit(destroy);
        }
        return _pInstance;
    }

    static void destroy() 
    {
            if(_pInstance)
            {
                delete _pInstance;
                _pInstance = nullptr;
            }
    }
private:
    Singleton()
    {
        cout << "Singleton" << endl;
    }
    ~Singleton()
    {
        cout << "~Singleton" << endl;
    }
private:
    static Singleton* _pInstance;
};
Singleton* Singleton::_pInstance = nullptr;

int main() {
    Singleton* sgl = Singleton::getInstance();
    return 0;
}

