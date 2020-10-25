/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Sun 25 Oct 2020 10:39:12 PM CST
 @ File Name	: 0215_findKthLargest.cpp
 @ Description	: 215. 数组中的第K个最大元素
 ************************************************************************/
#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>

using namespace std;

class Solution {
public:

	void Swap(vector<int>& nums, int i, int j) {
		int tmp = nums[i];
		nums[i] = nums[j];
		nums[j] = tmp; 
	}

	int Partition(vector<int>& nums, int low, int high) {
		if (low < high) {
			// 随机选取pivot，避免算法退化 	
			int r = low + (random()%(high - low + 1));
			Swap(nums, low, r);
		}

		int pivot_value = nums[low];
		int pivot = low;		// pivot 下标
		for (int i = low + 1; i <= high; ++i) {
			if (nums[i] < pivot_value) 
				Swap(nums, ++pivot, i);
		}	

		Swap(nums, pivot, low);

		return pivot;
	}

	void QuickSort(vector<int>& nums, int low, int high) {
		if (low >= high) {
			return ;
		}	

		int pivot = Partition(nums, low, high);
		if (low < pivot - 1) QuickSort(nums, low, pivot - 1); 
		if (pivot + 1 < high) QuickSort(nums, pivot + 1, high); 
	}

	/*
	// solution 1: 暴力, 排序后取第K位元素
	int findKthLargest(vector<int>& nums, int k) {
		QuickSort(nums, 0, nums.size() - 1);
		return nums[nums.size() - k];
    	}
	*/

	void PrintVector(vector<int>& vec) {
		cout <<"--------------" << endl;
		for (auto elem : vec) {
			cout << elem << " ";
		}
		cout << endl;
	}


	/*
	// solution 2: 使用小顶堆辅助
	// c++ 的堆操作接口什么狗屎垃圾, 一波操作下来比快排后的还要慢， 妈的
	int findKthLargest(vector<int>& nums, int k) {
		vector<int> heap;
		make_heap(heap.begin(), heap.end());
		for (auto beg = nums.begin(); beg != nums.end(); ++beg) {
			heap.push_back(*beg);
			push_heap(heap.begin(), heap.end(), greater<int>());
			if (heap.size() > k) {
				pop_heap(heap.begin(), heap.end(), greater<int>());
				heap.pop_back();
			}
		}	
		
		pop_heap(heap.begin(), heap.end(), greater<int>());
		return heap.back();
    	}
	*/
	
	// solution 3: 快速选择
	int findKthLargest(vector<int>& nums, int k) {
		int low = 0, high = nums.size() - 1;
		int res = nums.size() - k;		// 实现的partition是按照小到大的, 故要反过来
		int pivot;
	
		while (low <= high) {
			pivot = Partition(nums, low, high);
			if (pivot == res) {
				break;				
			}
			if (pivot < res) {
				low = pivot + 1;
			} else {
				high = pivot - 1;
			}
		}
		
		return nums[res];

    	}


};


int main(int argc, char *argv[]) {
	vector<int> vec{3,2,3,1,2,4,5,5,6};
	Solution obj;
	cout << obj.findKthLargest(vec, 2) <<endl;
	
	return 0;
}
