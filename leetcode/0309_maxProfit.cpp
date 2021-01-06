/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Wed 06 Jan 2021 08:18:04 PM CST
 @ File Name	: 0309_maxProfit.cpp
 @ Description	: 309. 最佳买卖股票时机含冷冻期 
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
	对比leetcode 122 增加了交易冷冻期
	
	solution 1: 回溯搜索

	solution 2: dp; 相对于leetcode 122， 有如下状态转移方程:
			dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i])
			dp[i][1] = max(dp[i-1][1], dp[i-2][0] - prices[i])
		
			使用三个滚动变量进行空间优化	
   */


/*
// solution 1: 回溯搜索
class Solution {
public:
	int ans = 0;
	// @status: 当前状态， 0 持有/ 1 冷冻不持有/ 2 非冷冻不持有
	void BackTracking(vector<int>& prices, int idx, int status, int profit) {
		if (idx == prices.size()) {
			ans = max(ans, profit);	
			return ;		
		}
		
		// 今天不操作
		if (1 == status) {
			BackTracking(prices, idx+1, 2, profit);
		} else {
			BackTracking(prices, idx+1, status, profit);
		}	

		// 今天操作
		if (0 == status) {
			BackTracking(prices, idx+1, 1, profit + prices[idx]);
		} else if (2 == status) {
			BackTracking(prices, idx+1, 0, profit - prices[idx]);
		}
	}	

    int maxProfit(vector<int>& prices) {
	BackTracking(prices, 0, 2, 0);
	return ans;	
    }
};
*/

// solution 2: dp
//                      dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i])
//                      dp[i][1] = max(dp[i-1][1], dp[i-2][0] - prices[i])
class Solution {
public:

    int maxProfit(vector<int>& prices) {
        int dp0 = 0, dp1 = INT_MIN, pre_dp0 = 0;
        for (auto &e : prices) {
                int tmp = dp0;
                dp0 = max(dp0, dp1 + e);
                dp1 = max(dp1, pre_dp0 - e);
                pre_dp0 = tmp;
        }
        return dp0;
    }
};



int main(int argc, char *argv[]) {

	return 0;

}
