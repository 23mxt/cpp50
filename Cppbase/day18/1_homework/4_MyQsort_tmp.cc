#include <string.h>
#include <iostream>
#include <vector>
#include <experimental/propagate_const>
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::less;

/* #define SIZE(a) sizeof(a)/sizeof(a[0]) */

template<typename T,typename Compare=std::less<T>> 
class MyQsort 
{ 
public:     
    MyQsort(T *arr, size_t size)
    :_vec(arr, arr + size)
    {
        cout << "MyQsort(T, size_t)" << endl;
    }//初始化_vec，用迭代器范围
    void quick(int left, int right);//Compare &com     
    int partition(int left, int right);// Compare &com    
    void print(); //遍历_vec
private:    
    vector<T> _vec;  //_vec存放待排序元素
};

//默认值设过后不能重复设置
template<typename T,typename Compare> 
void MyQsort<T, Compare>::print()
{
    for(auto &elem : _vec)
    {
        cout << elem << " ";
    }
    cout << endl;
}

//quick用递归方式来写
template<typename T,typename Compare> 
void MyQsort<T, Compare>::quick(int left, int right)
{
    if(left >= right)
    {
        return;
    }

    int index = partition(left, right);
    partition(left, index - 1);
    partition(index + 1, right);
}

//分区用compare进行比较
template<typename T,typename Compare> 
int MyQsort<T, Compare>::partition(int left, int right)
{
    Compare com;
    int pivot = _vec[right];
	int storeIdx = left;	// storeIdx: 存放下一个小于基准值的值
	for (int i = left; i < right; i++) {
		if (com(_vec[i], pivot)) {
			/* SWAP(_vec, storeIdx, i); */
            T temp = _vec[i];
            _vec[i] = _vec[storeIdx];
            _vec[storeIdx] = temp;
			storeIdx++;
		}
	} // i == right

    T temp = _vec[right];
     _vec[right] = _vec[storeIdx];
     _vec[storeIdx] = temp;

	return storeIdx;
}

void test()
{
    int arr[5] = {3, 5, 8, 1, 2};
    MyQsort<int> myq(arr, 5); 
    myq.print();
    myq.quick(0, 4);
    myq.print();

    cout << endl;
    char arr2[5] = {'a', 'e', 'f', 'b', 'c'};
    MyQsort<char> myq2(arr2, 5); 
    myq2.print();
    myq2.quick(0, 4);
    myq2.print();
}

int main() {
    test();
    return 0;
}

