#include <iostream>
#include <memory>
#include <vector>

using std::cout;
using std::endl;
using std::shared_ptr;
using std::vector;

class Point
{
public:
    Point(int ix = 0, int iy = 0)
    : _ix(ix)
    , _iy(iy)
    {
        cout << "Point(int = 0, int = 0)" << endl;
    }

    void print() const
    {
        cout << "(" << _ix
             << ", " << _iy
             << ")" << endl;
    }

    ~Point()
    {
        cout << "~Point()" << endl;
    }
private:
    int _ix;
    int _iy;
};

void test()
{
    /* shared_ptr<int> sp(new int(10)); */
    shared_ptr<Point> sp(new Point(10, 20));
    cout << "sp.use_count() = " << sp.use_count() << endl;
    sp->print();

    cout << endl;
    shared_ptr<Point> sp2(sp);
    cout << "sp.use_count() = " << sp.use_count() << endl;
    cout << "sp2.use_count() = " << sp2.use_count() << endl;
    sp->print();
    sp2->print();

    cout << endl;
    shared_ptr<Point> sp3(new Point(1, 2));
    cout << "sp3.use_count() = " << sp3.use_count() << endl;
    sp3->print();

    cout << endl;
    sp3 = sp;//堆对象调用delete析构
    cout << "sp.use_count() = " << sp.use_count() << endl;
    cout << "sp2.use_count() = " << sp2.use_count() << endl;
    cout << "sp3.use_count() = " << sp3.use_count() << endl;
    sp->print();
    sp3->print();
#if 1
    cout << endl << "作为容器的元素" << endl;
    //可以作为容器的元素
    vector<shared_ptr<Point>> vec;
    /* vec.reserve(100); */
    /* vec[0] = sp; */
    vec.push_back(sp);//既可以传左值，也可以传右值
    vec[0]->print();
    vec.push_back(std::move(sp));//ok,可以传右值
    vec[1]->print();
    //vector不会检查数组越界
    /* vec[2]->print(); */
    vec.push_back(std::move(sp3));//ok
#endif 
}

int main(int argc, char *argv[])
{
    test();
    cout << "test end" << endl;
    return 0;
}


