#include <iostream>
#include <memory>
#include <cstring>

using std::cout;
using std::endl;
using std::allocator;

class Point
{
public:
Point() {}

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

int getX()
{
    return _ix;
}

private:
    int _ix;
    int _iy;
};

//Vector接口 
template<typename T> 
class Vector 
{ 
public:     
    Vector(int size = 0);     
    ~Vector();          
    
    void push_back(const T &);      
    void pop_back();         

    int size() const {return _finish - _start;}     
    int capacity() const {return _end_of_storage - _start;}
private:     
    void reallocate();//重新分配内存,动态扩容要用的 
private:         
    static std::allocator<T> _alloc;          
    T *_start;                 //指向数组中的第一个元素     
    T *_finish;                //指向最后一个实际元素之后的那个元素     
    T *_end_of_storage;        //指向数组本身之后的位置 
};
template<typename T> 
allocator<T> Vector<T>::_alloc; 

//---------------------------------------------------
//构造函数
template<typename T> 
Vector<T>::Vector(int size)
{
    cout << "Vector(int =0)" << endl;
    //先申请空间
    T* tmp = _alloc.allocate(size);
    //初始化三个指针
    _start = tmp;
    _finish = _start;
    _end_of_storage = _start + size;
}

//析构函数
template<typename T> 
Vector<T>::~Vector()
{
    cout << "~Vector()" << endl;
    //先回收对象所占空间,底层调用对象的析构函数
    for(T* p = _start; p != _finish; ++p)
    {
        _alloc.destroy(p);
    }
    _alloc.deallocate(_start, capacity());
    _start = nullptr;
    _finish = nullptr;
    _end_of_storage = nullptr;
}


template<typename T> 
void Vector<T>::push_back(const T &rhs)
{
    //先判断容器是否已满
    if(_finish == _end_of_storage)
    {
        //容器已满，先扩容
        reallocate();
    }
    _alloc.construct(&rhs);
    cout << "---------------测试注释猜想,push_back()----------------------" << endl;
    cout << "_finish = " << _finish <<endl;
    _finish++;
}


template<typename T> 
void Vector<T>::pop_back()
{
    if(_start == _finish)
    {
        return;
    }
    --_finish;
    _alloc.destroy(_finish);
    cout << "pop_back scusses" << endl;
}


template<typename T> 
void Vector<T>::reallocate()
{
    cout << "reallocate" << endl;
    //先计算新空间的大小，需考虑初始时容器空间为0的情况
    int newCapacity = (size() == 0) ? 1 : capacity() * 2;
    T* tmp = _alloc.allocate(newCapacity);
    //将旧空间元素转移
    memcpy(tmp, _start, capacity());
#if 0
    T* it = _start;
    int i = 0;
    while(it !=_finish)
    {
        tmp[i] = it;
        ++it;
        ++i;
    }
#endif
    //将原空间对象所申请的资源回收
    for(T* p = _start; p != _finish; ++p)
    {
        _alloc.destroy(p);
    }
    //将原空间回收
    _alloc.deallocate(_start, capacity());

    //重置三个指针
    _start = tmp;
    _finish = tmp + newCapacity/2;
    _end_of_storage = tmp + newCapacity;
}

void test()
{
    //测试栈区
    Vector<int>vec1;
    int ret = vec1.size();
    cout << "ret = " << ret << endl;
    vec1.push_back(10);
    ret = vec1.size();
    cout << "ret = " << ret << endl;
    vec1.pop_back();
    ret = vec1.size();
    cout << "ret = " << ret << endl;

    //测试堆对象
    cout << endl;
    Vector<int>vec2;
    int* pa = new int();
    cout << "*pa = " << *pa << endl;
    vec2.push_back(*pa);
    int ret2 = vec2.size();
    cout << "ret2 = " << ret2 << endl;
    vec2.pop_back();
    ret2 = vec2.size();
    cout << "ret2 = " << ret2 << endl;
    delete pa;//堆空间需要手动释放
    
    cout << "-------" << endl;
}

void test2()
{
#if 1
    cout << "---------------测试自定义类型栈区----------------------" << endl;
    //先测栈区
    Vector<Point>vec1;
    Point p1(1,2);
    vec1.push_back(p1);
    cout << "---------------测试第二个注释猜想,test()----------------------" << endl;
    cout << "p1 = " << &p1 <<endl;
    cout << "vec1.size() " << vec1.size() << endl;
    cout << "vec1.capacity() " << vec1.capacity() << endl;
    vec1.pop_back();
    cout << "vec1.size() " << vec1.size() << endl;
    cout << "vec1.capacity() " << vec1.capacity() << endl;
    cout << "p1.getX()" << p1.getX() << endl;

#endif
#if 0
    //测试临时对象
    cout << endl;
    cout << "---------------测试自定义类型临时对象----------------------" << endl;
    Vector<Point>vec2;
    vec2.push_back({1, 2});
    cout << "vec2.size() " << vec2.size() << endl;
    cout << "vec2.capacity() " << vec2.capacity() << endl;
    vec2.pop_back();
    cout << "vec2.size() " << vec2.size() << endl;
    cout << "vec2.capacity() " << vec2.capacity() << endl;
#endif
    //即便容器中的栈对象已经被弹出，test里的栈对象还在
    //那么说明容器中保存的是栈对象的值，而不是栈对象本身
    //堆对象也是同理,所以堆对象需要程序员手动申请，手动释放

    //可以肯定，在堆区，容器的构造函数没有创建新对象，那么
    //就说明空间分配器构建对象时，是让当前的_finish指针指向堆空间元素
    //栈对象也是同理,是让当前的_finish指针指向栈空间元素
#if 0
    cout << endl;
    cout << "---------------测试自定义类型堆区----------------------" << endl;
    Vector<Point>vec3;
    Point* p2 = new Point({3, 4});
    vec3.push_back(*p2);
    cout << "p2 = " << p2 <<endl;
    cout << "vec3.size() " << vec3.size() << endl;
    cout << "vec3.capacity() " << vec3.capacity() << endl;
    vec3.pop_back();
    cout << "vec3.size() " << vec3.size() << endl;
    cout << "vec3.capacity() " << vec3.capacity() << endl;
    cout << "p2.getX()" << p2->getX() << endl;

    cout << endl;
    cout << "---------------测试注释猜想,test()----------------------" << endl;
    cout << "p2 = " << p2 <<endl;
    Point p3(5,6);
    cout << " &p3 = " << &p3 <<endl;
    delete p2;
#endif
}


int main() {
    //test();
    test2();
    return 0;
}

