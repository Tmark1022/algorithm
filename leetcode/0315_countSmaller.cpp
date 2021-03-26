/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Fri 26 Mar 2021 10:22:07 AM CST
 @ File Name	: 0315_countSmaller.cpp
 @ Description	: 315. 计算右侧小于当前元素的个数 
 ************************************************************************/
#include <iostream>
#include <iterator>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
#include <deque>
#include <unordered_map>
#include <unordered_set>
#include <set>

using namespace std;


/*
	
	solution 1: brute force; <O(n^2), O(1)>	

	solution 2: 二分 : 数组<O(n^2), O(n)> or 红黑树实现 <O(nlogn), O(n)> 

	solution 3: 归并排序 <O(nlogn), O(n)>; 相对于 leetcode 493 求重要逆序对的总个数， 该题目因为需要求原数组中的每一个位置的逆序对个数; 
				而在算法过程中， 原数组位置会发生变化， 而导致后续统计的逆序对个数不能准确地加入到对应位置上， 
				故这里使用编程技巧 索引数组 (原数组作为collation, 正在进行排序的是索引数组)
				




	solution 4: 树状数组
	solution 5: 线段树
   */


/*
// solution 1:
class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
	vector<int> ans(nums.size(), 0);
	for (int i = 0; i < nums.size(); ++i) {
		for (int j = i + 1; j < nums.size(); ++j) {
			if (nums[i] > nums[j]) ++ans[i];
		}
	}				
	return ans;
    }
};


// solution 2: 二分 + 数组
class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
	int n = nums.size();
	vector<int> ans(n, 0);
	if (n <= 1) return ans; 

	vector<int> arr = {nums[n-1]}; 
	for (int i = n-2; i >= 0; --i) {
		auto it = std::lower_bound(arr.begin(), arr.end(), nums[i]);
		ans[i] = std::distance(arr.begin(), it);
		arr.insert(it, nums[i]);
	}				
	return ans;
    }
};

// solution 2: 二分 + multiset
class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
	int n = nums.size();
	vector<int> ans(n, 0);
	if (n <= 1) return ans; 

	std::multiset<int> mset =  {nums[n-1]};
	for (int i = n-2; i >= 0; --i) {
		auto it = mset.lower_bound(nums[i]); 
		ans[i] = std::distance(mset.begin(), it);
		mset.insert(it, nums[i]);		// specify a hint of insertion
	}				
	return ans;
    }
};
*/

// solution 3: 归并排序 + 索引数组
class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
	int n = nums.size();
	vector<int> ans(n, 0);
	if (n <= 1) return ans; 

	vector<int> cache(n), index(n);  	
	for (int i = 0; i < n; ++i) index[i] = i; 
	MergeSort(index, cache, ans, nums, 0, n-1);

	return ans;
    }

    void MergeSort(vector<int> &index, vector<int> &cache, vector<int> &ans, const vector<int> &collation, int low, int high) {
	// terminator
	if (low >= high) return ;
	// sub problem
	int mid = low + ((high - low) >> 1);	
	MergeSort(index, cache, ans, collation, low, mid);
	MergeSort(index, cache, ans, collation, mid + 1, high);
	// 归并排序优化
	if (collation[index[mid]] <= collation[index[mid+1]]) return ;	
	// 计算逆序对
	for (int i = low, j = mid + 1; i <= mid; ++i) {
		while (j <= high && collation[index[i]] > collation[index[j]]) ++j;	
		ans[index[i]] += j - mid - 1; 		
	}	
	// merge
	Merge(index, cache, ans, collation, low, mid, high);	
    }

    void Merge(vector<int> &index, vector<int> &cache, vector<int> &ans, const vector<int> &collation, int low, int mid, int high) {
	int i = low, j = mid + 1, idx = low;
	while (i <= mid || j <= high) {
		cache[idx++] = i <= mid && (j > high || collation[index[i]] <= collation[index[j]]) ? index[i++] : index[j++];
	}
	copy(cache.begin() + low, cache.begin() + high + 1, index.begin() + low);
    }
};


int main(int argc, char *argv[]) {

	return 0;
}
