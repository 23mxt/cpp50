#include <string.h>
#include <iostream>
#include <vector>
#include <experimental/propagate_const>
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::less;

template <typename T, typename Compare = std::less<T>> 
class HeapSort 
{ 
public:  
    HeapSort(T *arr, size_t size, Compare com)
    :vec(arr, arr + size)
    {
        cout << "HeapSort(T *, size_t)" << endl;
        sort(com);
    }

    void heapAdjust(size_t left,size_t right, Compare &com);  
    void sort(Compare &com);  
    void print();
private:  
    vector<T> vec; 
};

    template <typename T, typename Compare>
void HeapSort<T,  Compare>::print()
{
    for(auto &elem : vec)
    {
        cout << elem << " ";
    }
    cout << endl;
}


    template <typename T, typename Compare>
void HeapSort<T, Compare>::heapAdjust(size_t left,size_t right, Compare &com)
{
    while(true)
    {
        int leftchild = 2 * left + 1;
        int rightchild = 2* left + 2;

        size_t maxIndex = left;

        /* if(vec[leftchild] > vec[maxIndex] && leftchild < right) */
        if(com(vec[maxIndex], vec[leftchild]) && leftchild < right)
        {
            maxIndex = leftchild;
        }

        /* if(vec[rightchild] > vec[maxIndex] && rightchild < right) */
        if(com(vec[maxIndex], vec[rightchild]) && rightchild < right)
        {
            maxIndex = rightchild;
        }

        if(maxIndex == left)
        {
            break;
        }

        //交换元素，可以要用函数模板实现
        //交换元素后，小元素要不断下坠
        T temp = vec[maxIndex];
        vec[maxIndex] = vec[left];
        vec[left] = temp;

        left  = maxIndex;
    }
}

template <typename T, typename Compare>
void HeapSort<T, Compare>::sort(Compare &com)
{
    //2i + 1 <= n-1 ---> i <= (n - 2)/ 2
    //初始化一个大根堆
    for(int  i = (vec.size() - 2)/2; i >= 0; --i)
    {
        heapAdjust(i, vec.size(), com);
    }

    //每次选出一个最大的元素
    int len = vec.size();
    while(len > 1)
    {
        //交换0和len - 1位置的元素
        T temp = vec[len - 1];
        vec[len - 1] = vec[0];
        vec[0] = temp;

        //重新调整成大根堆
        len--;
        heapAdjust(0, len, com);
    } 

}

void test()
{
    int arr[5] = {1, 3, 2, 6, 4};
    HeapSort<int> heap(arr, 5, std::less<int>());
    heap.print();

    cout << endl;
    char arr2[5] = {'a', 'e', 'f', 'v', 'b'};
    HeapSort<char> heap2(arr2, 5, std::less<char>());
    heap2.print();
}

int main() {
    test();
    return 0;
}

