#pragma once
#include "Query.h"

class NotQuery
:public QueryBase
{
    friend Query operator~(const Query &);

    NotQuery(const Query & q):query(q){}

    string rep()const override
    {return "~("+query.rep()+")";}

    //eval是查询系统的核心，取反利用迭代器对比
    QueryResult eval(const TextQuery & text)const override;
    Query query;
};

inline Query operator~(const Query & operand)
{
    return shared_ptr<QueryBase>(new NotQuery(operand));
}

