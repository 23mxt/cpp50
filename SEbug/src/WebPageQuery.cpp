#include "../include/WebPageQuery.h"
#include <algorithm>
#include <iostream>
#include<cmath>
#include<fstream>
#include<sstream>
#include<unistd.h>
#include"../include/WebPage.hpp"
#include<nlohmann/json.hpp>
using json=nlohmann::json;
using std::set_intersection;
using std::cout;
using std::endl;
using std::ifstream;
using std::stringstream;
WebPageQuery::WebPageQuery()
:_jieba(new SplitToolCppjieba())
{
    loadLibrary();
    cout << "loadLibrary success" << endl;
}
WebPageQuery::~WebPageQuery(){
    if(_jieba){
        delete _jieba;
        _jieba =nullptr;
    }
}

//chatgpt
#if 0
string WebPageQuery::createJosn(vector<int>& docIdVec,const vector<string>&queryWords){
    json jsonObj;

    // 构建 docIdVec 的 JSON 数组
    json docIds = json::array();
    for (const int& docId : docIdVec) {
        docIds.push_back(docId);
    }

    // 构建 queryWords 的 JSON 数组
    json query = json::array();
    for (const string& word : queryWords){
        query.push_back(word);
    }

    // 将 docIds 和 query 添加到 jsonObj
    jsonObj["docIds"] = docIds;
    jsonObj["query"] = query;

    // 将 JSON 对象转换为字符串
    string jsonString = jsonObj.dump();
    return jsonString;
}
#endif
//执行查询
string WebPageQuery::doQuery(const string&str){
//find
    cout << "debug position3" << endl;
    string ret = _redis.findstr(str);
    cout << "debug position 4" << endl;
    if(ret == ""){
        cout << "redis has not save it " << endl;
    } else {
        return ret;
    }

    cout << "debug position5" << endl;
    /* return ""; */
    vector<string> queryWords = _jieba->cut(str);//分词成功
    //取出每个短语的文章ID。
    vector<set<int>> idSet;
    getIdSet(queryWords,idSet);
    //取交集 得到候选文章ID
    vector<int> candidate(idSet[0].begin(),idSet[0].end());
    getIntersection(++idSet.begin(),idSet.end(),candidate);
    //得到候选文章ID 计算相似度 得到按相似度大小排序的网页
    //得到基准向量Base
    vector<double>Base = getQueryWordsWeightVector(queryWords);
    vector<pair<int,double>> like; //第一项文章ID，第二项相似度
    getLike(Base,candidate,like);
    //发送 文章信息 按顺序
    //取出5篇相似度最高的文章 发送过去
    vector<int> docIdVec;
    for(int idx=0;idx<5&&idx<like.size();idx++){
        docIdVec.push_back(like[idx].first);
    }
    ret = createJosn(docIdVec,queryWords);
//store
    _redis.store(ret);
    cout << "debug position6" << endl;
    cout << ret << endl;
    return ret;
}

bool compare(pair<int,double>p1,pair<int,double>p2){
    if(p1.second<p2.second)
        return true;
    return false;
}

//加载库文件
void WebPageQuery::loadLibrary(){
    ifstream ifs;
    //初始化倒排索引库
    ifs.open("../data/invertIndex.dat");
    if(!ifs){
        std::cerr<<"ifs.open failed 倒排索引库文件"<<std::endl;
        return ;
    }
    string buf;
    while(std::getline(ifs,buf),!ifs.eof()){
        stringstream ss(buf);
        //获取短语
        string word;
        ss>>word;
        while(!ss.eof()){
            //文章ID
            int docID;
            //短语所在文章ID的权重
            double weight;
            ss>>docID>>weight;
            _invertIndexTable[word].insert(std::make_pair(docID,weight));
        }
    }
    ifs.close();
    //初始化偏移库
    ifs.open("../data/offset.dat");
    if(!ifs){
        std::cerr<<"open 偏移库文件 failed"<<std::endl;
        return;
    }
    buf.clear();
    while(std::getline(ifs,buf),!ifs.eof()){
        stringstream ss(buf);
        int DocId;
        int DocBegin;
        int DocSize;
        ss>>DocId>>DocBegin>>DocSize;
        _offsetLib.insert(std::make_pair(DocId,std::make_pair(DocBegin,DocSize)));
    }
    ifs.close();
    //初始化网页库
    ifs.open("../data/pagelib.dat");
    WordSegmentation& wordSeg = _jieba->getWordSeg();
    if(!ifs){
        std::cerr<<"open 网页库文件 failed"<<std::endl;
    }
    for(int idx=0;idx<_offsetLib.size();idx++){
        char buff[100000] = {0};
        int docBegin = _offsetLib[idx+1].first;
        int docSize = _offsetLib[idx+1].second;
        ifs.seekg(docBegin);
        ifs.read(buff,docSize);
        _pageLib.insert(std::make_pair(idx+1,WebPage(buff,wordSeg)));
    }
    cout << "初始化三个网页库文件成功" << endl;
}
//计算查询词的权重值
vector<double> WebPageQuery::getQueryWordsWeightVector(vector<string>&queryWords){
    unordered_map<string,int> tmp;
    for(auto &word:queryWords){
        tmp[word]++;
    }
    vector<int>TF;
    for(auto &frequency:tmp){
        TF.push_back(frequency.second);
    }
    unordered_map<string,int>DF;
    for(auto &word:queryWords){
        DF[word] = _invertIndexTable[word].size();
    }
    vector<double>IDF;
    for(auto &wordFrequency:DF){
        double res = log((double)_pageLib.size()/(wordFrequency.second+1))/log(2);
        IDF.push_back(res);
    }
    vector<double>weights;
    for(int idx=0;idx<TF.size();idx++){
        weights.push_back(TF[idx]*IDF[idx]);
    }
    double sum =0;
    for(int idx=0;idx<weights.size();idx++){
        sum += weights[idx]*weights[idx];
    }
    sum = sqrt(sum);
    for(int idx=0;idx<weights.size();idx++){
        weights[idx] = weights[idx]/sum;
    }

    return weights;
}

