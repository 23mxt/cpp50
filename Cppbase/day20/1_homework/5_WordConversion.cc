#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>

using std::cout;
using std::endl;
using std::string;
using std::map;
using std::ifstream;
using std::ofstream;
using std::istringstream;

//建立映射
map<string, string> buildMap(ifstream &map_file)
{
    //map_file是转换规则的文档
    map<string, string> trans_map;
    //trans_map是转换关系的映射
    
    string key; //待转换的单词
    string value; //转换后的结果
                  //读取第一个单词到key中，并将后面的内容存入value
    while(map_file >> key  && getline(map_file, value))
    {
        //若转换正常
        if(value.size() > 1)
        {
            trans_map[key] = value.substr(1); //跳过前导空格
        }
        else
        {
            throw std::runtime_error ("this is false" + key);
        }
    }

    return trans_map;
}

//生成转换单词
const string &
transform(const string &s, const  map<string, string> &m)
{
    //实际的转换工作
    auto m_it = m.find(s);

    if(m_it != m.end())
    {
        //找到了
        return m_it->second;
    }
    else
    {
        //mei找到，返回原单词
        return s;
    }
}

//单词转换过程
void word_transfrom(ifstream &map_file, ifstream &input)
{
    auto trans_map = buildMap(map_file);    //trans_map存储转换规则
    string text;    //保存一行输入
    while(getline(input, text))
    {
        ///从要转换单词的文件是input
        istringstream iss(text); //iss用来读取每个单词
        string  word;

        bool firstword = true;
        while(iss  >> word)
        {
            if(firstword) //firstword用来控制空格
            {
                firstword = false;
            }
            else
            {
                cout << " ";
            }
                cout << transform(word,  trans_map);
        }
        cout << endl; //打印完一行
    }
}


int main() {
    ifstream map_file("map.txt");
    ifstream input("file.txt");
    word_transfrom(map_file, input);
    return 0;
}

