#include "DictProducer.h"


DictProducer::DictProducer(const string &dir)    
:_dir(dir)
{
    _files.reserve(100);
}

DictProducer::~DictProducer() {}

void DictProducer::buildEnDict()    //创建英文词典
{
    getFiles();
    //每一个file都是一个文件的绝对路径
    for(auto & file : _files)
    {
        ifstream ifs(file);
        if(!ifs)
        {
            cerr << "ifstream open file" << file << "error" << endl;
            return;
        }

        //读取一行数据
        string line;
        while(getline(ifs, line))
        {
            preProcessLine(line);

            istringstream iss(line);
            string word;
            while(iss >> word)
            {
                //如果为空或者是停用词就继续
                if(word.empty() || _stopWord.count(word) > 0) 
                {
                    continue;
                }
                
                _dict[word]++;  //不存在，新插入词典
                                //词频为1
            }
        }

        //字节流不用关闭,出循环就没了
        ifs.close();
    }
}

void DictProducer::preProcessLine(string &line)
{
    for(auto &ch : line)
    {
        //大写转小写，标点符号转空格
        if(!isalpha(ch))
        {
            ch = ' ';
        }
        else if(isupper(ch))
        {
            ch = tolower(ch);
        }
    }
}

void DictProducer::readStopWords(const string &filepath)
{
    ifstream ifs(filepath);
    if(!ifs)
    {
        cerr << "ifs open filepath " << filepath << "error" << endl;
        return;
    }

    string word;
    while(ifs >> word)
    {
        _stopWord.insert(word);
    }

    ifs.close();
}

void buildCnDict();    //创建中文词典

void DictProducer::storeDict(const char* filepath)  //将词典写入文件
{
    //打开文件
    ofstream ofs(filepath);
    if(!ofs)
    {
        cerr << "ofs open filepath " << filepath << "error" << endl;
        return;
    }

    //一行写入一个单词 词频
    for(auto &elem : _dict)
    {
       ofs << elem.first << " " << elem.second << endl; 
    }
    
    ofs.close();
}

void DictProducer::getFiles()   //获取文件的绝对路径
{
    DIR* pDir = opendir(_dir.c_str());
    if(!pDir)
    {
        perror("opendir");
        cout << _dir << endl;
        return;
    }

    struct dirent* ptr;
    while((ptr=readdir(pDir)) != 0)
    {
        if(strcmp(ptr->d_name, ".") != 0 && strcmp(ptr->d_name, ".."))
        {
           _files.push_back(_dir + "/" + ptr->d_name); 
        }
    }

    closedir(pDir);
}

void pushDict(const string & word); //存储某个单词

#if 0
void showFiles() const;    //查看文件路径，作为测试用
void showDict() const;     //查看词典，作为测试用

#endif
