#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <iostream>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::map;
using std::unordered_map;

struct DLinkedNode
{
    int key, value;
    DLinkedNode* prev;
    DLinkedNode* next;

    DLinkedNode()
        :key(0)
         ,value(0)
         ,prev(nullptr)
         ,next(nullptr)
    {}

    DLinkedNode(int _key, int _value)
        :key(_key)
         ,value(_value)
         ,prev(nullptr)
         ,next(nullptr)
    {}
};


class LRUCache {
private:
    //用unordered_map记录下标和下标对应双链表节点（节点key,节点value)
    unordered_map<int, DLinkedNode*>cache;
    DLinkedNode* head;
    DLinkedNode* tail;
    int _size;
    int _capacity;
public:
    LRUCache(int capacity) 
    :_size(0)
    ,_capacity(capacity)
    {
        //初始化用虚拟头节点和虚拟尾节点
        //后面对头尾节点不用单独判断
        head = new DLinkedNode();
        tail = new DLinkedNode();
        head->next = tail;
        tail->prev = head;
    }

    //获取某个节点的value
    int get(int key) 
    {
        //先判断key是否存在于unordered_map
        if(!cache.count(key))
        {
            return -1;
        }
        //若存在，先找到节点的位置
        DLinkedNode* nowNode = cache[key];
        mvNodeToHead(nowNode);//更新节点到开头
        return nowNode->value;
    }

    //插入一个新节点
    void put(int key, int value) 
    {
        //若链表节点不存在,创建一个新节点
        if(!cache.count(key))
        {
            DLinkedNode* newNode = new DLinkedNode(key, value);
            cache[key] = newNode;//把该节点加入哈希表
            addNodeToHead(newNode);//把新节点加到开头
            ++_size;
            //若容量超出,删除链表的尾节点
            if(_size > _capacity)
            {
                //先在逻辑上删除尾节点
                DLinkedNode* tailNode =  removeTailNode();
                cache.erase(tailNode->key);//删除尾节点的value
                delete tailNode;//防止内存泄露
                --_size;
            }

        }
        else
        {
            //若链表节点已存在，修改链表节点的值
            DLinkedNode* existNode = cache[key];
            existNode->value = value;
            mvNodeToHead(existNode);
        }
    }

    //逻辑删除双链表节点
    void removeNode(DLinkedNode* node)
    {   
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    //把节点加到开头
    void addNodeToHead(DLinkedNode* node)
    {
        node->prev = head;
        node->next = head->next;
        head->next->prev = node;
        head->next = node;
    }

    //移动节点到开头
    void mvNodeToHead(DLinkedNode* node)
    {
        //删除原节点，逻辑删除
        removeNode(node);
        //因为是逻辑删除，节点位置还在，把节点加到开头
        addNodeToHead(node);
    }

    //删除链表尾节点
    DLinkedNode* removeTailNode()
    {
        DLinkedNode* tailNode = tail->prev;
        tail->prev = tailNode->prev;
        tailNode->prev->next = tail;
        return tailNode;
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */


int main() {
    LRUCache* lRUCache = new LRUCache(2);
    //这一步lRUCache失效了
    lRUCache->put(1, 1); // 缓存是 {1=1}
    lRUCache->put(2, 2); // 缓存是 {1=1, 2=2}
    int ret1 =lRUCache->get(1); // 返回 1
    cout << ret1 << endl;
    lRUCache->put(3, 3); // 该操作会使得关键字 2 作废，缓存是 {1=1, 3=3}
    int ret2 = lRUCache->get(2); // 返回 -1 (未找到)
    cout << ret2 << endl;
    lRUCache->put(4, 4); // 该操作会使得关键字 1 作废，缓存是 {4=4, 3=3}
    int ret3 = lRUCache->get(1); // 返回 -1 (未找到)
    cout << ret3 << endl;
    int ret4 = lRUCache->get(3); // 返回 3
    cout << ret4 << endl;
    lRUCache->get(4); // 返回 4
return 0;
}

