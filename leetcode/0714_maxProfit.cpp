/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Thu 07 Jan 2021 11:21:33 AM CST
 @ File Name	: 0714_maxProfit.cpp
 @ Description	: 714. 买卖股票的最佳时机含手续费 
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
	对比leetcode 122 增加了交易手续费， 手续费可以附加在购买股票时， 也可以附加在出售股票时， 这里统一将手续费附加在购买购票时进行分析
	
	solution 1: 回溯搜索

	solution 2: dp; 相对于leetcode 122， 有如下状态转移方程:
			dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i])
			dp[i][1] = max(dp[i-1][1], dp[i-1][0] - prices[i] - fee)
		
			使用两个滚动变量进行空间优化	
	
	solution 3: 贪心
   */


/*
// solution 1: 回溯搜索
class Solution {
public:
	int ans = 0;
	// @status: 当前状态， 0 不持有/ 1 持有
	void BackTracking(vector<int>& prices, int idx, int status, int profit, int fee) {
		if (idx == prices.size()) {
			ans = max(ans, profit);	
			return ;		
		}
		
		// 今天不操作
		BackTracking(prices, idx+1, status, profit, fee);

		// 今天操作
		if (status) BackTracking(prices, idx+1, 0, profit + prices[idx], fee);
		else BackTracking(prices, idx+1, 1, profit - prices[idx] - fee, fee);
	}	

    int maxProfit(vector<int>& prices, int fee) {
	BackTracking(prices, 0, 0, 0, fee);
	return ans;	
    }
};

// solution 2: dp
//			dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i])
//			dp[i][1] = max(dp[i-1][1], dp[i-1][0] - prices[i] - fee)
class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        int dp0 = 0, dp1 = INT_MIN;
        for (auto &e : prices) {
		int dp0_tmp = dp0;
                dp0 = max(dp0, dp1 + e);
                dp1 = max(dp1, dp0_tmp - e - fee);
        }
        return dp0;
    }
};

// solution 2: dp
//			dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i])
//			dp[i][1] = max(dp[i-1][1], dp[i-1][0] - prices[i] - fee)
class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        int dp0 = 0, dp1 = INT_MIN;
        for (auto &e : prices) {
		int dp0_tmp = dp0;
                dp0 = max(dp0, dp1 + e);
                dp1 = max(dp1, dp0_tmp - e - fee);
        }
        return dp0;
    }
};
*/

// solution 3: 贪心, 核心是维护一个买入股票价格(含fee)变量, 时刻更新低买入价格
//		注意如下几种情况:
//			1) 考虑连续涨的情况
//			2) 涨没有超过上次买入价格
//			3) 跌没有跌出上次买入价格
class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
	int buy = INT_MAX, ans = 0;	
        for (auto &e : prices) {
		if (e + fee < buy) {
			// 当前购入股票价格更低， 更新购入股票价格
			buy = e + fee;
		} else if (e > buy) {
			ans += e - buy;
			buy = e;		// 更新当前购入价格为当前股票价格（不重复计算fee，考虑连续涨的情况） 
		}
		// 剩余的 buy - fee <= e <= buy 这个区间价格不用理会
        }
        return ans;
    }
};






int main(int argc, char *argv[]) {

	return 0;
}
