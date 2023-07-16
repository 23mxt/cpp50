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
    void parseRss(XMLNode* node)//解析xml文件
    {
        //解析RSS文件，将Rssitem存入vector
        if(node == nullptr)
        {
            return;
        }

        RssItem tmp;
        if(node->ToDeclaration())
        {
            auto declaration = dynamic_cast<XMLDeclaration*>(node);
            tmp.description = declaration->Value();
            _rss.push_back(tmp);
            cout << "XMLDeclaration 声明， value = " << declaration->Value() << endl;
        }

        if(node->ToElement())
        {
             auto element = dynamic_cast<XMLElement*>(node);
             //这段if要改，先测试下
             tmp.title = element->Value();
            _rss.push_back(tmp);
             cout << "XMLElement 元素， value = " << element->Value() << endl;
        }

        XMLNode* child = node->FirstChild();
        while(child != nullptr)
        {
            parseRss(child);
            child = child->NextSibling();
        }
    }

private:
    vector<RssItem> _rss;//将每个解析结果放入RssItem
};

//遍历xml文件，读取xml文件内容，测试
#if 0
void traverse(XMLNode* node)
{
    if(node == nullptr)
    {
        return;
    }

    if(node->ToDeclaration())
    {
        auto declaration = dynamic_cast<XMLDeclaration*>(node);
        cout << "XMLDeclaration 声明， value = " << declaration->Value() << endl;
    }

    if(node->ToElement())
    {
        auto element = dynamic_cast<XMLElement*>(node);
        cout << "XMLElement 元素， value = " << element->Value() << endl;
        /* const XMLAttribute* attribute = element->FirstAttribute(); */
        /* while(attribute != nullptr) */
        /* { */
        /*     cout << "\t属性" << attribute->Name() << "=" << attribute->Value() << endl; */
        /*     attribute = attribute->Next(); */
        /* } */
    }

    XMLNode* child = node->FirstChild();
    while(child != nullptr)
    {
        traverse(child);
        child = child->NextSibling();
    }
}
#endif

int main() {
    //打开文件
    XMLDocument xmlDocument;
    XMLError error = xmlDocument.LoadFile("coolshell.xml");
    if(error != XML_SUCCESS)
    {
        cout << "读取 coolshell.xml 失败" << xmlDocument.ErrorStr() << endl;
        return -1;
    }
    
    RssReader rssreader;
    rssreader.parseRss(&xmlDocument);
    return 0;
}

