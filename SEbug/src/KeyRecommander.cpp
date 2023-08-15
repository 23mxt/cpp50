#include "../include/KeyRecommander.hpp"
#include <stdio.h>
#include<string>
using std::string;
using std::to_string;
/* KeyRecommander::KeyRecommander(string & query,const TcpConnectionPtr & coon)//构造函数 */
/* :_queryWord(query) */
/* ,_coon(coon) */
/* { */
/* } */
KeyRecommander::~KeyRecommander(){}
int KeyRecommander::distance(const string& rhs)//计算最小编辑距离
{
    //老师已给出计算方式
    //要明确当前单词和待查询单词最小编辑距离
    return editDistance(rhs,_queryWord);
}

void KeyRecommander::queryIndexTable()//查询索引
{
    //加载文件
    Dictionary* dict = Dictionary::createInstance("../data/dict_Zh.dat","../data/zh_index.dat","../data/dict_En.dat","../data/en_index.dat"); 

    int length = _queryWord.size();
    //确认首个字符占几个字节
    //中英文混合索引
    for(int i = 0; i < length; )
    {
        if(_queryWord[i] & 0x80 ){
            /* if(!isalpha(_queryWord[])){ */
            //首个字符不止一个字节
            //视作中文处理
            /* for(int i = 0; i < length; i += 3){ */
            string s1 = _queryWord.substr(i,3);
            //查找中文索引文件，遍历每个包含中文字符的行号。
            for(auto & elem:dict->cngetIndexTable()[s1]){
                cout << "cnelem " << elem << " ";
                //对于每个字符的行号。取并集
                _goRepeat.insert(elem);
            }

            /* } */
            cout << endl;
            i += 3; 
        }
        else{
            //首个字符为一个字节
            //视作英文处理
            /* for(int i = 0; i < length; i++){ */
            string s1 = _queryWord.substr(i,1);
            /* cout << "i = " << i << " s1 = " << s1 << " "; */
            //对英文的处理和中文一致
            for(auto & elem:dict->engetIndexTable()[s1]){
                //cout << "enelem " << elem << endl;
                _goRepeat.insert(elem);
            }
            /* } */
            /* cout << endl; */
            i += 1;
        }
        }
    }

    void KeyRecommander::execute()//执行查询
    {
        //该行可去掉。不过因为词典是单例类，写上也没事
        Dictionary* dict = Dictionary::createInstance("../data/dict_Zh.dat","../data/zh_index.dat","../data/dict_En.dat","../data/en_index.dat"); 

        //原本要不就视作中文，要不就视作英文查询，现在要中英文混合索引
        int length = _queryWord.size();
        for(int i = 0; i < length;)
        {
            if(_queryWord[i] & 0x80 ){
                //遍历中英文取并集后的索引集合
                //对于每个中文id
                for(auto &elem :_goRepeat){
                    //得到包含字符的单词的行号
                    string word ;
                    int freq;
                    int dist;
                    word = dict->cngetDict()[elem - 1].first;
                    freq = dict->cngetDict()[elem - 1].second;
                    //计算拿到单词的最小编辑距离
                    //计算分词
                    dist = distance(word);
                    cout << "word " << word << " freq = " << freq << " dist = " << dist << endl;
                    //算出单词，词频，距离后，压入优先级队列
                    _resultQue.push(MyResult(word,dist,freq));
                }
                i += 3;
            }
            else {
                //对于每个英文，处理逻辑一致
                for(auto &elem :_goRepeat){
                    /* cout << "elem" << elem << endl; */
                    string word;
                    int freq;
                    int dist;
                    word = dict->engetDict()[elem - 1].first;
                    freq = dict->engetDict()[elem - 1].second;
                    //计算分词
                    dist = distance(word);
                    cout << "word " << word << " freq = " << freq << " dist = " << dist << endl;
                    _resultQue.push(MyResult(word,dist,freq));
                }
                i += 1;
            }
        }

}

    /*void KeyRecommander::enexecute()//执行查询
      {
      Dictionary* dict = Dictionary::createInstance("cnDictpath","cnIndexpath","enDictpath","enIndexpath");  


      for(auto &elem :_goRepeat){
      string word ;
      int freq;
      int dist;
      word = dict->engetDict()[elem - 1].first;
      freq = dict->engetDict()[elem - 1].second;
      dist = distance(word);
    //cout << "word " << word << " freq = " << freq << " dist = " << dist << endl;
    _resultQue.push(MyResult(word,dist,freq));
    }


    }*/

    /*void KeyRecommander::queryIndexTable()//查询索引
      {
      Dictionary* dict = Dictionary::createInstance("cnDictpath","cnIndexpath","enDictpath","enIndexpath");  
      int length = _queryWord.size();
      if(_queryWord[0] & 0x80 ){
      for(int i = 0; i < length; i += 3){
      string s1 = _queryWord.substr(i,3);
      for(auto & elem:dict->getIndexTable()[s1]){
    //cout << "cnelem " << elem << " ";
    _goRepeat.insert(elem);
    }

    }
    //cout << endl;
    }
    else{
    for(int i = 0; i < length; i++){
    string s1 = _queryWord.substr(i,1);
    //cout << "i = " << i << " s1 = " << s1 << " ";
    for(auto & elem:dict->getIndexTable()[s1]){
    //cout << "enelem " << elem << endl;
    _goRepeat.insert(elem);
    }

    }
    //cout << endl;
    }
    }

    void KeyRecommander::execute()//执行查询
    {
    Dictionary* dict = Dictionary::createInstance("cnDictpath","cnIndexpath","enDictpath","enIndexpath");  

    if(_queryWord[0] & 0x80 ){
    for(auto &elem :_goRepeat){
    string word ;
    int freq;
    int dist;
    word = dict->getDict()[elem - 1].first;
    freq = dict->getDict()[elem - 1].second;
    dist = distance(word);
    cout << "word " << word << " freq = " << freq << " dist = " << dist << endl;
    _resultQue.push(MyResult(word,dist,freq));
    }
    }
    else {
    for(auto &elem :_goRepeat){
    string word ;
    int freq;
    int dist;
    word = dict->getDict()[elem - 1].first;
    freq = dict->getDict()[elem - 1].second;
    dist = distance(word);
    //cout << "word " << word << " freq = " << freq << " dist = " << dist << endl;
    _resultQue.push(MyResult(word,dist,freq));
    }
    }


    }*/


    string KeyRecommander::response(const string & query,LRUCache* cache)//响应客户端
    {
        _goRepeat.clear();
        // _resultQue.clear();
        /*for(int i = 0; i < 5; i++){
          cout << _resultQue.top()._string << endl;
          _resultQue.pop();
          }*/
        _queryWord = query;
        string result=cache->getelement(_queryWord);
        if(result=="")
        {
            queryIndexTable();
            execute();
            json js;
            if(_resultQue.size() <= 5){
                int tmp = _resultQue.size();
                for(int i = 0; i < tmp; ++i){
                    string msg = _resultQue.top()._string;
                    js[to_string(i)].push_back(msg);
                    _resultQue.pop(); 
                    // cout << _resultQue.top()._string << endl;
                    // _resultQue.pop();

                    //cout << _resultQue.size() << endl;
                }

            }
            else {
                for (int j = 0 ; j < 5; j++){
                    string msg = _resultQue.top()._string;
                    js[to_string(j)].push_back(msg);
                    _resultQue.pop();
                    // cout << _resultQue.top()._string << endl;
                    // _resultQue.pop();
                }

                for (int m = 0; m < _resultQue.size(); m++){
                    _resultQue.pop();
                }
            }
            cache->addelement(_queryWord,js.dump());
            result=js.dump();
        }
        return result;
    }
