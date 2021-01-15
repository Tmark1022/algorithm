/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Fri 15 Jan 2021 10:20:14 AM CST
 @ File Name	: 0403_canCross.cpp
 @ Description	: 403. 青蛙过河 
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
	
	NOTE:
		这道题目有一个关键的信息: 就是下标为i的石头， 最大的下一跳距离为i+1; 

	solution 1: 朴素回溯搜索; 时间O(3^N), 空间O(1) or O(N)考虑递归深度

	solution 2: 优雅回溯搜索(使用二分查找或unordered_map来判断下一跳是否存在); 时间O(3^N), 空间O(1) or O(N)考虑递归深度

	solution 3: 优雅回溯搜索 + 记忆化递归进行剪枝; 使用N*N的二维数组visit 来保存搜索记录，如visit[idx][k] 代表上一跳距离为k的第idx块石头是否可达。
			使用了记忆化递归后的递归总次数为N*N（即	N个石头 * 最大跳距离为N）
			当使用unordered_map来判断下一跳是否存在时， 总的时间复杂度为O(N*N), 空间复杂度为O(N*N)
	
	solution 4: dp; 设dp[i][k] 表示上一跳距离为k的下标为i的石头是否可达;
			存在如下状态转移方程:
				dp[i][k] = dp[j][k-1] || dp[j][k] || dp[j][k+1]		// 其中j取值范围为 0 ~ i-1

				根据NOTE 的提示， k的有效范围为 [1, i], 可以利用这个来进行剪枝

			时间O(N*N), 空间O(N*N)
	
	solution 5: dp 思路逆转【不清楚这是否还算是dp】; solution 4 是根据i之前的计算结果判断当前i是否可达, 这里思路转换一下， 根据i可达， 判断i后面的石头的可达情况;
				使用到辅助数据 unordered_map<int, set<int>> map 记录可达情况; 集合set表示能够到达下标i的石头时，前一跳距离为多少	
				容易可得， map[i].empty() 表示下标i的石头不可达

			时间O(N*N), 空间O(N*N)
   */

