#ifndef __MyResult_H__
#define __MyResult_H__
#include <string>
using std::string;
class MyCompare;
class KeyRecommander;

class MyResult
{
    friend class MyCompare;
    friend class KeyRecommander;
public:
    MyResult(const string & str,int dist,int freq)
    :_string(str)
    ,_dist(dist)
    ,_freq(freq)
    {
        
    }
private:
    string _string;
    int _dist;
    int _freq;
};
#endif