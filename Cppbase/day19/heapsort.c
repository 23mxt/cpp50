#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define SIZE(a) (sizeof(a)/sizeof(a[0]))

#define SWAP(arr, i, j)	{		\
	int tmp = arr[i];			\
	arr[i] = arr[j];			\
	arr[j] = tmp;				\
}

void print_array(int arr[], int n) {
	for (int i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}


void heapify(int arr[], int i, int n) {
	// O(logn)
	while (i < n) {
		int lchild = 2 * i + 1;
		int rchild = 2 * i + 2;

		int maxIdx = i;
		if (lchild < n && arr[lchild] > arr[maxIdx]) {
			maxIdx = lchild;
		}
		if (rchild < n && arr[rchild] > arr[maxIdx]) {
			maxIdx = rchild;
		}

		if (maxIdx == i) break;

		SWAP(arr, i, maxIdx);

		i = maxIdx;
	}
}

void build_heap(int arr[], int n) {
	// 2i+1 <= n-1  --> i <= (n-2)/2
	for (int i = (n - 2 >> 1); i >= 0; i--) {
		heapify(arr, i, n);
	}
}

void heap_sort(int arr[], int n) {
	// 构建大顶堆
	build_heap(arr, n);	// O(n)
	
	print_array(arr, n);

	int len = n;
	while (len > 1) {
        //堆顶元素必为有序的
		// 交换堆顶元素和无序区最后一个元素
		SWAP(arr, 0, len - 1);
		len--;
		// 重新调整成大顶堆
		heapify(arr, 0, len);
	}
}

int main(void) {

	int arr[] = { 9, 5, 2, 7, 0, 1, 3, 4, 6, 8, };

	print_array(arr, SIZE(arr));
	
	heap_sort(arr, SIZE(arr));

	print_array(arr, SIZE(arr));

	return 0;
}
