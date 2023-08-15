#ifndef _WORDSEGMENTATION_H_
#define _WORDSEGMENTATION_H_
#include "cppjieba/Jieba.hpp"
#include <iostream>
#include <string>
#include <vector>
using std::cout;
using std::endl;
using std::string;
using std::vector; // . --> src/
const char * const DICT_PATH = "/home/tml/cpp50-group2-se/SearchEngine/include/cppjieba/dict/jieba.dict.utf8"; //分词所使用的词典路径
const char * const HMM_PATH = "/home/tml/cpp50-group2-se/SearchEngine/include/cppjieba/dict/hmm_model.utf8"; 
const char * const USER_DICT_PATH = "/home/tml/cpp50-group2-se/SearchEngine/include/cppjieba/dict/user.dict.utf8";
const char * const IDF_PATH = "/home/tml/cpp50-group2-se/SearchEngine/include/cppjieba/dict/idf.utf8";
const char * const STOP_WORD_PATH = "/home/tml/cpp50-group2-se/SearchEngine/include/stop_words_zh.txt";
class WordSegmentation//使用结巴分词库进行分词
{
public:
WordSegmentation()
: _jieba(DICT_PATH, HMM_PATH, USER_DICT_PATH,IDF_PATH,STOP_WORD_PATH)//初始化Jieba类对象
{
// cout << "cppjieba init!" << endl;
}
vector<string> operator()(const string str)//返回str的分词结果
{
vector<string> words;
_jieba.CutAll(str, words);//FullSegment
return words;
}
private:
cppjieba::Jieba _jieba;
};
#endif
