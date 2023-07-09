#ifndef _LINE_H_
#define _LINE_H_

#include <iostream>

using std::cout;
using std::endl;

class Line
{
public:
    Line(int x1, int y1, int x2, int y2);
    void printLine() const;//只要不修改数据成员，都加const
    ~Line();

    class LinePimpl;//前向声明
private:
    LinePimpl* _pimpl;
};


#endif 
