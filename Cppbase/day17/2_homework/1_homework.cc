#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

template <typename T, int kSize = 20>
class Queue
{
public:
    Queue()
    : _front(-1)
    ,_tail(-1)
    , _data(new T[kSize]()) //申请一片堆空间，元素是T，大小为kSize的堆上数组
    {
        cout << "Queue()" << endl;
    }

    ~Queue();
    bool empty() const;
    bool full() const;
    void push(const T &value);
    void pop();
    T head() const;
private:
    int _front;
    int _tail;
    T *_data;
};

//模板参数的使用和函数参数的使用类似，此处针对的是模板类
template <typename T, int kSize>
Queue<T, kSize>::~Queue()
{
    cout << "~Queue()" << endl;
    if(_data)
    {
        delete [] _data;
        _data = nullptr;
    }
}

template <typename T, int kSize>
bool Queue<T, kSize>::empty() const
{
    return -1 == _tail;//魔数
}

template <typename T, int kSize>
bool Queue<T, kSize>::full() const
{
#if 0
    if(_top < kSize - 1)
    {
        return false;
    }
    else
    {
        return true;
    }
#endif
    return _front == kSize - 1;
}

template <typename T, int kSize>
void Queue<T, kSize>::push(const T &value)
{
    if(!full())
    {
        if(empty()){
            _tail = 0;
        }
        _data[++_head] = value;
    }
    else
    {
        cout << "The queue is full, cannot push data" << endl;
        return;
    }
}

template <typename T, int kSize>
void Queue<T, kSize>::pop()
{
    if(!empty())
    {
        ++_front;//逻辑删除
    }
    else
    {
        cout << "The queue is empty, cannot pop data" << endl;
        return;
    }
}

template <typename T, int kSize>
T Queue<T, kSize>::head() const
{
    return _data[_front];
}

void test()
{
    Queue<int, 10> queue;
    cout << "该队列是不是空的 "<< queue.empty() << endl;
    queue.push(1);
    cout << "该队列是不是满的 "<< queue.full() << endl;

    for(int sz = 2; sz != 15; ++sz)
    {
        queue.push(sz);
    }
    cout << "该队列是不是满的 "<< queue.full() << endl;

    while(!queue.empty())
    {
        cout << queue.head() << "  ";//先获取元素
        queue.pop();//再移动栈顶指针
    }
    cout << endl;
    cout << "该队列是不是空的 "<< queue.empty() << endl;
}

void test2()
{
    Stack<string, 10> st;
    cout << "该栈是不是空的 "<< st.empty() << endl;
    st.push(string("aa"));
    cout << "该栈是不是满的 "<< st.full() << endl;

    for(int sz = 1; sz != 15; ++sz)
    {
        st.push(string(2, 'a' + sz));
    }
    cout << "该栈是不是满的 "<< st.full() << endl;

    while(!st.empty())
    {
        cout << st.top() << "  ";//先获取元素
        st.pop();//再移动栈顶指针
    }
    cout << endl;
    cout << "该栈是不是空的 "<< st.empty() << endl;
}

int main(int argc, char *argv[])
{
    test2();
    return 0;
}