/*
// solution 1:
class Solution {
public:
        vector<int> idx_diff = {-1, 0, 1};
        bool BackTracking(vector<int>& stones, int idx, int k) {
                if (idx == stones.size() - 1) return true;
                for (int next = idx + 1; next < stones.size() && stones[idx] + k + 1 >= stones[next]; ++next) {  // stones[idx] + k + 1 >= stones[next] 提前剪枝
                        for (auto &diff : idx_diff) {
                                if (stones[idx] + k + diff == stones[next]) {
                                        if (BackTracking(stones, next, k + diff)) return true;
                                }
                        }
                }
                return false;
        }

    bool canCross(vector<int>& stones) {
        return BackTracking(stones, 0, 0);
    }
}

// solution 2: 使用二分加快下一跳目标查找
class Solution {
public:
	vector<int> idx_diff = {-1, 0, 1};
	bool BackTracking(vector<int>& stones, int idx, int k) {
		if (idx == stones.size() - 1) return true;
		for (auto &diff : idx_diff) {
			int next_target = stones[idx] + k + diff;
			auto first = std::lower_bound(stones.begin() + idx + 1, stones.end(), next_target);
			if (first != stones.end() && *first == next_target) {
				if (BackTracking(stones, first - stones.begin(), k+diff)) return true;
			}	
		}
		return false;
	}

    bool canCross(vector<int>& stones) {
	return BackTracking(stones, 0, 0);
    }
};


// solution 2: 使用unordered_map加快下一跳目标查找
class Solution {
public:
	vector<int> idx_diff = {-1, 0, 1};
	bool BackTracking(vector<int>& stones, int idx, int k, unordered_map<int, int>& map) {
		if (idx == stones.size() - 1) return true;
		for (auto &diff : idx_diff) {
			int next_target = stones[idx] + k + diff;
			if (next_target > stones[idx] && map.count(next_target)) {
				if (BackTracking(stones, map.at(next_target), k+diff, map)) return true;
			}	
		}
		return false;
	}

    bool canCross(vector<int>& stones) {
	unordered_map<int, int> map;
	for (int i = 0; i < stones.size(); ++i) map[stones[i]] = i;
	return BackTracking(stones, 0, 0, map);
    }
};

// solution 3: 记忆化递归 + 使用二分加快下一跳目标查找
class Solution {
public:
	vector<int> idx_diff = {-1, 0, 1};
	bool BackTracking(vector<int>& stones, int idx, int k, vector<vector<bool>>& visit) {
		if (idx == stones.size() - 1) return true;
		// 剪枝
		if (visit[idx][k]) return false;
		visit[idx][k] = true;

		for (auto &diff : idx_diff) {
			int next_target = stones[idx] + k + diff;
			auto first = std::lower_bound(stones.begin() + idx + 1, stones.end(), next_target);
			if (first != stones.end() && *first == next_target) {
				if (BackTracking(stones, first - stones.begin(), k+diff, visit)) return true;
			}	
		}
		return false;
	}

    bool canCross(vector<int>& stones) {
	int len = stones.size();
	vector<vector<bool>> visit(len, vector<bool>(len, false));			// 表示是否已经计算过， 计算过的直接返回
	return BackTracking(stones, 0, 0, visit);
    }
};

// solution 3: 记忆化递归 + 使用unordered_map加快下一跳目标查找
class Solution {
public:
	vector<int> idx_diff = {-1, 0, 1};
	bool BackTracking(vector<int>& stones, int idx, int k, unordered_map<int, int>& map, vector<vector<bool>>& visit) {
		if (idx == stones.size() - 1) return true;
		// 剪枝
		if (visit[idx][k]) return false;
		visit[idx][k] = true;

		for (auto &diff : idx_diff) {
			int next_target = stones[idx] + k + diff;
			if (next_target > stones[idx] && map.count(next_target)) {
				if (BackTracking(stones, map.at(next_target), k+diff, map, visit)) return true;
			}	
		}
		return false;
	}

    bool canCross(vector<int>& stones) {
	unordered_map<int, int> map;
	for (int i = 0; i < stones.size(); ++i) map[stones[i]] = i;
	int len = stones.size();
	vector<vector<bool>> visit(len, vector<bool>(len, false));			// 表示是否已经计算过， 计算过的直接返回
	return BackTracking(stones, 0, 0, map, visit);
    }
};

//solution 4: dp; 设dp[i][k] 表示上一跳距离为k的下标为i的石头是否可达;
//		存在如下状态转移方程:
//			dp[i][k] = dp[j][k-1] || dp[j][k] || dp[j][k+1]		// 其中j取值范围为 0 ~ i-1
//
//			根据NOTE 的提示， k的有效范围为 [1, i], 可以利用这个来进行剪枝
//
//		时间O(N*N), 空间O(N*N)
class Solution {
public:
    bool canCross(vector<int>& stones) {
	int len = stones.size();
	vector<vector<bool>> dp(len, vector<bool>(len, false));	
	dp[0][0] = true;

	for (int i = 1; i < len; ++i) {
		// 剪枝一: 如果相邻两个石头之间的距离 比 相邻的前一个石头的最大跳跃范围i 还要大， 那么对于i之前的任何石头都不可能会跳到i及任何i之后石头了（即下标 >= i的石头都是不可达的）可以直接return 掉
		if (stones[i] - stones[i-1] > i) return false;	
		for (int j = i-1; j >= 0; --j) {		// j从后往前， 方便剪枝
			int k = stones[i] - stones[j];		// 直接计算可能的K值， 一些无用K的不用计算, 因为stones[i] > stones[j], 所以k > 0
			if (k > j+1)	break;			// 剪枝二: 如果下标j 不可能跳到下标i， 那么j前面的下标更加不可能了，所以可以跳出该层循环 
			dp[i][k] = dp[j][k-1] | dp[j][k] | dp[j][k+1];
		}
	}
	return *(std::max_element(dp[len-1].begin(), dp[len-1].end()));
    }
};
*/

// solution 5:
class Solution {
public:
	vector<int> idx_diff = {-1, 0, 1};
    bool canCross(vector<int>& stones) {
	unordered_map<int, unordered_set<int>> map;
	for (auto &e : stones) map[e]; 	
	map[0].insert(0);
	for (auto &e : stones) {  
		for (auto &k : map[e]) {
			for (auto &diff : idx_diff) {
				int next_target = e + k + diff;
				if (next_target > e && map.count(next_target)) map[next_target].insert(k+diff);			
			}
		} 
	}		
	return !map[stones.back()].empty();  
    }
};

int main(int argc, char *argv[]) {

	return 0;
}
