#include "../include/WebPage.hpp"
WebPage::WebPage()
{
}
WebPage::WebPage(const string &doc, WordSegmentation &jieba)
{
    processdoc(doc, jieba);
}
int WebPage::getdocid()
{
    return _docid;
}
string WebPage::getdoctitle()
{
    return _doctitle;
}
string WebPage::getsummary()
{
    return _docsummary;
}
string WebPage::geturl()
{
    return _docurl;
}
map<string, int> &WebPage::getwordsmap()
{
    return _wordsmap;
}
void WebPage::LoadStopWordDict()
{
    string path = "../data/stop_words_zh.txt";
    std::ifstream ifs(path.c_str());
    if (!ifs)
    {
        cout << "open " << path << " failed" << endl;
        ;

        return;
    }
    string line;
    while (getline(ifs, line))
    {
        _stopwords.insert(line);
    }
    ifs.close();
}
void WebPage::pushDict()
{
    for (auto &elem : _sentence)
    {
        auto it = _stopwords.find(elem);
        if (it == _stopwords.end())
        {
            auto iter = _wordsmap.find(elem);
            if (iter == _wordsmap.end())
            {
                _wordsmap.insert(std::make_pair(elem, 1));
            }
            else
            {
                iter->second += 1;
            }
        }
        else
        {
            continue;
        }
    }
}
void WebPage::processdoc(const string &doc, WordSegmentation &jieba)
{
    _docid = atoi(((doc.substr(doc.find("<docid>") + 7, doc.find("</docid>") - doc.find("<docid>") - 7))).c_str());
    _doctitle = doc.substr(doc.find("<title>") + 7, doc.find("</title>") - (doc.find("<title>") + 7));
    _docurl = doc.substr(doc.find("<link>") + 6, doc.find("</link>") - (doc.find("<link>") + 6));
    _docsummary = doc.substr(doc.find("<description>") + 13, doc.find("</description>") - (doc.find("<description>") + 13));
    vector<string> tmp = jieba(doc);
    _sentence.swap(tmp);
    LoadStopWordDict();
    pushDict();
}