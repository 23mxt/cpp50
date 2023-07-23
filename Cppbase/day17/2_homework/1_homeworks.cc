#include <string.h>
#include <iostream>
using std::cout;
using std::endl;
using std::string;

//用数组实现队列
template<typename T, int kSize = 20>
class Queue
{
public:
    //构造
    Queue()
    :_data(new T[kSize]())
    ,_front(-1)
    ,_rear(-1)
    ,_size(0)
    {
        cout << "Queue()" << endl;
    }

    //析构
    ~Queue()
    {
        cout << "~Queue()" << endl;
        if(_data)
        {
            delete [] _data;
            _data = nullptr;
        }
    }


    //判空
    bool isEmpty()
    {
        return 0 == _size;
    }
    //判满
    bool isFull()
    {
        return kSize == _size;
    }
    
    //入队
    void inQueue(T t)
    {
        //判队满
        if(isFull())
        {
            cout << "The queue is full, cannot InQueue" << endl;
            return;
        }
        //判队空
        if(isEmpty())
        {
            _front = 0;
        }
        //插入队尾
        _data[++_rear] = t;
        _rear = (_rear  % kSize); //循环队列
        ++_size;//容量增加
    }

    //出队
    void deQueue()
    {
        //判队空
        if(isEmpty())
        {
            cout << "The queue is full, cannot InQueue" << endl;
            return;
        }
        //弹出队头，逻辑弹出，通过队头指针后移实现
        _front = (_front + 1) % kSize;
        --_size;//容量减小
    }

    //peek
    T peek()
    {
        //判空逻辑放在外面做
        //判空逻辑放在里面做可不可行？
        return _data[_front];
    }
private:
    int _front; //队头
    int _rear;  //队尾
    int _size;  //队列大小
    T* _data;
};

void test()
{
    Queue<int, 10> qu;
    cout << "队列是不是空的" << qu.isEmpty() << endl;
    qu.inQueue(1);
    cout << "队列是不是空的" << qu.isEmpty() << endl;
    cout << "队列是不是满的" << qu.isFull() << endl;

    for(int sz = 2; sz < 15; ++sz)
    {
        qu.inQueue(sz);
    }
    cout << "队列是不是满的" << qu.isFull() << endl;

    while(!qu.isEmpty())
    {
        cout << qu.peek() << "  ";
        qu.deQueue();
    }
    cout << endl;
    cout << "队列是不是空的" << qu.isEmpty() << endl;
}

void test2()
{
    Queue<string, 10> qu;
    cout << "队列是不是空的" << qu.isEmpty() << endl;
    string s1 = "aa";
    qu.inQueue(s1);
    cout << "队列是不是空的" << qu.isEmpty() << endl;
    cout << "队列是不是满的" << qu.isFull() << endl;

    for(int sz = 1; sz < 15; ++sz)
    {
        qu.inQueue(string(2, 'a' + sz));
    }
    cout << "队列是不是满的" << qu.isFull() << endl;

    while(!qu.isEmpty())
    {
        cout << qu.peek() << "  ";
        qu.deQueue();
    }
    cout << endl;
    cout << "队列是不是空的" << qu.isEmpty() << endl;
}

int main() {
    test2();
    return 0;
}

