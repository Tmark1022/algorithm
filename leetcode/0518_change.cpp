/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Tue 05 Jan 2021 11:38:12 AM CST
 @ File Name	: 0518_change.cpp
 @ Description	: 518. 零钱兑换 II 
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

   solution 1: 回溯搜索， 组合枚举每一个硬币的需求个数
   
   solution 2: dp, 需要注意的是， 要求组合数， 而不是排列数 
		状态转移方程 f(i) = f(i - coins[x1]) + f(i - coins[x2]) + ..  是排列数，  
		
		设 f(i, k) 表示金额i使用前k个硬币时， 最大有多少中组合数;
		存在如下状态转移方程:
			f(i, k) = f(i, k-1) + f(i-coins[k], k); 

		这是一个二维dp, 又因为f(i, k) 只与 k-1 有关， 所以可以使用一维滚动数组来优化空间， 优化后的状态转移方程为:
			f(i) = f(i) + f(i-coins[k]);

   */

/*
// solution 1: 回溯搜索 【超时】
class Solution {
public:
	int ans = 0;
	void BackTracking(vector<int>& coins, int idx, int amount) {
		if (idx == coins.size() - 1) {
			if (amount % coins[idx] == 0) ++ans;
			return ;
		}
		for (int k = amount / coins[idx]; k >= 0; --k) {
			BackTracking(coins, idx+1, amount - coins[idx] * k);
		}
	}	

    int change(int amount, vector<int>& coins) {
	if (!amount || !coins.size()) return 0;
	BackTracking(coins, 0, amount);
	return ans;
    }
};
*/

// solution 2: dp, time complexity O(amout * N), space complexity O(amount);
class Solution {
public:
    int change(int amount, vector<int>& coins) {
	vector<int> dp(amount + 1, 0);
	dp[0] = 1;
	for (auto &c : coins) {
		for (int i = c; i <= amount; ++i) {
			dp[i] += dp[i-c];
		}	
	}
	return dp[amount];
    }
};



int main(int argc, char *argv[]) {

	return 0;
}
