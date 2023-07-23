#include <string.h>
#include <iostream>
using std::cout;
using std::endl;
using std::string;

class Point;
class Computer;

Point pt(1, 2);
Point pt2(3, 4);

Computer com("Mac", 8888);

int main(void)
{
    Computer *pc1 = Singleton<Computer>::getInstance("Xiaomi", 6666);
    Computer *pc2 = Singleton<Computer>::getInstance("Xiaomi", 6666);
    assert(pc1 == pc2);//判断两者是同一个地址
    
    Point　*pt3 = Singleton<Point>::getInstance(1, 2);
    Point　*pt4 = Singleton<Point>::getInstance(1, 2);
    assert(pt3 == pt4);
    
    return 0;
} 
