#include <string.h>
#include <iostream>
using std::cout;
using std::endl;
using std::string;

/* Definition for singly-linked list. */
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Soultion
{
public:
    ListNode* removeListNode(ListNode* head, int val)
    {
        //虚拟头节点保持删除节点方式一致
        ListNode* dummyHead = new ListNode();
        dummyHead->next = head;

        //cur的next用来寻找待删除的元素，因此初始化为虚拟头节点
        //因为原链表的头节点也可能是待删除的元素
        ListNode* cur = dummyHead;
        while(cur->next != nullptr)
        {
            //是要删除的节点
            if(cur->next->val == val)
            {
                cout << "hhh" << endl;
                ListNode* tmp = cur->next;
                cur->next = cur->next->next;
                cout << "hhh" << endl;
            }
            else
            {
                cur = cur->next;
            }
        }

        //dummyHead->next即为新的头节点
        head = dummyHead->next;
        cout << "now delete" << endl;
        delete dummyHead;
        return head;
    }
};

int main() {
    //复习链表的创建
    ListNode ln1(10);
    ListNode ln2(20);
    ListNode ln3(30);//栈对象可以自己回收
    ListNode ln4(40);

    ln1.next = &ln2;
    ln2.next = &ln3;
    ln3.next = &ln4;

    Soultion s;

    ListNode* cur = &ln1;
    while(cur != nullptr)
    {
        cout <<  cur->val << endl;
        cur = cur->next;
    }

    ListNode* res = s.removeListNode(&ln1, 30);

    while(res != nullptr)
    {
        cout <<  res->val << endl;
        res = res->next;
    }

    return 0;
}

