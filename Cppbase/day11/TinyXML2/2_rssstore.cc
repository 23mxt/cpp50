#include <string.h>
#include <iostream>
#include <vector>
#include "tinyxml2.h"
using std::cout;
using std::endl;
using std::string;
using std::vector;
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

            //获取title
            XMLElement* item_title = item->FirstChildElement("title");
            rss_item.title = item_title->GetText();

            //获取link
            XMLElement* item_link = item->FirstChildElement("link");
            rss_item.title = item_link->GetText();
            
            //获取description
            XMLElement* item_description = item->FirstChildElement("description");
            rss_item.title = item_description->GetText();

            //获取content
            XMLElement* item_content = item->FirstChildElement("content:encoded");
            rss_item.title = item_content->GetText();

            _rss.push_back(rss_item);
            item = item->NextSiblingElement();
            cout << "insert while?" << endl;
        }

#if 0
        for(auto &elem : _rss)
        {
            cout << elem.title << endl;
            cout << elem.link << endl;
            cout << elem.description << endl;
            cout << elem.content << endl;
        }
#endif
    }

private:
    vector<RssItem> _rss;//将每个解析结果放入RssItem
};


int main() {
    RssReader rssreader;
    rssreader.parseRss();
    return 0;
}

