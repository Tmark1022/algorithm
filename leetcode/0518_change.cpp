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
		

		dp (inspire fron solutoin 1, 回溯， 观察到状态转移)， 设 f(i, v) 为使用下边0 ~ i 的coins, 组成面值为v的组合数
    		状态转移方程：
			f(i, v) = f(i-1, v) + f(i-1, v-coins[i]) + f(i-1, v-coins[i]*2) + ... ;     v - coins[i] * x >= 0
    		
    		base case:
    		 1) 当 v == 0时， f(i, v) = 1;
    		 2) 当 i < 0 时， 除了当v == 0 时 f(i, v) = 1， 其他情况 f(i, v) 均为0
    		 3）v < 0 时， 均是非法状态， f(i, v) 均是0


		基于上边推导出来的递推关系式， 有 f(i, v-coins[i]) = f(i-1, v-coins[i]) + f(i-1, v-coins[i]*2) + ... ; 
		两相结合一下， 上述关系式可以优化为 f(i, v) = f(i-1, v) + f(i, v-coins[i])

		这是一个二维dp, 又因为f(i, v) 只与 i-1 有关， 所以可以采取从左到右的方式遍历， 且使用一维滚动数组来优化空间， 优化后的状态转移方程为:
			f(v) = f(v) + f(v-coins[i]);
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

/*
// solution 2: dp, f(i, v) = f(i-1, v) + f(i-1, v-coins[i]) + f(i-1, v-coins[i]*2) + ... ;     v - coins[i] * x >= 0
class Solution {
public:
    int change(int amount, vector<int>& coins) {
        if (amount == 0) return 1;
	// 旧的测试用例可以过， 新增的测试用例不行了， 得 unsinged long long 才可以
        // vector<int> dp(amount + 1, 0);
        vector<unsigned long long> dp(amount + 1, 0);
        dp[0] = 1;

        for (auto coin : coins) {
            for (int j = amount; j >= 1; --j) {		// 右到左进行遍历
                for (int k = j / coin; k > 0; --k) {
                    dp[j] += dp[j - k * coin];
                }
            }
        }
        return dp[amount];
    }
};
*/

// solution 2: dp, 优化后的递推关系式, f(v) = f(v) + f(v-coins[i]);
class Solution {
public:
    int change(int amount, vector<int>& coins) {
	// 旧的测试用例可以过， 新增的测试用例不行了， 得 unsinged long long 才可以
        // vector<int> dp(amount + 1, 0);
        vector<unsigned long long> dp(amount + 1, 0);
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
