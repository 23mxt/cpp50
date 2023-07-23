#include <string>
/* #include <vector> */
#include <iostream>

using std::cout;
using std::endl;
using std::string;
/* using std::vector; */

class Point
{
Point()
{

}

Point(int ix, int iy)
:_ix(ix)
,_iy(iy)
{
    cout << "Point(int, int)" << endl;
}

~Point()
{
    cout << "~Point()" << endl;
    //对象的析构函数不是用来对对象所在的堆空间进行释放
    //而是释放对象申请的堆空间
}
private:
    int _ix;
    int _iy;
};

//自己实现空间配置器
template<typename T>
struct Allocator
{
public:
    //容器要想正确实现，空间和对象的处理就要分开，容器本来只应该负责空间的管理，不应该擅自增删对象
    //内存开辟
    T* allocate(size_t size)
    {
        return (T*)malloc(sizeof(T) * size);
    }

    //内存释放
    void deallocate(T* p)
    {
        free(p);
    }

    //对象的构造函数
    void construct(void* p,const T &val)
    {
        new (p) T(val);
    }

    //对象的析构函数
    void destroy(T* p)
    {
        p->~T();
    }
};

//用空间配置器初始化，就能避免容器擅自操纵对象的问题
template<typename T,typename _Allocator = Allocator<T>>
class vector
{
public:
    //构造函数
    vector(int size = 10)
    {
        cout << "vector(int size = 10)" << endl;
        //开辟空间
        _first = _Alloc.allocate(10);
        _last = _first;
        _end = _first + size;
    }

    //析构函数
    ~vector()
    {
        //先回收空间内有效的元素所申请的堆空间
        for(T* p = _first; p != _last; ++p)
        {
            _Alloc.destroy(p);
        }
        //释放堆空间的元素
        for(T* p = _first; p != _last; ++p)
        {
            /* _Alloc.deallocate(p); */
            //new出来的要delete
            delete p;
        }
        //回收剩余空间
        for(T* p = _last; p != _end; ++p)
        {
            _Alloc.deallocate(p);
        }
        
        //把指针置为nullptr
        _first = _last = _end = nullptr;
        cout << "容器已经析构完毕" << endl;
    }

    
    //向容器尾部插入元素
    void push_back(const T &val)
    {
        if(full())
        {
            cout << "容器已满!" << endl;
            expand();
        }
        //用空间配置器实现元素的构造函数
        _Alloc.construct(_last, val);
        _last++;
        cout << "插入成功" << endl;
    }

    //在容器尾部删除元素
    void pop_back()
    {
        if(empty())
        {
            cout << "容器为空!" << endl;
            return;
        }
        //用空间配置器实现元素的析构函数
        //元素的析构函数并不会释放堆对象
        _Alloc.destroy(_last);
        _last--;//让指针后移 因为_last指向的是容器最后一个元素的下一个位置
        /* cout << *_last << endl; 析构后2这个堆对象所在的空间仍未被回收*/
        /* _Alloc.deallocate(_last); */
        cout << "删除成功" << endl;
    }

    //判满
    bool full()
    {
        return _last == _end;
    }
    //判空
    bool empty()
    {
        return _first == _last;
    }
    //求容器当前元素数量
    int size()
    {
        return _last - _first;
    }

    //扩容
    void expand()
    {
        cout << "vector扩容了" << endl;
        //先求出当前的大小，并求出扩容后空间的大小，申请对应的空间
        int newsize =  size() * 2;
        T* tmp = _Alloc.allocate(newsize);
        
        //将旧空间的元素移动到新空间
        for(int i = 0; i < size(); ++i)
        {
            tmp[i] = _first[i];
        }
    
        //将旧空间的元素销毁
        for(T* p = _first; p != _last; p++)
        {
            _Alloc.deallocate(p);
        }

        //释放旧空间
        _Alloc.deallocate(_first);
        //重设三个指针
        _first = tmp;
        _last = tmp + size();
        _end = tmp + newsize;
    }

private:
    T* _first;//指向容器的第一个元素
    T* _last;//指向容器的最后一个元素的后一个位置
    T* _end;//指向容器的尾后
    _Allocator _Alloc;
};

void test()
{
    vector<int>test;
    int * pa = new int(100);
    cout << "*pa = " << *pa << endl;
    test.push_back(*pa);
    test.push_back(2);
#if 0
    for(int i = 0; i < 15; ++i){
        test.push_back(2);
    }
#endif
    int ret = test.size();
    cout << "容器的容量为：" << ret << endl;
    test.pop_back();
    ret = test.size();
    cout << "容器的容量为：" << ret << endl;
    /* test.pop_back(); */
    /* ret = test.size(); */
    /* cout << "容器的容量为：" << ret << endl; */
}

int main() {
    test();
        cout << "end test 容器的析构时机" << endl;
    return 0;
}

