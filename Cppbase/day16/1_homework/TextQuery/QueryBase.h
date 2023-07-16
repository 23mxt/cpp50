#pragma once
#include "QueryResult.h"

//继承体系的源头，不负责eval和rep的实现，将其声明为纯虚函数
class QueryBase 
{
    friend class Query;//调用虚函数
protected:
    using line_no=TextQuery::line_no;
    virtual ~QueryBase()=default;
private:
    virtual QueryResult eval(const TextQuery&)const=0;
    virtual string rep()const=0;
};



class WordQuery:public QueryBase
{
    friend class Query;//调用构造函数
private:
    WordQuery(const string & s):queryWord(s){}

    QueryResult eval (const TextQuery & t)const override
    {return t.query(queryWord);}

    string rep()const override
    {return queryWord;}

    string queryWord;
};


