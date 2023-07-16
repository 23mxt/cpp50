#if 0
使用tinyXml2库解析RSS文件，并生成一个网页库pagelib.txt

tinyXml2 -- https://github.com/leethomason/tinyxml2

rss -- http://www.runoob.com/rss/rss-tutorial.html

对于html的标签需要使用正则表达式进行过滤，正则表达式需要用到标准库中的std::regex

参考接口：

//创建RSS的格式
//设置要解析的内容
//没有属性，都是元素
struct RssItem {    //RSS项目
    string title; //标题
    string link;  //链接
    string description; //描述
    string content; //内容
};
   
//通过TinyXML2解析
class RssReader{    
public:
    RssReader();
    void parseRss();//解析 
                    //第一步解析RSS文件，将rssitem存入vector，测试
                    //第二步解析后用正则表达式（C++ref）过滤rssitem，将过滤好的rssitem存入vector,测试
    void dump(const string & filename);//格式化输出到txt文件,ofstream
private:
    vector<RssItem> _rss;//将解析结果放入RSSItem
};  
要求：最后生成一个 pagelib.txt, 其格式如下:

//每个RSSITEM都包含下面内容，自增除外
//遍历vector输入txt即为所求
<doc>
   <docid>1</docid> //自增
   <title> ... </title>
   <link> ...  </link>
   <description>...</description>
   <content> ... </content>
</doc> //   /表示标签结束
<doc>
   ...
</doc>
<doc>
   ...
</doc>
提示：RSS文件解析作业思路： xml(已有) --> rss(一种格式) --> tinyxml2（对该格式进行操作） --> std::regex

#endif
