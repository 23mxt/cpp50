#if 0
文本查询

该程序将读取用户指定的任意文本文件【当前目录下的china_daily.txt】，
然后允许用户从该文件中查找单词。查询的结果是该单词出现的次数，并列
出每次出现所在的行。如果某单词在同一行中多次出现，程序将只显示该行
一次。行号按升序显示。

要求：
a. 它必须允许用户指明要处理的文件名字。
// 打开文件流

b. 程序将存储该文件的内容，以便输出每个单词所在的原始行。
vector<string> lines;//O(1) 读取文本内容

c. 它必须将每一行分解为各个单词，并记录每个单词所在的所有行。
在输出行号时，应保证以升序输出，并且不重复。

map<string, set<int> > wordNumbers; //set记录单词所在的行号，不用去重，一个单词的行号用insert加入
map<string, int> dict; //词频统计

d. 对特定单词的查询将返回出现该单词的所有行的行号。

e. 输出某单词所在的行文本时，程序必须能根据给定的行号从输入
文件中获取相应的行。

示例：
使用提供的文件内容，然后查找单词 "element"。输出的前几行为：
---------------------------------------------
element occurs 125 times.
(line 62) element with a given key. //set默认升序,字符串拼接
(line 64) second element with the same key.
(line 153) element |==| operator.
(line 250) the element type.
(line 398) corresponding element.
---------------------------------------------

程序接口[可选]:
class TextQuery
{
public:
//......
void readFile(const string filename);//打开文件，按行读取文件并保存到vector，打印vector测试一下；
                                     //第二步词频统计，
                                     //并在统计词频时，统计每个单词所在的行号，用_wordNumbers统计
                                     //
void query(const string & word);//在_wordNumbers查询单词，读取其中的行号，打印到终端
                                //第一步：打印出现次数
                                //第二步：找到单词位置,已知word find 返回迭代器/ []返回value  set
                                //第三步：读取行号 打印行号的内容

private:
//......
vector<string> _lines;//O(1) 一次读一行，压入vector
map<string, set<int> > _wordNumbers;//the the
map<string, int> _dict;//
};

#endif

//程序测试用例
int main(int argc, char *argv[])
{
string queryWord("hello");

TextQuery tq;
tq.readFile("test.dat");
tq.query(queryWord);
return 0;
}
