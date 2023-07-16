#pragma once
#include "QueryBase.h"
class Query     //对外的接口
{
    friend Query operator~(const Query &);//调用私有构造函数
    friend Query operator|(const Query &,const Query &);
    friend Query operator&(const Query &,const Query &);

public:
    Query(const string & s):q(new WordQuery(s)){}

    QueryResult eval(const TextQuery &t)const
    {return q->eval(t);}

    string rep()const
    {return q->rep();}
private:
    Query(shared_ptr<QueryBase> query):q(query){} //copy
    shared_ptr<QueryBase> q;
};

inline 
ostream & operator<<(ostream & os,const Query & query)
{
    return os<<query.rep();
}


