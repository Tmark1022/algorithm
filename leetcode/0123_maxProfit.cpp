/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Thu 07 Jan 2021 07:48:12 PM CST
 @ File Name	: 0123_maxProfit.cpp
 @ Description	: 123. 买卖股票的最佳时机 III
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
	solution 1: 回溯搜索
	
	solution 2: dp; 列举状态 设 i 代表天数【在这里是prices数组下标】， k 代表 交易次数（购入股票时递增）, 0/1 代表 是否持有股票 
			存在如下状态转移方程:	
				dp[i][k][0] = max(dp[i-1][k][0], dp[i-1][k][1] + prices[i]);
				dp[i][k][1] = max(dp[i-1][k][1], dp[i-1][k-1][0] - prices[i]);

			base case:
				当 k==0, 对于任意的i:	dp[i][0][0] = 0, dp[i][0][1] = -infinite



			另外：	
			因为K最大取值2, k = 0 的结果已知并且不是答案， 所以K只能取1 和 2, 我们完全可以通过写死枚举k = 1 和  k= 2 来省略一维dp
			如 使用i 代表天数， 0 代表 k = 1 且未持有股票; 1 代表 k = 1 且 持有股票; 2 代表 k = 2 且 未持有股票, 3 代表 k = 2 且 持有股票

			所以状态转移方程可以简化为如下:
				dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i]);
				dp[i][1] = max(dp[i-1][1], -prices[i]);
				dp[i][2] = max(dp[i-1][2], dp[i-1][3] + prices[i]);
				dp[i][3] = max(dp[i-1][3], dp[i-1][0] - prices[i]);
   */

/*
// solution 1: 回溯搜索 【超时】
class Solution {
public:
	int ans = 0; 
	// @k : 当前交易次数
	// @status : 股票持有状态
	void BackTracking(vector<int>& prices, int idx, int k, int status, int profit) {
		if (idx == prices.size()) {
			ans = max(ans, profit);
			return ;
		}
		
		// non operate
		BackTracking(prices, idx + 1, k, status, profit);	

		// operate
		if (status) {
			BackTracking(prices, idx+1, k, 0, profit +prices[idx]);
		} else {
			// 存在购买限制
			if (k < 2) BackTracking(prices, idx+1, k+1, 1, profit - prices[idx]);
		}
	}

    int maxProfit(vector<int>& prices) {
	BackTracking(prices, 0, 0, 0, 0);
	return ans;	
    }
};

// solution 2: dp1 : 
//				dp[i][k][0] = max(dp[i-1][k][0], dp[i-1][k][1] + prices[i]);
//				dp[i][k][1] = max(dp[i-1][k][1], dp[i-1][k-1][0] - prices[i]);
//
//			base case:
//				当 k==0, 对于任意的i:	dp[i][0][0] = 0, dp[i][0][1] = -infinite

class Solution {
public:
    int maxProfit(vector<int>& prices) {
	if (!prices.size()) return 0;		
	vector<vector<int>> dp(3, vector<int>(2, 0));	

	// base case
	for (int k = 1; k <= 2; ++k) {
		dp[k][0] = 0;
		dp[k][1] = -prices[0];
	}

	for (int i = 1; i < prices.size(); ++i) {
		for (int k = 2; k >= 1; --k) {			// 这里k倒序是因为dp[i-1][k-1][0] 的覆盖问题
			dp[k][0] = max(dp[k][0], dp[k][1] + prices[i]);
			dp[k][1] = max(dp[k][1], dp[k-1][0] - prices[i]);	
		}
	} 
	return dp[2][0];
    }
};
*/


// solution 3: dp2 : 状态转移方程可以简化为如下:
//				dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i]);
//				dp[i][1] = max(dp[i-1][1], -prices[i]);
//				dp[i][2] = max(dp[i-1][2], dp[i-1][3] + prices[i]);
//				dp[i][3] = max(dp[i-1][3], dp[i-1][0] - prices[i]);

class Solution {
public:
    int maxProfit(vector<int>& prices) {
	if (!prices.size()) return 0;		
	int dp0 = 0, dp1 = -prices[0], dp2 = 0, dp3 = -prices[0]; 
	for (int i = 1; i < prices.size(); ++i) {
		int tmp = dp0;	
		dp0 = max(dp0, dp1 + prices[i]);
		dp1 = max(dp1, -prices[i]);
		dp2 = max(dp2, dp3 + prices[i]);
		dp3 = max(dp3, tmp - prices[i]);
	}
	return dp2;
    }
};




int main(int argc, char *argv[]) {

	return 0;
}
