/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Wed 06 Jan 2021 11:57:27 AM CST
 @ File Name	: 0121_maxProfit.cpp
 @ Description	: 121. 买卖股票的最佳时机 
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
	solution 1: brute force, 枚举购入价格 和 出售价格， 取最大值  

	solution 2: 单调栈思路，减去范围内的最小购入价格 

	solution 3: dp; 列举状态 设 i 代表天数， k 代表 交易次数（购入股票时递增）, 0/1 代表 是否持有股票 
			存在如下状态转移方程:	
				dp[i][k][0] = max(dp[i-1][k][0], dp[i-1][k][1] + prices[i]);
				dp[i][k][1] = max(dp[i-1][k][1], dp[i-1][k-1][0] - prices[i]);

			基础状态:
				对于i是-1:	dp[-1][k][0] = 0, dp[-1][k][1] = -infinite
				对于k是0::	dp[i][0][0] = 0, dp[i][0][1] = -infinite
		
		
			因为本题题意中k的最多只能取1， k为0时状态已知并且绝对不是题目答案，k为1时才可能是题意答案， 我们可以得出K=1时的状态转移方程
				dp[i][1][0] = max(dp[i-1][1][0], dp[i-1][1][1] + prices[i])
				dp[i][1][1] = max(dp[i-1][1][1], dp[i-1][0][0] - prices[i]); 可以简化为 dp[i][1][1] = max(dp[i-1][1][1], -prices[i]); 

			因为k只能取1， 可以省略该维度, 得出如下简化版状态转移方程
				dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i])
				dp[i][1] = max(dp[i-1][1], -prices[i]);
   */


/*
// solution 1: brute force
class Solution {
public:
    int maxProfit(vector<int>& prices) {
	int len = prices.size();
	if (!len) return 0;
	int ans = 0;		
	for (int i = 0; i < len - 1; ++i) {
		for (int j = i+1; j < len; ++j) {
			ans = max(ans, prices[j] - prices[i]);
		}
	}
	return ans;
    }
};

// solution 2: 单调栈思路， 一遍循环 
class Solution {
public:
    int maxProfit(vector<int>& prices) {
	int ans = 0, min_price = INT_MAX;		
	for (int i = 0; i < len; ++i) {
		if (prices[i] < min_price) min_price = prices[i];
		else ans = max(ans, prices[i] - min_price);
	}
	return ans;
    }
};
*/

// solution 3: dp;	dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i]), 
//			dp[i][1] = max(dp[i-1][1], -prices[i]);
class Solution {
public:
    int maxProfit(vector<int>& prices) {
	int dp0 = 0, dp1 = INT_MIN;
	for (auto &e : prices) {
		dp0 = max(dp0, dp1 + e);
		dp1 = max(dp1, -e);
	}
	return dp0;
    }
};



int main(int argc, char *argv[]) {

	return 0;
}
