/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Thu 10 Dec 2020 07:38:52 PM CST
 @ File Name	: 0332_coinChange.cpp
 @ Description	: 322. 零钱兑换 
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
// solution 1: 回溯搜索所有可能的组合， 时间复杂度为O(s^n), 其中s是coins.size()
class Solution {
public:
	int ans = INT_MAX;
	void backTracking(vector<int>& coins, int amount, int step) {
		cout << ans << ","  << step << "," << amount << endl;
		if (amount < 0) return ;
		if (amount == 0) {
			ans = std::min(ans, step);		
			return ;
		}
		// 提前剪枝	
		if(step >= ans) return ;	
		for (const auto &e : coins)  backTracking(coins, amount-e, step + 1); 
	}		

    int coinChange(vector<int>& coins, int amount) {
	if (amount == 0) return 0;
	// 大到小排个序
	std::sort(coins.begin(), coins.end(), [](const int& a, const int &b)->bool{return a >= b;});	
	std::for_each(coins.begin(), coins.end(), [](const int &a){cout << a << endl;});
	backTracking(coins, amount, 0);	
	return ans != INT_MAX ? ans : -1;
    }
};

// solution 2: 动态规划， 从后往前;
//		递推关系式 :
//			f(N) = min(f(N - x), ...) + 1, 其中f(N-x) 为当前amount - 所有coins后的取值
//			f(0) = 0
//		观察递归状态树， 发现很多f(N) 会被重复计算， 所以使用res数组来缓存子问题结果
//
//		有amount个数值需要被计算， 每个数值计算时需要遍历coins数组， 所以时间复杂度为 O(amount * coins.size())

class Solution {
public:
	int recur(vector<int>& coins, int amount, vector<int>& res) {

		if (amount < 0) return INT_MAX;		
		if (res[amount] != -2) return res[amount];	
		int ans = INT_MAX;
		for (auto &e : coins) {
			ans = std::min(ans, recur(coins, amount - e, res));
		}
		ans = ans == INT_MAX ? ans : ans + 1;	
		res[amount] = ans; 
		return ans;
	}
	
    int coinChange(vector<int>& coins, int amount) {
	if (amount == 0) return 0;
	vector<int> res(amount+1, -2);		// -2 代表还没有计算
	res[0] = 0;
	recur(coins, amount, res);
	return res[amount] == INT_MAX ? -1 : res[amount];
    }
};
*/

/*
// solution 3: 动态规划， 从前往后;
//		从前往后遍历每一个amount， 如果当前amount 可达， 那么就遍历coins 更新amount + c 的步数
//		有amount个数值需要被计算， 每个数值计算时需要遍历coins数组， 所以时间复杂度为 O(amount * coins.size())

class Solution {
public:	
    int coinChange(vector<int>& coins, int amount) {
	if (amount == 0) return 0;
	vector<int> res(amount+1, INT_MAX);		// INT_MAX 代表还没有计算
	res[0] = 0;
	for (int i = 0; i < amount; ++i) {
		if (res[i] == INT_MAX) continue;	// i 本来就不可达，所以没必要计算i 之后的所有coins情况
		for (auto &e : coins) {
			// if (i + e > amount) continue; // i + e 有溢出风险	
			if (i > amount - e) continue;		
			res[i+e] = std::min(res[i+e], res[i] + 1);
		}	
	}
	return res[amount] == INT_MAX ? -1 : res[amount];
    }
};
*/

// solution 4: 贪心 + dfs 【最佳】
//		每次选取尽可能多数量的最大面值硬币， 求出次最优解（进行不断剪枝）
class Solution {
public:	
	int ans = INT_MAX;
	void dfs(vector<int>& coins, int idx, int amount, int step) {
		if (0 == amount) {
			ans = min(ans, step);
			return ;
		}
		if (idx >= coins.size()) return ;
		for (int k = amount / coins[idx]; k >= 0 && step + k < ans; --k) {	
			dfs(coins, idx + 1, amount - k * coins[idx], step + k);
		}
	}
    int coinChange(vector<int>& coins, int amount) {
	if (amount == 0) return 0;
	sort(coins.rbegin(), coins.rend());		// 倒序排序一下
	dfs(coins, 0, amount, 0);
	return ans == INT_MAX ? -1 : ans;
    }
};




int main(int argc, char *argv[]) {

	Solution obj;
	vector<int> coins = {1,2,5};
	cout << obj.coinChange(coins, 100) << endl;;
	return 0;
}
