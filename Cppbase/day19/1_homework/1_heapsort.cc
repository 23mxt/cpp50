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
    HeapSort(T *arr, size_t size)
        :vec(arr, arr + size)
    {
        cout << "HeapSort(T *, size_t)" << endl;
    }

    void heapAdjust(size_t left,size_t right);  
    void sort();  
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
void HeapSort<T, Compare>::heapAdjust(size_t left,size_t right)
{
    while(true)
    {
        int leftchild = 2 * left + 1;
        int rightchild = 2* left + 2;

        size_t maxIndex = left;

        if(vec[leftchild] > vec[maxIndex] && leftchild < right)
        {
            maxIndex = leftchild;
        }

        if(vec[rightchild] > vec[maxIndex] && rightchild < right)
        {
            maxIndex = rightchild;
        }

        if(maxIndex == left)
        {
            break;
        }

        //交换元素后，小元素要不断下坠
        T temp = vec[maxIndex];
        vec[maxIndex] = vec[left];
        vec[left] = temp;

        left  = maxIndex;
    }
}

template <typename T, typename Compare>
void HeapSort<T, Compare>::sort()
{
    //2i + 1 <= n-1 ---> i <= (n - 2)/ 2
    //初始化一个大根堆
    for(int  i = (vec.size() - 2)/2; i >= 0; --i)
    {
        heapAdjust(i, vec.size());
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
        heapAdjust(0, len);
    } 

}

void test()
{
    int arr[5] = {1, 3, 2, 6, 4};
    HeapSort<int> heap(arr, 5);
    heap.print();
    heap.sort();
    heap.print();

    cout << endl;
    char arr2[5] = {'a', 'e', 'f', 'v', 'b'};
    HeapSort<char> heap2(arr2, 5);
    heap2.print();
    heap2.sort();
    heap2.print();
}

int main() {
    test();
    return 0;
}

