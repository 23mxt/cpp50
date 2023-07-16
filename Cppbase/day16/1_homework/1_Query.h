#ifndef _QUERY_H_
#define _QUERY_H_ 

#include "TextQuery.h"
#include <string>
#include <iostream>
#include <memory>
#include <set>
#include <vector>
using std::cout;
using std::endl;
using std::set;
using std::vector;
using std::string;
using std::ostream;
using std::istream;
using std::shared_ptr;

class TextQuery;

class QueryResult{
public:
    typedef vector<string>::size_type line_no;//保存出现的行号，使用类型别名
    friend ostream& operator<<(ostream&,const QueryResult&);//输出查询结果

private:
    string word;//查询的单词
    shared_ptr<set<line_no>> nos;//用set保存出现的行号
    shared_ptr<vector<string>> input;//输出文件vector的指针
};

//Query_Base类 抽象基类，具体的查询类型从中派生
//所有成员都是私有的,用户通过Query这个对外的接口操作Query_Base类
class Query_Base
{
    friend class Query;
protected:
    using line_no = TextQuery::line_no; //用于eval函数
    virtual ~Query_Base() = default;
private:
    virtual QueryResult eval(const TextQuery &) const = 0;
    virtual string rep() const = 0;
};

//对外接口
//这是一个管理Query_base继承体系的接口类
class Query
{
//需要访问接收sp智能指针的构造函数，而构造函数是私有的
    friend Query operator~(const Query &);
    friend Query operator|(const Query &, const Query &);
    friend Query operator&(const Query &, const Query &);

    //通过sp对rep进行调用
    ostream &operator<<(ostream &os, const Query &query)
    {
        return os << query.rep();
    }
public:
    Query(const string &);  //构建一个新的wordQuery，在此基础上进行操作
    //接口函数：调用对应的Query_base操作
    QueryResult eval(const TextQuery &t) const 
    {
        return q->eval(); 
    }

    string rep() const
    {
        return q->rep();
    }
private:
    Query(shared_ptr<Query_Base> query)
    :q(query)
    {
    
    }

    shared_ptr<Query_Base> q;//接收base类型
};

//派生类不使用sp，使用Query来操作
//WordQuery
class WordQuery
:public Query_Base 
{
friend class Query;//Query使用WordQuery构造函数
    WordQuery(const string &s)
    :query_word(s)
    {
        cout << "WordQuery" << endl;
    }

    //WordQuery将定义所有继承而来的纯虚函数
    //WordQuery需要调用TextQuery进行文本查询
    QueryResult eval(const TextQuery &t) const 
    {
        return t->query(query_word);
    }
    string rep() const
    {
        return query_word;
    }

string query_word;
};

//定义完wordquery后，可以实现接收string的Query的构造函数了
inline
Query::Query(const string &s)
:q(new WordQuery(s))//智能指针做栈对象会回收wordquery申请的堆空间
{}

//~生成一个NotQuery，其中保存着一个需要对齐进行取反的Query
//NotQuery
class NotQuery
{
//因为所有成员都是私有的，因此要先将~运算符设为友元
friend Query operator~(const Query &);
    NotQuery(const Query& rhs)
    :query(rhs) //说明取反的操作将通过纯虚函数实现
    {
        cout << "NotQuery" << endl;
    }

    string rep() const 
    {
        return ""~" + "(" + query.q->rep() << ")"";
    }
    QueryResult eval(const TextQuery &) const; 

Query query;//NotQuery将要定义的函数有构造函数，继承而来的纯虚函数
};
inline
Query operator~(const Query &operand)
{
    return shared_ptr<Query_base>(new NotQuery(operand));
}

//Binary类不定义eval，而是继承了该纯虚函数。
//既然继承了该纯虚函数，则不能创建对象
class BinaryQuery
{
protected:
    BinaryQuery(const Query &l, const Query &r, const string &s)
    :lhs(l)
    ,rhs(r)
    ,opSym(s)
    {}

    string rep() const 
    {
        return "(" + lhs.rep()
            + opSym + rhs.rep() + ")"; 
    }

    Query lhs, rhs; //左侧和右侧运算对象
    string opSym;   //运算符的名字
};

//定义完与类后，可以在内联函数里重载与运算符了
class AndQuery
{
friend Query operator&(const Query&, const Query&);
AndQuery(const Query& l, const Query &r)
:BinaryQuery(l, r, "&")
{}

QueryResult eval(const TextQuery &) const;
};
//让inline绑定与类
inline Query operator&(const Query &lhs, const Query &rhs)
{
    return shared_ptr<Query_Base>(new AndQuery(lhs, rhs));
}

//或运算符的代码逻辑和与基本一致
class OrQuery
{
friend Query operator|(const Query&, const Query&);
OrQuery(const Query& l, const Query &r)
:Query_Base(l, r, "|")
{}

QueryResult eval(const TextQuery &) const;
};
inline Query operator|(const Query &lhs, const Query &rhs)
{
    return shared_ptr<Query_Base>(new OrQuery(lhs, rhs));
}

#endif

