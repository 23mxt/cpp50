#ifndef __KeyRecommander_H__
#define __KeyRecommander_H__
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <queue>
#include "Dictionary.hpp"
#include "EditDistance.hpp"
#include <unordered_set>
#include "MyResult.hpp"
#include <nlohmann/json.hpp>
#include "LRUCache.hpp"
using json = nlohmann::json;
using std::string;
using std::vector;
using std::set;
using std::queue;
using std::cout;
using std::endl;
using std::unordered_set;
using std::priority_queue;


class MyCompare
{
public:
    //重载函数调用运算符，自定义优先级队列排序的规则
    bool operator ()(MyResult x,MyResult y){
        //编辑距离大的应排在后面
        if(x._dist > y._dist){
            return true;
        }
        else if (x._dist < y._dist){
            return false;
        }
        else {
            //编辑距离相同，词频大的就应该在前面
            if (x._freq > y._freq){ 
                return false;
            }
            else if(x._freq < y._freq){
                return true;
            } else {
                //编辑距离相同，比较字母序.字母序大的应该在前面
                if(x._string > y._string) {
                    return false;
                } else {
                    return true;
                }
            } 
            
        }
    }
};

class KeyRecommander
{
public:
    /* KeyRecommander(string & query,const TcpConnectionPtr & coon) ; */
    ~KeyRecommander();
    void execute();
    //void enexecute();
    void queryIndexTable();
    int distance(const string&rhs);
    string response(const string & query,LRUCache*);

private:
    string _queryWord;
    /* TcpConnectionPtr _coon; */
    //元素类型 容器 比较规则
    priority_queue<MyResult,vector<MyResult>,MyCompare> _resultQue; //
    unordered_set<int> _goRepeat;   //每个字符的id集合，后面要取并集
};
#endif


