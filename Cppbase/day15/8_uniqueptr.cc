#include <iostream>
#include <memory>
#include <vector>

using std::cout;
using std::endl;
using std::unique_ptr;
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
    /* unique_ptr<int> up(new int(10)); */
    //用构造函数托管资源
    unique_ptr<Point> up(new Point(10, 20));
    up->print();

    //表现的是对象语义
    //不允许复制或者赋值
    cout << endl;
    /* unique_ptr<Point> up2(up);//error */
    unique_ptr<Point> up3(new Point(1, 2));
    /* up3 = up;//error */

    //可以作为容器的元素
    vector<unique_ptr<Point>> vec;
    /* vec.push_back(up);//error,因为up的拷贝构造函数被删除了 */
    vec.push_back(std::move(up));//ok,可以传右值
    vec.push_back(std::move(up3));//ok
    /* vec.push_back(up);//not ok */
                                  //用析构函数释放资源
    for(auto & elem : vec)
    {
        elem->print();
    }
}

int main(int argc, char *argv[])
{
    test();
    return 0;
}


