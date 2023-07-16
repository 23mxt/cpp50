#include <string.h>
#include <iostream>
#include <memory.h>
using std::cout;
using std::endl;
using std::string;

//Query_Base类 抽象基类，具体的查询类型从中派生
//所有成员都是私有的,用户通过Query这个对外的接口操作Query_Base类
class Query_Base
{
    friend class Query;
protected:
    using line_no = TextQuery::line_no; //用于eval函数
    virtual ~Query_base() = default;
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

//

int main() {

    return 0;
}

