#pragma once
#include <memory>
#include <vector>
#include <string>
#include <fstream>
#include <set>
#include <map>
#include <sstream>
using namespace std;

class QueryResult;

class TextQuery
{
public:
    using line_no=vector<string>::size_type;
    TextQuery(ifstream & is);
    QueryResult query(const string & word)const;
private:
    shared_ptr<vector<string>> file; //file是存储文本容器的shared_ptr指针
    map<string,shared_ptr<set<line_no>>> wm;    //wm存的是单词对应的行号集合
};

