/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Wed 21 Oct 2020 03:42:41 PM CST
 @ File Name	: sort_collection.cpp
 @ Description	: 排序算法汇总
 ************************************************************************/
#include <stdlib.h>
#include <time.h>

#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int Compare(int a, int b) 
{
	return a <= b ? -1 : 1;	
}

void PrintArray(int * arr, int size)
{
	for (int idx = 0; idx < size; ++idx) {
		cout << arr[idx] << " ";
	}
	cout << endl;
}

class Solution {
public:

	// 冒泡排序 
	void BubbleSort(int * arr, int size, int (*cmp)(int, int));
	// 冒泡排序（优化）
	void BubbleSortOptimal(int * arr, int size, int (*cmp)(int, int));
	// 选择排序
	void SelectionSort(int * arr, int size, int (*cmp)(int, int));
	// 插入排序
	void InsertSort(int * arr, int size, int (*cmp)(int, int));
};

void Solution::BubbleSort(int *arr, int size, int (*cmp)(int, int)) 
{
	for (int i = 0; i < size - 1; ++i) 
		for (int j = 0; j < size -1 - i; ++j) {
			if (cmp(arr[j], arr[j+1]) > 0) {
				// exchange
				arr[j] = arr[j] ^ arr[j+1];
				arr[j+1] = arr[j] ^ arr[j+1];
				arr[j] = arr[j] ^ arr[j+1];
			}
		}	
}

void Solution::BubbleSortOptimal(int *arr, int size, int (*cmp)(int, int)) 
{
	// 减少本来就比较有序数组的的判断次数
	bool change = true;
	for (int i = 0; i < size - 1 && change; ++i) {
		change = false;
		for (int j = 0; j < size -1 - i; ++j) {
			if (cmp(arr[j], arr[j+1]) > 0) {
				// exchange
				arr[j] = arr[j] ^ arr[j+1];
				arr[j+1] = arr[j] ^ arr[j+1];
				arr[j] = arr[j] ^ arr[j+1];

				change = true;
			}
		}	
	}
}

void Solution::SelectionSort(int *arr, int size, int (*cmp)(int, int)) 
{
	for (int i = 0; i < size - 1; ++i) {	
		int k = i;
		for (int j = i + 1; j < size; ++j) {
			if (cmp(arr[k], arr[j]) > 0) {
				k = j;
			}
		}	
			
		if (i != k) {
			// exchange
			arr[k] = arr[k] ^ arr[i];
			arr[i] = arr[k] ^ arr[i];
			arr[k] = arr[k] ^ arr[i];
		}

	}
}

void Solution::InsertSort(int *arr, int size, int (*cmp)(int, int)) 
{

	for (int i = 0; i < size - 1; ++i) {	
		if (cmp(arr[i], arr[i+1]) > 0) {	
			// i 为有序区边界， i+1为当前要处理的值的下标
			// 在有序区域中找到合适的位置插入arr[j+1] 的值
			int j = i;
			int cache = arr[j + 1];
			do {
				arr[j + 1] = arr[j];
				--j;
			} while (j >= 0 && cmp(arr[j], cache) > 0);

			// insert 
			arr[j+1] = cache;
		}
	}
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		cout << "usage : " << argv[0] << " count" << endl;
		exit(EXIT_FAILURE);
	}		
	long count = atol(argv[1]);
	if (count <= 0) {
		cout << "parameter count (" << count << ") invalid" << endl;
		exit(EXIT_FAILURE);
	}

	srand(time(NULL));
	int * arr = (int *)malloc(sizeof(int) * count);
	for (long i = 0; i < count; ++i) {
		arr[i] = random() % 10000;
	}	

	Solution obj;
	obj.InsertSort(arr, count, Compare);
	PrintArray(arr, count);	
	return 0;
}
