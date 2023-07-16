#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include "tinyxml2.h"
using std::cout;
using std::endl;
using std::regex;
using std::string;
using std::vector;
using std::ofstream;
using namespace tinyxml2;

//设置TinyXML2的解析出的RSS的格式
struct RssItem
{
    //默认公有
    string title;
    string link;
    string description;
    string content;
};

class RssReader
{
public:
    RssReader() {}
    void parseRss()//解析xml文件
    {
        XMLDocument xmlDocument;
        XMLError error = xmlDocument.LoadFile("coolshell.xml");
        if(error != XML_SUCCESS)
        {
            cout << "读取 coolshell.xml 失败" << xmlDocument.ErrorStr() << endl;
            return ;
        }

        //树状结构
        //获取根节点
        XMLElement* rss = xmlDocument.RootElement();
        //获取channel节点
        XMLElement* channel = rss->FirstChildElement("channel");
        //获取item节点
        XMLElement* item = channel->FirstChildElement("item");

        
        while(item)
        {
            //解析RSS文件，将RSSITEM存入vector
            RssItem rss_item;
            regex reg("<[^>]*>");

            //获取title
            XMLElement* item_title = item->FirstChildElement("title");
            rss_item.title = item_title->GetText();

            //获取link
            XMLElement* item_link = item->FirstChildElement("link");
            rss_item.title = item_link->GetText();
            
            //获取description
            XMLElement* item_description = item->FirstChildElement("description");
            rss_item.title = item_description->GetText();
            rss_item.description = regex_replace(rss_item.description, reg, "");

            //获取content
            XMLElement* item_content = item->FirstChildElement("content:encoded");
            rss_item.title = item_content->GetText();
            rss_item.content = regex_replace(rss_item.content, reg, "");

            _rss.push_back(rss_item);
            item = item->NextSiblingElement();
            /* cout << "insert while?" << endl; */
        }

/* #if 0 */
        for(auto &elem : _rss)
        {
            cout << elem.title << endl;
            cout << elem.link << endl;
            cout << elem.description << endl;
            cout << elem.content << endl;
        }
/* #endif */
    }
//内容按指定格式输出到文件
void dump()
{
    ofstream ofs("pagelib.txt");

    for(size_t idx = 0; idx < _rss.size(); ++idx){
        ofs << "<doc>" << "\n"
            << "\t" << "<docid>" << idx + 1 << "</docid>" << "\n"
            << "\t" << "<title>" << _rss[idx].title << "</title>" << "\n"
            << "\t" << "<link>" << _rss[idx].link << "</link>" << "\n"
            << "\t" << "<description>" << _rss[idx].description << "</description>" << "\n"
            << "\t" << "<content>" << _rss[idx].content << "</content>" << "\n"
            << "</doc>" << endl;
    }
    ofs.close();
}   
private:
    vector<RssItem> _rss;//将每个解析结果放入RssItem
};


int main() {
    RssReader rssreader;
    rssreader.parseRss();
    rssreader.dump();
    return 0;
}

