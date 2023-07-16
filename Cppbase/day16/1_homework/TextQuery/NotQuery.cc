#include "NotQuery.h"

QueryResult NotQuery::eval(const TextQuery & text)const
{
    auto retLines=
        make_shared<set<line_no>>();

    auto result=query.eval(text);

    for(int i=0;i<result.getFile()->size();++i)
    {
        retLines->insert(i);
    }
    auto itr=result.begin();
    auto ret=retLines->begin();
    while(itr!=result.end()&&ret!=retLines->end())
    {
        if(*ret==*itr)
        {
            //erase的两种使用方式
            retLines->erase(ret++);
            //ret=retLines->erase(ret);
            ++itr;
        }
        else
            ++ret;

    }

    return QueryResult(rep(),retLines,result.getFile());
}




