#include <time.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
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
using std::unordered_map;
using std::pair;
using std::make_pair;
using std::ifstream;
using std::ofstream;
using std::istringstream;
using std::sort;

int count = 0;//统计第几个单词的词频

//Record 记录单词---->词频
/* struct Record */
/* { */
/*     Record(const string &word, int frequency) */
/*     : _word(word) */
/*     , _frequency(frequency) */
/*     { */
/*     } */

/*     string _word; */
/*     int _frequency; */
/* }; */

/* //重载<,定义比较自定义类型的规则 */
/* bool operator<(const Record &lhs, const Record &rhs) */
/* { */
/*     return lhs._word < rhs._word; */
/* } */

//词典 用vector实现，元素是Record
//词典 用map实现，key是string，value是count
class Dictionary
{
public:
    Dictionary()
    {
        /* _dict.reserve(capa);//先开辟空间，不放元素 */
        cout << "Dictionary()"  << endl;
    }

    void read(const string &filename)
    {
        ifstream ifs(filename);
        if(!ifs)//bool operator!(){}  operator bool() {}
    {
        cerr << "ifs open file " << filename << " error!" << endl;
        return;
    }

    string line;
    while(getline(ifs, line))
    {
        istringstream iss(line);//串IO，内存
        string word;

        while(iss >> word, !iss.eof())//word可能就是不规范abc123
        {
            //newWord是处理之后的新单词
            string newWord = dealWord(word);

            //把新的单词插入到vector里面
            /* insert(newWord); */
            ++_dict[newWord];
        }
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

        for(auto it = _dict.begin(); it != _dict.end(); ++it)
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
#if 0
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
#endif 
private:
    unordered_map<string, int> _dict;
};

int main(int argc, char **argv)
{
    Dictionary dictionary;
    cout << "before reading..." << endl;
    time_t beg = time(NULL);
    dictionary.read("The_Holy_Bible.txt");
    /* dictionary.read("tml.txt"); */
    time_t end  = time(NULL);
    cout << "time : " << (end - beg) << "s" << endl;
    cout << "after reading..." << endl;
    dictionary.store("dictMap.dat");
    return 0;
}

