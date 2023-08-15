#ifndef __WebPage_H__
#define __WebPage_H__
#include "func.h"
#include "WordSegmentation.h"
#include <string>
#include <map>
#include <unordered_set>
#include <vector>
using namespace std;
class WebPage
{
public:
    WebPage();
    WebPage(const string &, WordSegmentation &);
    int getdocid();
    string getdoctitle();
    string getsummary();
    string geturl();
    map<string, int> &getwordsmap();

private:
    void LoadStopWordDict();
    void pushDict();
    void processdoc(const string &,WordSegmentation &);

private:
    int _docid;
    string _doctitle;
    string _docurl;
    string _docsummary;
    vector<string> _sentence;
    unordered_set<string> _stopwords;
    map<string, int> _wordsmap;
};
#endif
