#include <string.h>
#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::string;
using std::vector;

struct RssItem {
    string title;
    string link;
    string description;
    string content;
};

class RssReader{
public:
    RssReader();
    void parseRss();//解析
    void dump(const string & filename);//输出
private:
    vector<RssItem> _rss;
};

int main() {

    return 0;
}