//执行Json文章信息
#if 1
string WebPageQuery::createJosn(vector<int>& docIdVec,const vector<string>&queryWords){
    json j;
    for(int idx=0;idx<docIdVec.size();idx++){
        WebPage page = _pageLib[docIdVec[idx]];
        string summary = page.getsummary();
        cout << "summary" << endl;
        cout << summary << endl;
        string querywords;
        for(int j = 0;j<queryWords.size();j++){
            querywords.append(queryWords[j]);
        }
        if(summary.find(querywords)>summary.size()){
            j[std::to_string(idx)].push_back(std::make_tuple("","",""));
            continue;
        }
        summary = summary.substr(summary.find(queryWords[0]),300);
        string tmp;
        tmp+="\033[01;31m";
        tmp+=querywords;
        tmp+="\033[0m";

        for(int j = querywords.size();j<summary.size();j++){
            if(summary[j]&(1<<7)){
                if(summary.size()>=j+3){
                    tmp.push_back(summary[j++]);
                    tmp.push_back(summary[j++]);
                    tmp.push_back(summary[j]);
                }else{
                    break;
                }
            }else{
                tmp.push_back(summary[j]);
            }
        }
        j[std::to_string(idx)].push_back(std::make_tuple(page.getdoctitle(),page.geturl(),
        tmp));
    }

    cout << "j.dump()" << endl;
    cout << j.dump() << endl;
    string jresult = j.dump();
    return jresult;
}
#endif

double WebPageQuery::countSimilarity(vector<double> &x,vector<double>&y){
    x.resize(y.size());
    double inner= 0;
    double sumX = 0;
    double sumY = 0;
    for(int idx = 0;idx<x.size();idx++){
        inner += x[idx]*y[idx];
        sumX +=x[idx]*x[idx];
        sumY +=y[idx]*y[idx];
    }
    sumX = sqrt(sumX);
    sumY = sqrt(sumY);
    double sum = sumX+sumY;
    double ret = inner/sum;
    return acos(ret);
}

void WebPageQuery::getIntersection(vector<set<int>>::iterator begin,vector<set<int>>::iterator end,vector<int>&result){
    if(begin>=end){
        return ;
    }
    vector<int> res;
    set_intersection(result.begin(),result.end(),begin->begin(),begin->end(),
    std::back_inserter(res));
    result.swap(res);
    getIntersection(++begin,end,result);
}

void WebPageQuery::getIdSet(vector<string>&queryWords,vector<set<int>>&idSet){
    for(int i = 0;i<queryWords.size();i++){
        string words = queryWords[i];
        auto ret = _invertIndexTable[words];
        set<int> id;
        for(auto &x:ret){
            id.insert(x.first);
        }
        idSet.push_back(id);
    }
}

void WebPageQuery::getLike(vector<double>&Base,vector<int>&candidate,vector<pair<int,double>>&like){
    for(int i = 0;i<candidate.size();i++){
        vector<double> totalWeight;
        for(auto &elem:_invertIndexTable){//unordered_map<string,set<pair<int,double>>>
            for(auto &pageInfo:elem.second){//set<pair<int,double>>
                if(pageInfo.first==candidate[i]) //int ->docID
                {
                    totalWeight.push_back(pageInfo.second);//pageInfo.second -->weight
                }
            }
        }
        like.push_back(std::make_pair(candidate[i],countSimilarity(Base,totalWeight)));
    }
    std::sort(like.begin(),like.end(),compare);
}

