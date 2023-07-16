#include "Query.h"

//BinaryQuery也是抽象类，将其构造函数设为protected
class BinaryQuery
:public QueryBase
{
protected:
    BinaryQuery(const Query & lt,const Query & rt,string s):
    lhs(lt),rhs(rt),opSym(s){}

    string rep()const override
    {
        return "("+lhs.rep()+" "+opSym+" "+rhs.rep()+")";
    }

    Query lhs,rhs;
    string opSym;
};

class AndQuery
:public BinaryQuery
{
    friend Query operator&(const Query &,const Query &);
    AndQuery(const Query & left,const Query & right):BinaryQuery(left,right,"&"){}

    QueryResult eval(const TextQuery &)const override; //经过比较，行号同时存在才插入集合



};

class OrQuery
:public BinaryQuery
{
    friend Query operator|(const Query &,const Query &);
    OrQuery(const Query & left,const Query & right):BinaryQuery(left,right,"|"){}

    QueryResult eval(const TextQuery &)const override; //取并集，set的插入



};

inline Query operator|(const Query & lhs,const Query & rhs)
{
    return shared_ptr<QueryBase>(new OrQuery(lhs,rhs));
}

inline Query operator&(const Query & lhs,const Query & rhs)
{
    return shared_ptr<QueryBase>(new AndQuery(lhs,rhs));
}

