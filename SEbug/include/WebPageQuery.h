#ifndef __WEBPAGEQUERY_H__
#define __WEBPAGEQUERY_H__
#include "WordSegmentation.h"
#include "SplitTool.hpp"
#include "SplitToolCppjieba.hpp"
#include <iostream>
#include <unordered_map>
#include <map>
#include <string>
#include <set>
#include <vector>
#include <sw/redis++/redis++.h>
#include "WebPage.hpp"
using std::cout;
using std::endl;
using std::unordered_map;
using std::pair;
using std::string;
using std::set;
using std::vector;
using std::map;
using namespace sw::redis;

class MyRedis{
public:
    MyRedis() : _redis("tcp://127.0.0.1:6379")
    { cout << "MyRedis is ok" << endl; }

    string findstr(const string& str){
        //查看redis内是否有缓存
        //如果有就原样返回，没有就返回空
        _key = str;
        auto optionalValue = _redis.get(_key);
        if(optionalValue){
            //有，原样返回
            return *optionalValue;
        } 
        //没有去内存读取
        else {
            return "";
        }
    }

    void store(const string& value){
        //key是查询内容，value是服务器提供的结果
        _redis.set(_key, value);
    }

private:
    string _key;//存传过来的key值
    Redis _redis;//Redis连接后的返回值
};

class WebPageQuery{
public:
    WebPageQuery();
    ~WebPageQuery();
    string doQuery(const string&str);
private:
    void loadLibrary();//加载库文件
    vector<double> getQueryWordsWeightVector(vector<string>&queryWords);//得到基准向量
    string createJosn(vector<int>& docIdVec,const vector<string>&queryWords);
private:
    double countSimilarity(vector<double> &x,vector<double>&y);//计算相似度
    void getIntersection(vector<set<int>>::iterator begin,vector<set<int>>::iterator end,vector<int>&result);//求交集
    void getIdSet(vector<string>&queryWords,vector<set<int>>&idSet);//得到每个关键词的文章id
    void getLike(vector<double>&Base,vector<int>&candidate,vector<pair<int,double>>&like);//排序后的结果·
private:
    SplitTool* _jieba;
    //网页查询模块需要把网页库的三个文件加载到内存来
    //那用数据库Redis意义何在?
    //但是用数据库速度确实快了，原因可能是因为Redis的内容太少了
    unordered_map<int,WebPage> _pageLib;//网页库
    unordered_map<int,pair<int,int>> _offsetLib;//偏移库
    unordered_map<string,set<pair<int,double>>> _invertIndexTable;//倒排索引库
    MyRedis _redis;
};
#endif
