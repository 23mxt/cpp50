#include <string>
#include <vector>
#include <map>
#include <deque>
#include <stack>
#include <unordered_map>
#include <iostream>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::map;
using std::stack;
using std::unordered_map;

class Solution {
public:
    bool isValid(string s) {
        stack<char>st;
        for(int i = 0; i < s.size(); ++i)
        {
            //如果是括号，就往栈压入对应括号
            if(s[i] == '(')
            {
                st.push(')');
            }
            else if(s[i] == '[')
            {
                st.push(']');
            }
            else if(s[i] == '{')
            {
                st.push('}');
            }
            //如果栈提前空了，说明右括号多了
            //如果栈顶和s[i]不相同，说明类型不匹配
            //这两个任何一个满足都说明括号不匹配
            else if(st.empty() || s[i] != st.top())
            {
                return false;
            }
            else 
            {
                st.pop(); //s[i]是右括号
            }
        }

        //栈非空，左括号多了
        return st.empty();
    }
};

void test()
{
#if 0
    输入：s = "()"
        输出：true
        示例 2：

        输入：s = "()[]{}"
        输出：true
        示例 3：

        输入：s = "(]"
        输出：false
#endif
    Solution solu;
    string s = "()";
    bool ret = solu.isValid(s);
    cout << ret << endl;

    string s2 = "()[]{}";
    ret = solu.isValid(s2);
    cout << ret << endl;

    string s3 = "(]";
    ret = solu.isValid(s3);
    cout << ret << endl;
}

int main() 
{
    test();
    return 0;
}

