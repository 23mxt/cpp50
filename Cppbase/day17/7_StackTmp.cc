#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

template <typename T, int kSize = 20>
class Stack
{
public:
    Stack()
    : _top(-1)
    , _data(new T[kSize]())
    {
        cout << "Stack()" << endl;
    }

    ~Stack();
    bool empty() const;
    bool full() const;
    void push(const T &value);
    void pop();
    T top() const;
private:
    int _top;
    T *_data;
};

template <typename T, int kSize>
Stack<T, kSize>::~Stack()
{
    cout << "~Stack()" << endl;
    if(_data)
    {
        delete [] _data;
        _data = nullptr;
    }
}

template <typename T, int kSize>
bool Stack<T, kSize>::empty() const
{
    /* return _top = -1; */
    return -1 == _top;//魔数
}

template <typename T, int kSize>
bool Stack<T, kSize>::full() const
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
    return _top == kSize - 1;
}

template <typename T, int kSize>
void Stack<T, kSize>::push(const T &value)
{
    if(!full())
    {
        _data[++_top] = value;
    }
    else
    {
        cout << "The stack is full, cannot push data" << endl;
        return;
    }
}

template <typename T, int kSize>
void Stack<T, kSize>::pop()
{
    if(!empty())
    {
        --_top;
    }
    else
    {
        cout << "The stack is empty, cannot pop data" << endl;
        return;
    }
}

template <typename T, int kSize>
T Stack<T, kSize>::top() const
{
    return _data[_top];
}

void test()
{
    Stack<int, 10> st;
    cout << "该栈是不是空的 "<< st.empty() << endl;
    st.push(1);
    cout << "该栈是不是满的 "<< st.full() << endl;

    for(int sz = 2; sz != 15; ++sz)
    {
        st.push(sz);
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


