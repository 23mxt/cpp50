#pragma once //防止头文件重复包含引发重定义
#include "TextQuery.h"

#include <iostream>


class QueryResult
{
public:
    friend ostream & print(ostream & os,const QueryResult & sought);
    //Query的构造函数负责保存单词，行号，行号对应的文本
    QueryResult(const string & s,shared_ptr<set<TextQuery::line_no>> p,
                shared_ptr<vector<string>> f):
    sought(s),lines(p),file(f){}

    //获取shared_ptr所指向的处理文件
    shared_ptr<vector<string>> getFile()
    {
        return file;
    }

    //添加begin和end成员，为后面~做准备
    set<TextQuery::line_no>::iterator begin()
    {
        return lines->begin();
    }

    set<TextQuery::line_no>::iterator end()
    {
        return lines->end();
    }

private:
    string sought;
    shared_ptr<vector<string>> file; //指向文本的智能指针
    shared_ptr<set<TextQuery::line_no>> lines;  //指向行号集合的智能指针
};

