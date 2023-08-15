#include "../include/Dictionary.hpp"
Dictionary*Dictionary::_pInstance = nullptr;
// 使用懒汉单例模式获取Configuration类的唯一实例
Dictionary::Dictionary(const string & cnDictpath,const string & cnIndexpath,const string & enDictpath,const string & enIndexpath)
{
    initdict(cnDictpath,enDictpath);
    initindex(cnIndexpath,enIndexpath);

}
Dictionary::~Dictionary(){}
Dictionary* Dictionary::createInstance(const string & cnDictpath,const string & cnIndexpath,const string & enDictpath,const string & enIndexpath)
{
    if (_pInstance == nullptr)
    {
        _pInstance = new Dictionary(cnDictpath,cnIndexpath,enDictpath,enIndexpath);
    }
    return _pInstance;
}

void Dictionary::initdict (const string & cnDictpath,const string & enDictpath)
{
    
    ifstream ifs1(cnDictpath);
   
    string line1;
    while(std::getline(ifs1,line1)){
        string word;
        string freq;
        istringstream iss(line1);
        iss >> word;
        
        iss >> freq;
        _cndict.push_back(make_pair(word,atoi(freq.c_str())));

    }
    ifs1.close();
    

    ifstream ifs2(enDictpath);
    string line2;
    while(std::getline(ifs2,line2)){
        string word;
        string freq;
        istringstream iss(line2);
        iss >> word;
        iss >> freq;
        _endict.push_back(make_pair(word,atoi(freq.c_str())));

    }
    ifs2.close();
    
}

void Dictionary::initindex(const string & cnIndexpath,const string & enIndexpath)
{
    
    ifstream ifs1(cnIndexpath);
    string line1;
    while(std::getline(ifs1,line1)){
        
        string word;
        string index;
        istringstream iss(line1);
        iss >> word;
        
        while(iss>>index)
        {
            _cnindexTable[word].insert(atoi(index.c_str()));
        }
        

    }
    ifs1.close();
    

    ifstream ifs2(enIndexpath);
    string line2;
    while(std::getline(ifs2,line2)){
        string word;
        string index;
        istringstream iss(line2);
        iss >> word;
        while(iss>>index)
        {
            _enindexTable[word].insert(atoi(index.c_str()));
        }
        

    }
    ifs2.close();
    
}

vector<pair<string,int>>& Dictionary::cngetDict()
{
    
    return _cndict;
}

map<string,set<int>>& Dictionary::cngetIndexTable()
{
    
    return _cnindexTable;
}

vector<pair<string,int>>& Dictionary::engetDict()
{
    return _endict;
}

map<string,set<int>>& Dictionary::engetIndexTable()
{
    return _enindexTable;
}

/*void Dictionary::initdict (const string & cnDictpath,const string & enDictpath)
{
    ifstream ifs1(cnDictpath);
    string line1;
    while(std::getline(ifs1,line1)){
        string word;
        string freq;
        istringstream iss(line1);
        iss >> word;
        iss >> freq;
        _dict.push_back(make_pair(word,atoi(freq.c_str())));

    }
    ifs1.close();
    

    ifstream ifs2(enDictpath);
    string line2;
    while(std::getline(ifs2,line2)){
        string word;
        string freq;
        istringstream iss(line2);
        iss >> word;
        iss >> freq;
        _dict.push_back(make_pair(word,atoi(freq.c_str())));

    }
    ifs2.close();
    
}

void Dictionary::initindex(const string & cnIndexpath,const string & enIndexpath)
{
    ifstream ifs1(cnIndexpath);
    string line1;
    while(std::getline(ifs1,line1)){
        string word;
        string index;
        istringstream iss(line1);
        iss >> word;
        while(iss>>index)
        {
            _indexTable[word].insert(atoi(index.c_str()));
        }
        

    }
    ifs1.close();
    

    ifstream ifs2(enIndexpath);
    string line2;
    while(std::getline(ifs2,line2)){
        string word;
        string index;
        istringstream iss(line2);
        iss >> word;
        while(iss>>index)
        {
            _indexTable[word].insert(atoi(index.c_str()));
        }
        

    }
    ifs2.close();
    
}

vector<pair<string,int>>& Dictionary::getDict()
{
    return _dict;
}

map<string,set<int>>& Dictionary::getIndexTable()
{
    return _indexTable;
}*/
