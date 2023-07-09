#include <time.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::vector;
using std::sort;
using std::ifstream;
using std::ofstream;
using std::istringstream;

struct Record
{
    Record(const string word, int frequency)
    :_word(word)
    ,_frequency(frequency)
    {

    }

friend bool operator<(const Record &lhs, const Record &rhs);

	string _word;
	int _frequency;
};

//字典序，排序用
bool operator<(const Record &lhs, const Record &rhs)
{
    return lhs._word < rhs._word;
}//true?

class Dictionary
{
public:
    //提前开辟词典的空间
    Dictionary(int capa)
    {
        _dict.reserve(capa);
    }

    //读取圣经
    void read(const std::string &filename)
    {
        ifstream ifs(filename);
        if(!ifs)
        {
            cerr << "ifs open"<< filename << "error"  << endl;//test
            return;
        }

        string line;
        while(getline(ifs, line))
        {
            //提取单词
            istringstream iss(line);
            string word;
            
            while(iss >> word, iss.eof()) 
            {
               //处理读到的单词
               string newword = handle(word);
               
               //压入词典
                insert(newword);
            }
        }
        //排序
        sort(_dict.begin(), _dict.end());

        ifs.close();
    }

    void store(const string &filename)
    {
        ofstream ofs(filename);
        if(!ofs)
        {
            cerr << "ofs open" << filename << "error" << endl;
            return;
        }

        for(int idx = 0; idx < _dict.size(); ++idx)
        {
            ofs << _dict[idx]._word << "  "
                << _dict[idx]._frequency << endl;
        }

        ofs.close();
    }
    
    string handle(string &word)
    {
        size_t i;
        for(i = 0; i != word.size(); ++i) 
        {
            if(!isalpha(word[i]))
            {
                word[i] = ' ';
                return word;
            }
        }

        return word;
    }

    void insert(const string &word)
    {
        //不可能是空串，不用判断

        for(size_t idx = 0; idx < _dict.size(); ++idx) 
        {
            if(word == _dict[idx]._word)
            {
                _dict[idx]._frequency++;
                break;
            }
        

             //若为新单词
            if(idx == _dict.size())
            {
                _dict.push_back(Record(word,1));    
            }
        }
    }


private:
	vector<Record> _dict;
};

int main() {
    Dictionary dict(13000);
    
    time_t begtime = time(NULL);
    cout << "before reading " << endl;
    dict.read("The_Holy_Bible.txt");
    cout << "after reading ..." << endl;
    time_t endtime = time(NULL);
    cout << "read use " << endtime - begtime << "s" << endl;

    dict.store("Dictionary.dat");
    return 0;
}

