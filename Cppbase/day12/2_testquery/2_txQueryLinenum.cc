#include <time.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <utility>
#include <fstream>
#include <sstream>
#include <algorithm>

using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::vector;
using std::map;
using std::set;
using std::pair;
using std::make_pair;
using std::ifstream;
using std::ofstream;
using std::istringstream;
using std::sort;

//词典 用map实现，key是string，value是count
class TextQuery
{
public:
    TextQuery()
    {
        cout << "TextQuery()"  << endl;
    }

    void read(const string &filename)
    {
        ifstream ifs(filename);
        if(!ifs)
        {
            cerr << "ifs open file " << filename << " error!" << endl;
            return;
        }

        string line;
        int linenum = 0;
        while(getline(ifs, line))
        {
            _lines.push_back(line); 
            linenum++;
            istringstream iss(line);//串IO，内存
            string word;

            while(iss >> word, !iss.eof())//word可能就是不规范abc123
            {
                //newWord是处理之后的新单词
                string newWord = dealWord(word);
                
                //把新的单词插入map
                ++_dict[newWord];
                //统计每个单词所在的行号，用_wordNumbers统计
                //取下标返回set,插入行号
                _wordNumbers[newWord].insert(linenum);
            }
        }

        //测试_wordNumbers统计的行号
        map<string, set<int>>::iterator it;
        for(it = _wordNumbers.begin(); it != _wordNumbers.end(); ++it)
        {
            for(auto &elem : it->second)
            {
                cout << it->first << "     " ;
                cout << elem << endl;
            }
            /* set<int>::iterator itset; */
            /* for(itset = it->second.begin(); itset != it->second.end(); ++itset) */
            /* { */
            /*     cout << itset << endl; */
            /* } */
        }
        ifs.close();
    }

    //将单词与词频存储到文件中
    void store(const string &filename)
    {
        ofstream ofs(filename);
        if(!ofs)
        {
            cerr << "ofs open " << filename << " error" << endl;
            return;
        }

        map<string, int>::iterator it;
        for(it = _dict.begin(); it != _dict.end(); ++it)
        {
            ofs << it->first << "   " 
                << it->second << endl;
        }

        ofs.close();
    }

    //对不符合要求的单词进行处理
    string dealWord(const string &word)
    {
        for(size_t idx = 0; idx != word.size(); ++idx)
        {
            if(!isalpha(word[idx]))
            {
                return string();//以空串进行替换
            }
        }

        return word;
    }

    //把结果插入到map中
    void insert(string &word)
    {
        if(word == string())
        {
            return;
        }

        map<string, int>::iterator it;
        for(it = _dict.begin(); it != _dict.end(); ++it)
        {
            if(it->first == word)
            {
                ++it->second;
                break;
            }
        }

        cout << "insert really?" << endl;
        _dict.insert(pair<string, int>(word, 1));
    }

private:
    vector<string>_lines;//一次读一行，压入vector
    map<string, set<int>> _wordNumbers;//统计每个单词所在的行号
    map<string, int> _dict;//词频统计
};

int main(int argc, char **argv)
{
    TextQuery dictionary;
    cout << "before reading..." << endl;
    time_t beg = time(NULL);
    /* dictionary.read("The_Holy_Bible.txt"); */
    dictionary.read("querytest.txt");
    time_t end  = time(NULL);
    cout << "time : " << (end - beg) << "s" << endl;
    cout << "after reading..." << endl;
    dictionary.store("dictVector.dat");
    return 0;
}

