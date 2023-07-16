#include <string.h>
#include <iostream>
#include <memory.h>

using std::cin;
using std::cout;
using std::endl;
using std::string;

class QueryResult
{

private:
    
};

class TextQuery
{

};


void testQuery()
{
    // infile是一个ifstream,指向我们要处理的文件
    TextQuery tq("The_Holy_Bible.txt");//指向我们要处理的文件
    
    //与用户交互：提示用户输入要查询的单词
    
    while(true)
    {
        string word;
        cout << "请输入要查询的单词" << endl;
        cin >> word;
        print(cout, tq.query(s));
    }
    
}
int main() {

    return 0;
}

