#include <string.h>
#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::string;
using std::vector;

#define SIZE(a) (sizeof(a)/sizeof(a[0]))

#define SWAP(arr, i, j) {		\
	int tmp = arr[i];			\
	arr[i]	= arr[j];			\
	arr[j]	= tmp;				\
}								

#define N 10

//使用模板实现一个快速排序算法
template<typename T,typename Compare=std::less<T>> 
class MyQsort 
{ 
public:     
    MyQsort(T *arr, size_t size, Compare com);     
    void quick(int left, int right, Compare &com);     
    int partition(int left, int right, Compare &com);     
    void print(); 
private:    
    vector<T> _vec; 
};


int partition(int arr[], int left, int right) {
	// 选取基准值
	int pivot = arr[right];
	int storeIdx = left;	// storeIdx: 存放下一个小于基准值的值
	for (int i = left; i < right; i++) {
		if (arr[i] < pivot) {
			SWAP(arr, storeIdx, i);
			storeIdx++;
		}
	} // i == right

	SWAP(arr, storeIdx, right);

	return storeIdx;
}

void quick_sort_helper(int arr[], int left, int right) {
	//[left, right]
	// 边界条件
	if (left >= right) return;
	// 递归公式
	int idx = partition(arr, left, right); // idx：基准值最终位于的位置

	print_array(arr, N);

	quick_sort_helper(arr, left, idx - 1);
	quick_sort_helper(arr, idx + 1, right);
}

void quick_sort(int arr[], int n) {
	quick_sort_helper(arr, 0, n - 1);
}

int main() {

    return 0;
}

