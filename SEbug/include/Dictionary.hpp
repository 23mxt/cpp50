#ifndef __Dictionaty_H__
#define __Dictionaty_H__
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <set>
#include <fstream>
#include <sstream>

using namespace std;

class Dictionary
{
public:
    static Dictionary* createInstance(const string & cnDictpath,const string & cnIndexpath,const string & enDictpath,const string & enIndexpath);
    void initdict (const string & cnDictpath,const string & enDictpath);
    void initindex (const string & cnIndexpath,const string & enIndexpath);
   
    vector<pair<string,int>>& cngetDict();
    map<string,set<int>>& cngetIndexTable();
    vector<pair<string,int>>& engetDict();
    map<string,set<int>>& engetIndexTable();
    /*vector<pair<string,int>>& getDict();
    map<string,set<int>>& getIndexTable();*/
    //string doQuery(string word);
    
private:
    Dictionary(const string & cnDictpath,const string & cnIndexpath,const string & enDictpath,const string & enIndexpath);
    ~Dictionary();

private:
    vector<pair<string,int>> _cndict;
    vector<pair<string,int>> _endict;
    map<string,set<int>> _cnindexTable;
    map<string,set<int>> _enindexTable;
    /*vector<pair<string,int>> _dict;
    map<string,set<int>> _indexTable;*/
    static Dictionary* _pInstance;
};
#endif