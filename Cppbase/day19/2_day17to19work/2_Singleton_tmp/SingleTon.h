#ifndef __WD_TEMPLATE_SINGLETON_H__
#define __WD_TEMPLATE_SINGLETON_H__

#include <iostream>
using std::cout;
using std::endl;

#if 0
class Singleton
{
public:
    static Point *getInstance(int ix, int iy)
    {
        if(nullptr == _pInstance)
        {
            _pInstance = new Point(ix, iy);
            _ar;//为了在模板参数推导时创建ar对象
        }
        return _pInstance;

    }
};
#endif

template <class T>
class Singleton
{
public:
    template <class... Args>
        static T *getInstance(Args... args)
        {
            if(nullptr == _pInstance)
            {
                cout << "create _pInstance" << endl;
                _pInstance = new T(args...);
                _ar;//为了在模板参数推导时创建ar对象
                /* cout << "getInstance" << &_ar << endl; */
            }
            return _pInstance;
        }

private:
    class AutoRelease
    {
    public:
        AutoRelease()
        {
            cout << "AutoRelease(times)" << endl;
            /* cout  << &_ar << endl; */
        }

        ~AutoRelease()
        {
            cout << "~AutoRelease()" << endl;
            if(_pInstance)
            {
                cout << "delete _pInstance" << endl;
                delete _pInstance;
                _pInstance = nullptr;
            }
        }
    };
private:
    Singleton()
    {
        cout << "Singleton()" << endl;
        _ar;
    }

    ~Singleton()
    {
        cout << "~Singleton()" << endl;
    }

private:
    static T *_pInstance;
    static AutoRelease _ar;
};

//相比较原本单例模式通过内部类＋静态成员的方式，加了一个类模板和函数模板
//类模板用来定义参数化的类
//函数模板用来定义参数化的函数
/* template <class T> */
/* T * Singleton<T>::_pInstance = nullptr; */

/* template <class T> */
/* typename Singleton<T>::AutoRelease Singleton<T>::_ar;//typename表名是一个类型 */

#endif

