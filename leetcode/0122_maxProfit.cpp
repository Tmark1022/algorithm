/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Wed 23 Dec 2020 01:59:07 PM CST
 @ File Name	: 0122_maxProfit.cpp
 @ Description	: 
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
	股票每天有 不操作 和 操作（买入/卖出） 两种选择
	solution 1: dfs 回溯搜索
	solution 2: 动态规划
       	solution 2: 动态规划, 每天持有股票状态有两种（持有/不持有），使用二维数组dp[n][2] 存储;
       			dp[i][0] 代表第i天不持有股票时的最大收益，dp[i][1] 代表第i天持有股票时的最大收益
       			
       			dp[i][0] 的状态转移方程如下:
       				dp[i][0] = max{dp[i-1][0], dp[i-1][1] + prices[i]};
       				dp[0][0] = 0;
       		
       			dp[i][1] 的状态转移方程如下:
       				dp[i][1] = max{dp[i-1][1], dp[i-1][0] - prices[i]};
       				dp[0][1] = 0 - prices[i];

       	solution 3: 贪心greddy, 因为没有限制交易次数， 所以只要明天是涨的， 就购买， 明天马上卖出;
			每天作为一个步骤， 每个步骤的最优解为 diff > 0 ? diff : 0; 同样可以写成max(0, prices[i] - prices[i-1]);
			每个步骤的最优解组合就是问题的最终解
*/

/*
// solution 1: dfs 回溯搜索
class Solution {
public:
	// @day: 当前第几天 从0开始
	// @status : 当前状态 0没持有/1持有股票
	// @profit : 当前总盈利
	int max_profit = 0;
    void Dfs(vector<int>& prices, int day, int status, int profit) {
	if (day == prices.size()) {
		max_profit = max(max_profit, profit);
		return ;
	}
	
	// 不操作
	Dfs(prices, day+1, status, profit);

	// 操作
	if (status) {
		// 卖出	
		Dfs(prices, day + 1, 0, profit + prices[day]);	
	} else {
		Dfs(prices, day + 1, 1, profit - prices[day]);	
	}		
    }

    int maxProfit(vector<int>& prices) {
	Dfs(prices, 0, 0, 0);	 
	return max_profit;
    }
};

// solution 2: 动态规划
class Solution {
public:
    int maxProfit(vector<int>& prices) {
	vector<vector<int>> dp(prices.size(), vector<int>(2));
	dp[0][0] = 0, dp[0][1] = 0 - prices[0];	
	for (int i = 1; i < prices.size(); ++i) {
		dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i]);
		dp[i][1] = max(dp[i-1][1], dp[i-1][0] - prices[i]);
	}
	return dp[prices.size() - 1][0];
    }
};

// solution 2: 动态规划, 因为当前步骤状态只与上一阶段优化， 所以可以使用滚动变量来优化dp存储空间
class Solution {
public:
    int maxProfit(vector<int>& prices) {
	int dp0 = 0, dp1 = -prices[0];
	for (int i = 1; i < prices.size(); ++i) {
		int new_dp0 =  max(dp0, dp1 + prices[i]);
		int new_dp1 =  max(dp1, dp0 - prices[i]);
		dp0 = new_dp0;
		dp1 = new_dp1;
	}
	return dp0;
    }
};
*/

// solution 3: greddy 
class Solution {
public:
    int maxProfit(vector<int>& prices) {
	int ans = 0;
	for (int i = 1; i < prices.size(); ++i) {
		ans += max(0, prices[i] - prices[i-1]);
	}
	return ans;
    }
};


int main(int argc, char *argv[]) {

	return 0;
}
