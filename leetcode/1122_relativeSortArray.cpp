/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Fri 19 Mar 2021 11:49:58 AM CST
 @ File Name	: 1122_relativeSortArray.cpp
 @ Description	: 1122. 数组的相对排序
 ************************************************************************/
#include <iostream>
#include <type_traits>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
#include <deque>
#include <unordered_map>
#include <unordered_set>
#include <functional>

using namespace std;

/*
	solution 1: 自定义排序规则，根据arr2 指定排序规则， 对arr1进行进行排序即为最终结果;
		排序实现:	
			1) 标准库 sort
			2) 手写10大排序算法 （当做练习）
				冒泡		bubble sort
				选择		selection sort
				插入排序	insertion sort
				希尔排序	shell sort
				快速排序	quick sort
				归并排序	merge sort
				堆排序(优先队列排序)	heap sort
				
				计数排序		counting sort		
				桶排序			bucket sort
				基数排序		radix sort

		时间复杂度 O(mlogm + n), 空间复杂度O(1);		其中m表示arr1.size(), n表示arr2.size();

	solution 2: 因为数组值范围为 0~1000， 所以可以使用计数排序的方式收集arr1每一个元素的出现频次， 然后按照arr2的元素次序 构造结果。	
		时间复杂度 O(m+n), 空间复杂度O(1001)【1001长度数组来收集arr1元素出现频次】

   */

//solution 1: 
class Solution {
public:
    vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2) {
	unordered_map<int, int> collation;		
	int n = arr2.size();
	for (int i = 0; i < n; ++i) {
		collation[arr2[i]] = i - n;
	}
	SortHelp(arr1, collation);
	return arr1;
    }

	void SortHelp(vector<int>& arr1, unordered_map<int, int> &collation) {	
		auto cmp = [&](int a, int b)->bool{
				return (collation.count(a) ? collation[a] : a) <= (collation.count(b) ? collation[b] : b); 
		};

		//std::sort(arr1.begin(), arr1.end(), cmp);	
		BubbleSort(arr1, cmp);
	}
	
	// 冒泡排序 O(n^2) 稳定排序  
	void BubbleSort(vector<int>& arr1, function<bool(int, int)> cmp) {
		int n = arr1.size();
		for (int i = 0; i < n - 1; ++i) {
			for (int j = 0; j < n-1-i; ++j) {
				if (!cmp(arr1[j], arr1[j+1])) swap(arr1[j], arr1[j+1]);
			}		
		}		
	}

	// 选择排序 O(N^2) 非稳定
	void SelectionSort(vector<int> &arr, function<bool(int, int)> cmp) {
		int n = arr.size(), min_idx;		
		for (int i = 0; i < n-1; ++i) {
			min_idx = i; 
			for (int j = i + 1; j < n; ++j) {
				if (!cmp(arr[min_idx], arr[j])) min_idx = j;
			}

			if (i != min_idx) swap(arr[i], arr[min_idx]); 
		}
	}

	// 插入排序 O(N^2) 稳定
	void InsertionSort(vector<int> &arr, function<bool(int, int)> cmp) {
		int n = arr.size();		
		for (int i = 0; i < n-1; ++i) {
			int j = i, tmp = arr[j+1];
			while (j >= 0 && !cmp(arr[j], tmp)) {
				arr[j+1] = arr[j];
				--j;
			}
			arr[j+1] = tmp;	
		}
	}

	// 希尔排序 O(N^2) 非稳定
	void ShellSortHelp(vector<int> &arr, function<bool(int, int)> cmp, int d) {
		int n = arr.size();		
		for (int i = 0; i < n-d; ++i) {
			int j = i, tmp = arr[j+d];
			while (j >= 0 && !cmp(arr[j], tmp)) {
				arr[j+d] = arr[j];
				j -= d;
			}
			arr[j+d] = tmp;	
		}
	}

	void ShellSort(vector<int> &arr, function<bool(int, int)> cmp) {
		vector<int> distance = {5, 3, 1};
		for (auto &d : distance) ShellSortHelp(arr, cmp, d); 
	}

};

/*
//solution 2: 
class Solution {
public:
    vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2) {
	vector<int> freq(1001, 0);		
	for (auto &e : arr1) ++freq[e];
	
	// 在arr1 上原地改	
	//int idx = 0;		
	//for (auto &e : arr2) {
	//	for (int i = 0; i < freq[e]; ++i) arr1[idx++] = e;	
	//	freq[e] = 0;
	//}	
	//for (int i = 0; i < freq.size(); ++i) {
	//	for (int j = 0; j < freq[i]; ++j) arr1[idx++] = i;	
	//}	
	//return arr1;
	
	// 新建数组存储结果
	vector<int> ans;
	for (auto &e : arr2) {
		ans.insert(ans.end(), freq[e], e);
		freq[e] = 0;
	} 
	for (int i = 0; i < freq.size(); ++i) {
		if (!freq[i]) continue;
		ans.insert(ans.end(), freq[i], i);
	}	
	return ans;
    }
};
*/

int main(int argc, char *argv[]) {

	return 0;
}
