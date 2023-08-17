#ifndef _DictProducer_H_
#define _DictProducer_H_

#include "Offline.h"

class SplitTool;

class DictProducer
{
public:
    DictProducer(const string &dir);    //构造函数
    DictProducer(const string &dir, SplitTool *SplitTool);  //中文构造函数
     ~DictProducer();

     void buildEnDict();    //创建英文词典
     void buildCnDict();    //创建中文词典
     void storeDict(const char* filepath);  //将词典写入文件
     
#if 0
     void showFiles() const;    //查看文件路径，作为测试用
     void showDict() const;     //查看词典，作为测试用
#endif                           

     void readStopWords(const string &filepath);
private:
     void getFiles();   //获取文件的绝对路径
     void pushDict(const string & word); //存储某个单词
     void preProcessLine(string &line); //大小写转换，标点符号变空格
private:
    string _dir;//文件夹路径
    vector<string> _files;//语料库文件的绝对路径
    //词典  词频统计
    //生成时去掉停用词
    map<string, int>_dict; 
    //索引
    //英文string存字母，set存词典中含有该单词的下标
    //中文string存汉字
    map<string, set<int>> _index;
    unordered_set<string> _stopWord;//停用词集合
    //分词工具
    SplitTool* _splitTool;
};

//分词工具类
class SplitTool
{
public:
    SplitTool();
    virtual ~SplitTool();

    //分词函数，纯虚函数
    virtual vector<string> cut() = 0;
};

class Configuration;

//分词工具类
class SplitToolCppJieba
:public SplitTool 
{
public:
    SplitToolCppJieba();
    virtual ~SplitToolCppJieba();

    //分词函数，虚函数
    virtual vector<string> cut(const string &sentence);

private:
    //配置文件路径
    Configuration &_conf;
};

#endif 

