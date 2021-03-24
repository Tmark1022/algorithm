/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Wed 24 Mar 2021 09:48:22 AM CST
 @ File Name	: 0493_reversePairs.cpp
 @ Description	: 493. 翻转对 
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
	solution 2: Merge sort;	<O(nlogn>, O(n)>
	solution 3: 二分查找(binary search), 可以使用数组 或 Self-balancing tree (ie: red black tree / avl)[C++ 使用multimap 或 multiset]
			使用数组时， 需要自己维护有序数组， <O(n^2), O(n)>
			使用 multiset， <O(nlogn), O(n)>

	// 后续补上
	solution 4: 树状数组(binary index tree)  
	solution 5: 线段树(segment tree)

   */

/*
// solution 1:
class Solution {
public:
    int reversePairs(vector<int>& nums) {
	    int ans = 0;
	    for (int i = 0; i < nums.size(); ++i) {
		    for (int j = i + 1; j < nums.size(); ++j) {
			    if (nums[i] > 2*static_cast<long long>(nums[j])) ++ans;
		    }		
	    }
	    return ans;
    }
};

// solution 2:
class Solution {
public:
    int reversePairs(vector<int>& nums) {
	if (nums.size() <= 1) return 0;
	vector<int> cache(nums.size(), 0);	
	return MergeSort(nums, cache, 0, nums.size() - 1);	
    }

    int MergeSort(vector<int>& nums, vector<int>& cache, int low, int high) {
	    int ans = 0;
	    // terminator
	    if (low >= high) {
		return ans;
	    }

	    // sub problem
	    int mid = low + ((high - low) >> 1); 
	    ans += MergeSort(nums, cache, low, mid);
	    ans += MergeSort(nums, cache, mid + 1, high);

	    // cal reverse pairs 
	    for (int i = low, j = mid + 1; i <= mid; ++i) {
		while (j <= high && nums[i] > 2 * static_cast<long long>(nums[j])) ++j;
		ans += j - mid - 1;
	    }

	    // merge
	    Merge(nums, cache, low, mid, high);
	    return ans;
    }

    void Merge(vector<int> &nums, vector<int> &cache, int low, int mid, int high) {
	    int i = low, j = mid + 1, idx = low; 
	    while (i <= mid || j <= high) {
		cache[idx++] =	i <= mid && (j > high || nums[i] <= nums[j]) ? nums[i++] : nums[j++];		    
	    }
	    copy(cache.begin() + low, cache.begin() + high + 1, nums.begin() + low);
    }
};

// solution 3: 数组二分
class Solution {
public:
    int reversePairs(vector<int>& nums) {
	int ans = 0;
	if (nums.size() <= 1) return ans;
	vector<int> arr = {nums[0]};				
	for (int i = 1; i < nums.size(); ++i) {
		auto it1 = std::upper_bound(arr.begin(), arr.end(), 2 * static_cast<long long>(nums[i]));
		ans += std::distance(it1, arr.end());
		arr.insert(std::upper_bound(arr.begin(), arr.end(), nums[i]), nums[i]);
	}	
	return ans;
    }
};
*/

// solution 3: self-balancing tree, 使用multiset实现
class Solution {
public:
    int reversePairs(vector<int>& nums) {
	int ans = 0;
	if (nums.size() <= 1) return ans;
	multiset<long long> mset = {nums[0]};				
	for (int i = 1; i < nums.size(); ++i) {
		auto it = mset.upper_bound(static_cast<long long>(nums[i]) * 2); 
		ans += std::distance(it, mset.end());
		mset.insert(nums[i]);
	}	
	return ans;
    }
};



int main(int argc, char *argv[]) {

	return 0;
}
