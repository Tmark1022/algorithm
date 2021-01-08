/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Fri 08 Jan 2021 01:58:57 PM CST
 @ File Name	: 0188_maxProfit.cpp
 @ Description	: 188. 买卖股票的最佳时机 IV 
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
   */

/*
// solution 1: 回溯搜索 【超时】
class Solution {
public:
	int ans = 0; 
	// @k : 当前交易次数
	// @status : 股票持有状态
	void BackTracking(vector<int>& prices, int idx, int k, int status, int profit, int klimit) {
		if (idx == prices.size()) {
			ans = max(ans, profit);
			return ;
		}
	
		// non operate
		BackTracking(prices, idx + 1, k, status, profit, klimit);	

		// operate
		if (status) {
			BackTracking(prices, idx+1, k, 0, profit +prices[idx], klimit);
		} else {
			// 存在购买限制
			if (k < klimit) BackTracking(prices, idx+1, k+1, 1, profit - prices[idx], klimit);
		}
	}

    int maxProfit(int k, vector<int>& prices) {
	BackTracking(prices, 0, 0, 0, 0, k);
	return ans;	
    }
};
*/


// solution 2: dp1 : 
//				dp[i][j][0] = max(dp[i-1][j][0], dp[i-1][j][1] + prices[i]);
//				dp[i][j][1] = max(dp[i-1][j][1], dp[i-1][j-1][0] - prices[i]);
//
//			base case:
//				当 j==0, 对于任意的i:	dp[i][0][0] = 0, dp[i][0][1] = -infinite
//
//				
//			按最频繁两天一个交易周期计算, 最多能进行ceil(prices.size() / 2)【其实floor(prices.size() / 2)即可，因为最后一天交易持有股票的不可能是最终答案】	
//			所以我们可以约束 k = min (floor(prices.size() / 2), k) 
//
//			当k >= floor(prices.size() / 2)时， 我可其实可以当做能够进行无限次交易， 进而转化为leetcode 122 股票最佳买卖时机②即可
class Solution {
public:
	int maxProfitWithInfiniteK(vector<int>& prices) {
		int ans = 0;				
		for (int i = 1; i < prices.size(); ++ i) {
			if (prices[i] > prices[i-1]) ans += prices[i] - prices[i-1]; 
		}
		return ans;
	}

    int maxProfit(int k, vector<int>& prices) {
	if (k >= prices.size() / 2) return maxProfitWithInfiniteK(prices);
	vector<vector<int>> dp(k+1, vector<int>(2, 0));	
	// base case
	for (int j = 0; j <= k; ++j) {
		dp[j][0] = 0;
		dp[j][1] = INT_MIN;
	}

	for (auto &e : prices) {
		for (int j = k; j >= 1; --j) {			// 这里j倒序是因为dp[i-1][j-1][0] 的覆盖问题
			dp[j][0] = max(dp[j][0], dp[j][1] + e);
			dp[j][1] = max(dp[j][1], dp[j-1][0] - e);	
		}
	} 
	return dp[k][0];
    }
};

int main(int argc, char *argv[]) {

	return 0;
}
