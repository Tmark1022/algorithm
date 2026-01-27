/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Mon 18 Jan 2021 02:10:52 PM CST
 @ File Name	: 0410_splitArray.cpp
 @ Description	: 410. 分割数组的最大值 
 ************************************************************************/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
#include <deque>
#include <unordered_map>
#include <unordered_set>

using namespace std;

/*
	solution 1: brute force,回溯搜索; 
			将N个元素分成M组，相当于从N个元素中找出M个分割数组的下标，上一个分割数组的下标的下一个位置 ~ 当前分割数组的下标 组成一个连续的子数组; 
			可以知道最后一个元素一定是一个分割点， 所以可以将问题变更为从 N-1 个下标中 选择 M-1 个下标的组合问题。

	solution 2: dp; 设 f(i, k) 表示 前i个元素分成k个连续数组后所有连续数组的最大和的最小值;
			存在如下状态转移方程【其中sum(i, j) 表示[i, j]区间和】:
				f(i, k) = min{max(f(j0, k-1), sum(j0+1, i)), max(f(j1, k-1), sum(j1+1, i)), .... max(f(k-1, k-1), sum(k, i))}; 
					// 其中j的取值范围为 [k-1, i)
					
			base case:	
				当i = 0 && k == 0 时， f(i,k) = 0
				对于其他的非法情况， 都使用INT_MAX作为异常数值

			tips:	
				对于求sum(k, i), 可以使用前缀和的方式来进行计算

			时空复杂度:
				时间 O(N*M*N), 空间 O(N*M)

			空间优化:
				上述状态转移方程中， 其实K的状态只与K-1有关， 可以使用一维滚动数组来进行空间优化

	solution 3: 贪心 + 二分; 对于给定的nums 和 m, 最后答案值的范围为[max(nums), sum(nums)], 可以通过二分的方式，枚举区间最大值， 看按该值能分成多少组【跟组数m比较】， 最终收敛于最终答案
			时间 O(N * log(Sum(nums)), 空间 O(1)
   */


/*
// solution 1: 回溯， 使用二进制枚举的递归实现方式来得出组合
class Solution {
public:
	int ans = INT_MAX;
	// @ m : 剩余还有多个未找到的分割点
	// @ sum : 当前待分割数组的和
	// @ max_sum : 之前所有的分割出来的连续数组的最大和 
	void BackTracking(vector<int> &nums, int idx, int m, int sum, int max_sum) {
		int len = nums.size();
		if (idx == nums.size()) {
			max_sum = max(sum, max_sum);		// 加上最后一个数组， 统计所有连续子数组的最大和	
			ans = min(ans, max_sum);
			return ;
		}
		
		// 剪枝, 剩下的数组元素已经不够划分了
		if (m > len - 1 - idx) return ;
		
		// non pick
		BackTracking(nums, idx+1, m, sum+nums[idx], max_sum);
	
		// pick
		if (m > 0) {
			max_sum = max(max_sum, sum + nums[idx]);
			BackTracking(nums, idx+1, m-1, 0, max_sum);					
		}
	}

    int splitArray(vector<int>& nums, int m) {
	    BackTracking(nums, 0, m-1, 0, 0);
	    return ans;
    }
};

// solution 2:
class Solution {
public:
    int splitArray(vector<int>& nums, int m) {
	// 求前缀和			
	int len = nums.size();	
	vector<int> prefix(len+1, 0);
	for (int i = 1; i <= len; ++i) prefix[i] = prefix[i-1] + nums[i-1];

	vector<vector<int>> dp(len + 1, vector<int>(m+1, INT_MAX));  
	dp[0][0] = 0;	
	for (int i = 1; i <= len; ++i) {
		for (int k = 1; k <= min(i, m); ++k) {
			for (int j = k-1; j < i; ++j) {
				dp[i][k] = min(dp[i][k], max(dp[j][k-1], prefix[i] - prefix[j]));
			}
		}
	}
	return dp[len][m];   	
    }
};

// solution 2: 空间优化版本
class Solution {
public:
    int splitArray(vector<int>& nums, int m) {
	// 求前缀和			
	int len = nums.size();	
	vector<int> prefix(len+1, 0);
	for (int i = 1; i <= len; ++i) prefix[i] = prefix[i-1] + nums[i-1];

	vector<int> dp(len + 1, INT_MAX);  
	dp[0]= 0;	
	for (int k = 1; k <= m; ++k) {
		for (int i = len; i >= k; --i) {
			for (int j = k-1; j < i; ++j) {
				dp[i] = min(dp[i], max(dp[j], prefix[i] - prefix[j]));
			}
		}
	}
	return dp[len];   	
    }
};
*/

// solution 3: 贪心 + 二分
class Solution {
public:
    int splitArray(vector<int>& nums, int m) {
	int left = 0, right = 0; 	
	for (auto &e : nums) {
		left = max(left, e);
		right += e;
	}	
	
	while (left < right) {
		int mid = left + (right - left) / 2; 
		if (Splits(nums, mid) > m) left = mid + 1;	
		else right = mid;  
	}		
	return left;
    }
	
    int Splits(vector<int>& nums, int bound) {
	int cnt  = 0, sum = 0;
	for (auto &e : nums) {
		if (sum + e > bound) {
			++cnt;
			sum = e;
		} else sum += e;	
	}		
	return cnt + 1;
    }
};




int main(int argc, char *argv[]) {

	return 0;
}
