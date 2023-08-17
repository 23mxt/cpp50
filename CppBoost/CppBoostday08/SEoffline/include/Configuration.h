#ifndef _Configuration_H_
#define _Configuration_H_

#include "Offline.h"

//配置文件
class Configuration
{
public:

public:
    Configuration(const string &filepath);
    ~Configuration() {}

    //获取存放配置内容的map,网页搜索模块用
    map<string, string> &getConfigMap();
    //获取停用词词集
    set<string> getStopwordList();
private:
    string _filepath;   //配置文件路径
    map<string, string> _configMap; //配置文件内容, 文件路径 文件名
    set<string> _stopWordList;  //停用词词集
};

#endif 

