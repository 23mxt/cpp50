#include <stdlib.h>
#include <pthread.h>
#include <iostream>
using std::cout;
using std::endl;

//stdlib 
//atexit（进程结束时执行注册的函数func） + 饱汉模式（多线程安全）
//pthread.h 只有linux下可用
//pthread_once  

class Singleton
{
public:
    static Singleton* getInstance()
    {
        pthread_once(&once, init);
        return _pInstance;
    }

    static void init()
    {
        if(_pInstance == nullptr)
        {
            _pInstance = new Singleton();
            atexit(destroy);
        }
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
    static pthread_once_t once;
};
Singleton* Singleton::_pInstance = nullptr;
//静态成员要在类外初始化
pthread_once_t Singleton::once;

int main() {
    cout << "beg main" << endl;
    Singleton* sgl = Singleton::getInstance();
    cout << "end main" << endl;
    return 0;
}

