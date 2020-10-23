/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Wed 21 Oct 2020 03:42:41 PM CST
 @ File Name	: sort_collection.cpp
 @ Description	: 排序算法汇总
 ************************************************************************/
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cmath>

#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::cerr;

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
	// 希尔排序	
	void ShellSort(int *arr, int size, int (*cmp)(int, int ));
	// 基数排序 (计数基数排序)
	void RadixSort(int *arr, int size, int (*cmp)(int, int ));

private:
	void ShellInsert(int * arr, int size, int (*cmp)(int, int), int d);
	void CounterRadixSort(int *from, int * to, int size, int (*cmp)(int, int), int *count, int *pos, int r, int m);

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

void Solution::ShellInsert(int * arr, int size, int (*cmp)(int, int), int d)
{
	for (int i = 0; i < size - d; ++i) {
		if (cmp(arr[i], arr[i+d]) > 0) {
			int j = i; 
			int cache = arr[j+d];			

			do {
				arr[j+d] = arr[j];
				j -= d;
			} while (j >= 0 && cmp(arr[j], cache) > 0);

			arr[j+d] = cache; 
		}
	}	
}

void Solution::ShellSort(int *arr, int size, int (*cmp)(int, int ))
{
	int d_list[] = {5, 3, 1};
	int len = sizeof(d_list) / sizeof(int);
	for (int i = 0; i < len; ++i) {
		ShellInsert(arr, size, cmp, d_list[i]);
	}
}



void Solution::CounterRadixSort(int *from, int * to, int size, int (*cmp)(int, int), int *count, int *pos, int r, int m)
{
	// 清零
	bzero(count, sizeof(int) * r);
	bzero(pos, sizeof(int) * r);

	// 计算除数
	int divisor = pow(10, m);		

	// 收集过程， 计算个数	
	for (int i = 0; i < size; ++i) {
		++count[(from[i] / divisor) % 10];
	}	

	// 计算位置
	for (int i = 1; i < r; ++i) {
		pos[i] = pos[i - 1] + count[i - 1];
	}

	// 分配过程
	for (int i = 0; i <size; ++i) {
		to[pos[(from[i] / divisor) % 10]++] = from[i];
	}	
}

void Solution::RadixSort(int *arr, int size, int (*cmp)(int, int ))
{
	if (size <= 1) {
		return ;
	}

	// 基数排序需要事先知道基数有多少, 这里10进制整数， 基数0-9
	int r = 10;

	// 这里预先假定最大整数位9999，最大位数为4
	int m = 4;

	int *tmp_arr = (int*)malloc(sizeof(int) * size);
	int *count = (int*)malloc(sizeof(int) * r);	
	int *pos = (int*)malloc(sizeof(int) * r);	
	if (!tmp_arr || !count || !pos) {
		cerr << "malloc failed" << endl;
		exit(EXIT_FAILURE);	
	}

	int i = 0;
	while (i < m) {
		if (i%2) {
			CounterRadixSort(tmp_arr, arr, size, cmp, count, pos, r, i);
		} else {
			CounterRadixSort(arr, tmp_arr, size, cmp, count, pos, r, i);
		}	

		++i;
	}

	if (i%2) {
		// copy 回来
		memcpy(arr, tmp_arr, size * sizeof(int));
	}

	free(tmp_arr);
	free(count);
	free(pos);
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
	obj.RadixSort(arr, count, Compare);
	PrintArray(arr, count);	
	return 0;
}
