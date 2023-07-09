#include <string.h>
#include <iostream>
using std::cout;
using std::endl;
using std::string;

//内部类 + 静态数据成员
class Singleton
{
public:
    static Singleton* getInstance()
    {
        if(_pInstance == nullptr)
        {
            _pInstance = new Singleton();
        }
        return _pInstance;
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
    class AutoRealese
    {
    public:
        AutoRealese()
        {
            cout << "AutoRealese" << endl;
        }
        ~AutoRealese()
        {
            cout << "~AutoRealese" << endl;
            if(_pInstance)
            {
                delete _pInstance;
                _pInstance = nullptr;
            }
        }
    };
private:
    static Singleton* _pInstance;
    static AutoRealese _ar;
};
Singleton* Singleton::_pInstance = nullptr;
Singleton::AutoRealese Singleton::_ar;

int main() {
    Singleton* sgl = Singleton::getInstance();
    return 0;
}

