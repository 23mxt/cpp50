#include <string>
#include <vector> 
#include <deque>
#include <queue>
#include <climits>
#include <map>
#include <unordered_map>
#include <iostream>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::queue;
using std::map;
using std::unordered_map;

class Solution {
    unordered_map<string, int>wordId;   //词典，存放每个单词对应的id
    vector<vector<int>>edge;    //edge保存与每个节点相连接的边
    int wordNum = 0;    

public:
    void addWord(string& word)
    {
        //先判断单词是否存在
        if(!wordId.count(word))
        {
            //若单词不存在，将单词加入哈希表
            wordId[word] = wordNum++;
            edge.emplace_back(); //创建与该单词相连接的边的集合
        }       
    }

    //给单词增加关联的边
    void addEdge(string& word)
    {
        //若该单词不存在，创建该单词
        addWord(word);
        int id1 = wordId[word]; //先获取原单词的id
        for(char &it : word)
        {
            char tmp = it;
            it = '*';
            addWord(word);  //添加与原单词关联的单词
            int id2 = wordId[word];
            edge[id1].push_back(id2);
            edge[id2].push_back(id1);
            it = tmp;   //添加完关联边，把单词还原，继续添加
        }
    }

    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        //先添加转换链表中单词的关联边
        for(string &word : wordList)
        {
            addEdge(word);
        }

        //添加beginWord的关联边
        addEdge(beginWord);
        //如果结尾单词在词典中不存在，直接return -1 
        if(!wordId.count(endWord))
        {
            cout << "目标单词不存在，转换失败" << endl;
            return -1;
        }

        //初始化dis数据结构，用vector
        vector<int>dis(wordNum, INT_MAX);

        //用队列来模拟ladder，并通过dis记录距离
        int beginWordId = wordId[beginWord];
        int endWordId = wordId[endWord];
        dis[beginWordId] = 0;
        queue<int> que;
        que.push(beginWordId);
        while(!que.empty())
        {
            //先获取当前队头的id
            int nowId = que.front();
            que.pop();
            //若为目标单词，返回距离
            if(nowId == endWordId)
            {
                return dis[nowId]/2 + 1;    //因为添加了*作为关联节点，距离多了一倍
                                            //因为忽略了起始节点的贡献，距离+1 
            }
            //不为目标单词，继续向下遍历
            for(int &it : edge[nowId])
            {
                if(dis[it] == INT_MAX)
                {
                    //若该边没遍历过，因为词典中是不存在重复字符串的
                    dis[it] = dis[nowId] +1;//距离+1
                    que.push(it);  //把该边加入队列
                }
            }
        }
        cout << "目标单词转换失败" << endl;
        return -1;
    }
};

void test()
{
    /* 输入：beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log","cog"] */
    /* 输出：5 */
    /* 解释：一个最短转换序列是 "hit" -> "hot" -> "dot" -> "dog" -> "cog", 返回它的长度 5。 */
    Solution solu;
    string beginWord = "hit";
    string endWord = "cog";
    vector<string> wordList;
    wordList.push_back("hot");
    wordList.push_back("dot");
    wordList.push_back("dog");
    wordList.push_back("lot");
    wordList.push_back("log");
    wordList.push_back("cog");
    int ret = solu.ladderLength(beginWord, endWord, wordList);
    cout << "查找结果为：" << ret << endl;

    /* 输入：beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log"] */
/* 输出：0 */
/* 解释：endWord "cog" 不在字典中，所以无法进行转换。 */
    Solution solu2;
    string beginWord2 = "hit";
    string endWord2 = "cog";
    vector<string> wordList2;
    wordList2.push_back("hot");
    wordList2.push_back("dot");
    wordList2.push_back("dog");
    wordList2.push_back("lot");
    wordList2.push_back("log");
    int ret2 = solu2.ladderLength(beginWord, endWord, wordList2);
    cout << "查找结果为：" << ret2 << endl;
}

int main() {
    test();
    return 0;
}

