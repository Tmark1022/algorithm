/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Mon 29 Mar 2021 10:53:16 AM CST
 @ File Name	: 0327_countRangeSum.cpp
 @ Description	: 327. 区间和的个数 
 ************************************************************************/
#include <iostream>
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
 *
	求区间和 可以使用 前缀和技巧	

	solution 1: brute force; 枚举起点i与终点j, 利用prefix_sum 计算区间和。<O(n^2), O(n)【不维护prefix_sum时， 时间复杂度只要O(1)】>;

	solution 2: 二分; 
			1)数组方式实现; arr 数组 是 数组前缀和S的数组元素的排序, 枚举区间和尾部j, 求有多少个起点i 符合
				lower <= S[j] - S[i] <= upper,

				因为 lower， upper 和 S[j] 是已知的， 求S[i], 我们可以把不等式转换一下
				S[j] - upper <= S[i] <= S[j] - lower	
				如果使用二分查找对应的库， 迭代器范围为 [lower_bound(S[j] - upper), upper_bound(S[j] - lower))

				<O(n^2), O(n)>

			2)使用multiset （红黑树）, 原理与数组实现一致, <O(nlogn), O(n)>

	solution 3: 归并排序; 


	solution 4: 树状数组
	solution 5: 线段树

   */


/*
// solution 1:
class Solution {
public:
    int countRangeSum(vector<int>& nums, int lower, int upper) {
	int n = nums.size(), ans = 0;
	if (n <= 0) return ans;

	// 计算前缀和
	vector<long long> prefix_sum(n + 1, 0);		// prefix_sum 表示前x个元素的和, 使用long long防止求和溢出
	for (int i = 1; i <= n; ++i) prefix_sum[i] = prefix_sum[i-1] + nums[i-1]; 

	// 暴力枚举区间起点和终点
	for (int i = 0; i < n; ++i) {
		for (int j = i; j < n; ++j) {
			long long range_sum = prefix_sum[j+1] - prefix_sum[i]; 	
			if(lower <= range_sum && range_sum <= upper) ++ans;
		}
	}
	return ans;
    }
};

// solution 2: 二分 + 数组
class Solution {
public:
    int countRangeSum(vector<int>& nums, int lower, int upper) {
	int n = nums.size(), ans = 0;
	if (n <= 0) return ans;

	// 计算前缀和
	vector<long long> prefix_sum(n + 1, 0);		// prefix_sum 表示前x个元素的和, 使用long long防止求和溢出
	for (int i = 1; i <= n; ++i) prefix_sum[i] = prefix_sum[i-1] + nums[i-1]; 

	// 枚举区间右边界
	vector<long long> arr = {prefix_sum[0]};
	for (int i = 1; i <= n; ++i) {
		auto lb = std::lower_bound(arr.begin(), arr.end(), prefix_sum[i] - upper); 
		auto rb = std::upper_bound(arr.begin(), arr.end(), prefix_sum[i] - lower); 
		ans += distance(lb, rb); 
		arr.insert(std::lower_bound(arr.begin(), arr.end(), prefix_sum[i]), prefix_sum[i]);	
	}
	
	return ans;
    }
};

// solution 2: 二分 + multiset
class Solution {
public:
    int countRangeSum(vector<int>& nums, int lower, int upper) {
	int n = nums.size(), ans = 0;
	if (n <= 0) return ans;

	// 计算前缀和
	vector<long long> prefix_sum(n + 1, 0);		// prefix_sum 表示前x个元素的和, 使用long long防止求和溢出
	for (int i = 1; i <= n; ++i) prefix_sum[i] = prefix_sum[i-1] + nums[i-1]; 

	// 枚举区间右边界
	multiset<long long> mset = {prefix_sum[0]};
	for (int i = 1; i <= n; ++i) {

		auto lb = mset.lower_bound(prefix_sum[i] - upper); 
		auto rb = mset.upper_bound(prefix_sum[i] - lower); 
		ans += distance(lb, rb); 
		mset.insert(prefix_sum[i]);	
	}
	
	return ans;
    }
};
*/

// solution 3 : 归并排序
class Solution {
public:
    int countRangeSum(vector<int>& nums, int lower, int upper) {
	int n = nums.size();
	if (n <= 0) return 0;	
	// 计算前缀和
	vector<long long> prefix_sum(n + 1, 0), cache(n + 1, 0);;
	for (int i = 1; i <= n; ++i) prefix_sum[i] = prefix_sum[i-1] + nums[i-1];	
	return MergeSort(prefix_sum, cache, 0, n, lower, upper); 	
    }
	
    int MergeSort(vector<long long> &arr, vector<long long> &cache, int low, int high, int lower, int upper) {
	// terminator
	int ans = 0;
	if (low >= high) return ans;
	// sub problem  
	int mid = low + ((high - low) >> 1);
	ans += MergeSort(arr, cache, low, mid, lower, upper);
	ans += MergeSort(arr, cache, mid + 1, high, lower, upper);
	// 求符合的区间和 
	for (int i = low, l = mid + 1, r = mid + 1; i <= mid; ++i) {
		while (l <= high && arr[l] - arr[i] < lower) ++l;		// l指向第一个合适的左边界
		while (r <= high && arr[r] - arr[i] <= upper) ++r;		// r 指向最后一个合适的右边界的后一位
		ans += r - l;
	}
	// merge
	if (arr[mid] <= arr[mid+1]) return ans;		// 归并排序优化
	Merge(arr, cache, low, mid, high);
	return ans;
    }

    void Merge(vector<long long> &arr, vector<long long> &cache, int low, int mid, int high) {
	int i = low, j = mid + 1, idx = low;
	while (i <= mid || j <= high) {
		cache[idx++] = i <= mid && (j > high || arr[i] <= arr[j]) ? arr[i++] : arr[j++]; 
	}
	std::copy(cache.begin() + low, cache.begin() + high + 1, arr.begin() + low);
    }
};




int main(int argc, char *argv[]) {

	return 0;
}
