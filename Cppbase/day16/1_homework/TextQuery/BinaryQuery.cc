#include "BinaryQuery.h"

//#include <algorithm>

QueryResult OrQuery::eval(const TextQuery & text)const
{
    auto left=lhs.eval(text),right=rhs.eval(text);

    auto retLines=
        make_shared<set<line_no>>(left.begin(),left.end());

    retLines->insert(right.begin(),right.end());

    return QueryResult(rep(),retLines,left.getFile());

}


QueryResult AndQuery::eval(const TextQuery & text)const
{
    auto left=lhs.eval(text),right=rhs.eval(text);


    auto retLines=
        make_shared<set<line_no>>();

    auto lt=left.begin(),rt=right.begin();

    while(lt!=left.end()&&rt!=right.end())
    {
        if(*lt<*rt)
            ++lt;
        else if(*rt<*lt)
            ++rt;
        else
        {
            retLines->insert(*lt);
            ++lt;
            ++rt;
        }
    }

   // set_intersection(left.begin(), left.end(), right.begin(), right.end(), inserter(*retLines, retLines->begin()));

    return QueryResult(rep(),retLines,left.getFile());

}

