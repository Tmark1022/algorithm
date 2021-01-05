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
// solution 1: 回溯搜索， 时间复杂度为O(s^n), 其中s是coins.size(), 进行排列
//		这种写法其实是进行排列枚举， 而不组合枚举, 而solution 4 进行的就是组合
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

// solution 2: 动态规划， 从后往前【记忆化递归】;
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
//		有amount个数值需要被计算， 每个数值计算时需要遍历coins数组， 所以时间复杂度为 O(amount * coins.size())
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        if (!amount) return 0;
        vector<int> dist(amount + 1, INT_MAX);
        dist[0] = 0;
        for(int i = 1; i <= amount; ++i)  {
            for (auto &e : coins) {
                int prev = i - e;
                if (prev < 0 || dist[prev] == INT_MAX) continue;
                dist[i] = min(dist[i], dist[prev] + 1);
            } 
        }
        return dist[amount] == INT_MAX ? -1 : dist[amount]; 
    }
};

// 从前往后另一种写法， 但这不是标准的动态规划写法
//class Solution {
//public:	
//    int coinChange(vector<int>& coins, int amount) {
//	if (amount == 0) return 0;
//	vector<int> res(amount+1, INT_MAX);		// INT_MAX 代表还没有计算
//	res[0] = 0;
//	for (int i = 0; i < amount; ++i) {
//		if (res[i] == INT_MAX) continue;	// i 本来就不可达，所以没必要计算i 之后的所有coins情况
//		for (auto &e : coins) {
//			// if (i + e > amount) continue; // i + e 有溢出风险	
//			if (i > amount - e) continue;		
//			res[i+e] = std::min(res[i+e], res[i] + 1);
//		}	
//	}
//	return res[amount] == INT_MAX ? -1 : res[amount];
//    }
//};
//
//
// solution 4: 贪心 + dfs ; solution1 是排列， 这里是组合, 每个面值的硬币应该选择多少个
//		每次选取尽可能多数量的最大面值硬币， 求出次最优解（进行不断剪枝）
		时间复杂度为 O ((amount / coins[0]) * (amout / coins[1]) * (amount / coins[2]) * ....)
		即 O(amount ^ s), s 为 coins.size()

		不过因为经过贪心算法， 尽快地找到了一个step来进行剪枝， 所以效率却是很快
//class Solution {
//public:	
//	int ans = INT_MAX;
//	void dfs(vector<int>& coins, int idx, int amount, int step) {
//		if (0 == amount) {
//			ans = min(ans, step);
//			return ;
//		}
//		if (idx >= coins.size()) return ;
//		for (int k = amount / coins[idx]; k >= 0 && step + k < ans; --k) {	
//			dfs(coins, idx + 1, amount - k * coins[idx], step + k);
//		}
//	}
//    int coinChange(vector<int>& coins, int amount) {
//	if (amount == 0) return 0;
//	sort(coins.rbegin(), coins.rend());		// 倒序排序一下
//	dfs(coins, 0, amount, 0);
//	return ans == INT_MAX ? -1 : ans;
//    }
//};

// solution 4 的容易理解版本
class Solution {
public:
    int ans = INT_MAX;
    void dfs(vector<int>& coins, int idx, int amount, int step) {
        if (amount == 0) {
            ans = min(ans, step); 
            return ;
        }
        // 进行一些剪枝 
        if (idx >= coins.size()) return ; 
        int k = amount / coins[idx];
        if (step + k >= ans) return;		// 当前idx选择最大个数时都小于当前ans， 当前状态的后续也无须继续进行递归了
        // 枚举所有可能
        while (k >= 0) {
            dfs(coins, idx + 1, amount - k * coins[idx], step + k);     
            --k;
        }
    }

    int coinChange(vector<int>& coins, int amount) {
        if (0 == amount) return 0;
        sort(coins.rbegin(), coins.rend());
        dfs(coins, 0, amount, 0); 
        return ans == INT_MAX ? -1 : ans; 
    }
};


// solution 5: BFS; 仔细观察， 其实这个问题可以转换为图求解最短无权路径问题。
//              0~amount 的每一个数值都是一个顶点; 对于每一个顶点， 存在 <x, x+coins[i]> 的边
//
//              时间复杂度为 O(n+e), n顶点数为amount，e边数为amount * coins.size()
//
//              这题有溢出问题， 所以可以改成 amount为源点， 0为终点， 来避免数值相加溢出问题
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        if (amount == 0) return 0;
        sort(coins.rbegin(), coins.rend());             // 倒序排序一下

        deque<int> que;
        que.push_back(amount);
        vector<bool> visit(amount + 1, false);
        visit[amount] = true;

        int step = 0;
        while (que.size()) {
                ++step;
                // 每次遍历一整层
                for (int cnt = que.size(); cnt ; --cnt) {
                        int cur = que.front();
                        que.pop_front();
                        // 遍历邻接顶点
                        for (auto &e : coins) {
                                int next = cur - e;
                                if (next == 0) return step;
                                if (next > 0 && !visit[next]) {
                                        que.push_back(next);
                                        visit[next] = true;
                                }
                        }
                }
        }
        return -1;
    }
};

// solution 6: solution 5的优化， 因为知道起点和终点， 所以可以进行双向BFS 
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        if (amount == 0) return 0;
        // sort(coins.rbegin(), coins.rend());             // 排序其实用处也不大
	vector<bool> visit(amount+1, false);	
	visit[0] = true, visit[amount] = true;
	unordered_set<int> set1 = {amount}, set2 = {0}, *head = &set1, *tail = &set2; 

        int step = 0;
	bool direction = false;
        while (head->size() && tail->size()) {
                ++step;
		if (head->size() > tail->size()) {
			swap(head, tail);	
			direction = !direction;
		}
		unordered_set<int> new_set;
		for (auto &cur : *head) {
                        for (auto &e : coins) {
				int next = direction ? cur+e : cur-e;	
				if (tail->count(next)) return step;	
				if (next >= 0 && next <= amount && !visit[next]) {
					visit[next] = true;
					new_set.insert(next);
				}
			}
		}
		*head = new_set;
        }
        return -1;
    }
};
*/









// solution 7: 完全背包问题 TODO

int main(int argc, char *argv[]) {

	Solution obj;
	vector<int> coins = {1,2,5};
	cout << obj.coinChange(coins, 100) << endl;;
	return 0;
}
