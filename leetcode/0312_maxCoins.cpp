/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Mon 25 Jan 2021 10:53:47 AM CST
 @ File Name	: 0312_maxCoins.cpp
 @ Description	: 312. 戳气球 
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
	solution 1: 回溯, 时间复杂度为O(N!) 
	
	solution 2: 记忆化递归; 需要注意子问题划分， 子问题需要相互独立;	
			设f(i, j)表示开区间(i, j)的获得最大硬币数量, K表示区间(i, j)最后戳爆的气球ID， 存在如下状态转移方程: 
				f(i, j) = max{nums[i] * nums[k] * nums[j] + f(i, k), + f(k, j), ...};		// i < k < j
				
				当 i >= j - 1; 开区间中没有可选的K， 所以f(i, j) = 0	

	solution 3: dp; 最优子结构 + 重叠子问题
   */


/* 
// solution 1: 回溯
class Solution {
public:
	int ans = 0; 
	void BackTracking(vector<int>& vals, int n, int coins) {
		if (!n) {
			ans = max(ans, coins);
			return ;
		}	
		for (int i = 1; i < vals.size() - 1; ++i) {
			if (-1 == vals[i]) continue;	
			// 左相邻气球
			int left = i-1;
			while (vals[left] == -1) --left;
			// 右相邻气球
			int right = i+1;
			while (vals[right] == -1) ++right;
			// backtrack
			int tmp = vals[i];	
			vals[i] = -1;			// 戳爆的设置为-1		
			BackTracking(vals, n-1, coins + vals[left] * tmp * vals[right]);		
			vals[i] = tmp;
		}		
	}

    int maxCoins(vector<int>& nums) {
	// 增加哨兵避免处理边界问题	
	int n = nums.size(); 
	vector<int> vals(n+2, 1);		
	for (int i = 0; i < n; ++i) vals[i+1] = nums[i]; 
	BackTracking(vals, n, 0);
	return ans;
    }	
};

// solution 2: 记忆化递归
class Solution {
public:
	int Recur(vector<int> &vals, vector<vector<int>> &dp, int i, int j) {
		if (i >= j-1) return 0; 			
		if (-1 != dp[i][j]) return dp[i][j];	
		
		for (int k = i + 1; k < j; ++k) {
			dp[i][j] = max(dp[i][j], vals[i] * vals[k] * vals[j] + Recur(vals, dp, i, k) + Recur(vals, dp, k, j));		
		}	
		return dp[i][j];
	}

    int maxCoins(vector<int>& nums) {
	// 增加哨兵避免处理边界问题	
	vector<int> vals(nums.size()+2, 1);		
	for (int i = 0; i < nums.size(); ++i) vals[i+1] = nums[i]; 
	int len = vals.size(); 
	vector<vector<int>> dp(len, vector<int>(len, -1));	
	return Recur(vals, dp, 0, len-1);
    }	
};
*/


// solution 3: dp
class Solution {
public:
    int maxCoins(vector<int>& nums) {
	// 增加哨兵避免处理边界问题	
	vector<int> vals(nums.size()+2, 1);		
	for (int i = 0; i < nums.size(); ++i) vals[i+1] = nums[i]; 
	int len = vals.size(); 
	vector<vector<int>> dp(len, vector<int>(len, 0));	
	for (int i = len-3; i >= 0; --i) {
		for (int j = i + 2; j < len; ++j) {
			for (int k = i + 1; k < j; ++k) {
				dp[i][j] = max(dp[i][j], vals[i] * vals[k] * vals[j] + dp[i][k] + dp[k][j]); 
			}
		}
	}	
	return dp[0][len-1];
    }	
};




int main(int argc, char *argv[]) {

	return 0;
}
