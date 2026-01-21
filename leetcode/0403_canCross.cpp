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
		这道题目有一个关键的信息: 就是下标为i的石头， 最大的下一跳距离为i+1;  即当在下标idx时， 其上一条值k最大也为idx

	solution 1: 朴素回溯搜索; 时间O(3^N), 空间O(1) or O(N)考虑递归深度; 朴素在于通过for循环寻找可行的下一跳石头

	solution 2: 优雅回溯搜索(使用二分查找【收敛于 >= x+k-1】或unordered_map来判断下一跳是否存在); 时间O(3^N), 空间O(1) or O(N)考虑递归深度

	solution 3: 优雅回溯搜索 + 记忆化递归进行剪枝; 使用N*N的二维数组visit 来保存搜索记录，如visit[idx][k] 代表上一跳距离为k的第idx块石头是否计算访问过了。
			使用了记忆化递归后的递归总次数为N*N（即	N个石头 * 最大跳距离为N）
			当使用unordered_map来判断下一跳是否存在时， 总的时间复杂度为O(N*N), 空间复杂度为O(N*N)
	
	solution 4: dp
			设 f(i, k) 表示从起点出发， 是否存在一条路劲到达下标i时， 上一跳为k
    			存在如下递推关系式：
    			    f(i, k) = f(j, k+1) || f(j, k) || f(j, k+1) ; 其中j为 stones[i] - k 对应的下标 

    			f(i, k) 中，k <= i 才有意义;    故当k > i, f(i, k) = false;
    			且当i > 0时， k >= 1才有意义， 因为只能往前跳; 故当 i>0 && k <= 0, f(i, k) = false;
    			f(0, 0) = true;
    			
    			time complexity : O（N^2）
    			space complexity : O (N^2)
	
	solution 5: dp 思路逆转【不清楚这是否还算是dp】; solution 4 是根据i之前的计算结果判断当前i是否可达, 这里思路转换一下， 根据i可达， 判断i后面的石头的可达情况;
				使用到辅助数据 unordered_map<int, set<int>> map 记录可达情况; 集合set表示能够到达下标i的石头时，前一跳距离为多少	
				容易可得， map[i].empty() 表示下标i的石头不可达

			时间O(N*N), 空间O(N*N)
 
		    NOTE:
			该解法类似求无环图最短路径时， 利用拓扑排序+BFS的思想。
			traceback求解时的递归状态树即抽象为无环图，循序遍历stones数组即刚好是拓扑排序
   */

/*
// solution 1: brute force
class Solution {
public:
    bool canCross(vector<int>& stones) {
        return recurse(stones, 0, 0);
    }

    bool recurse(const vector<int> &stones, int idx, int k) {
        if (idx == stones.size() - 1) return true;

        bool bingo = false;
        for (int i = idx + 1, diff = 0; i < stones.size() && (diff = stones[i] - stones[idx]) <= k + 1 && !bingo; ++i) {
            if (diff < k - 1) continue;
            bingo = recurse(stones, i, diff);
        }
        return bingo;
    }
};

// solution 2: brute force, traceback的基础上进行， 二分查找优化寻找下一跳
class Solution {
public:
    bool canCross(vector<int>& stones) {
        return recurse(stones, 0, 0);
    }

    bool recurse(const vector<int> &stones, int idx, int k) {
        if (idx == stones.size() - 1) return true;
        bool bingo = false;
        auto it = lower_bound(stones.begin() + idx + 1, stones.end(), stones[idx] + k - 1);
        for (; it != stones.end() && *it <= stones[idx] + k + 1 && !bingo; ++it) {
            bingo = recurse(stones, distance(stones.begin(), it), *it - stones[idx]);
        }
        return bingo;
    }
};

// solution 2: brute force, traceback的基础上进行， 利用哈希表优化寻找下一跳
class Solution {
public:
    vector<int> idxDiff = {-1, 0, 1};
    bool canCross(vector<int>& stones) {
        unordered_map<int, int> mm;
        for (int i = 0; i < stones.size(); ++i) mm[stones[i]] = i;
        return recurse(stones, 0, 0, mm);
    }

    bool recurse(const vector<int> &stones, int idx, int k, unordered_map<int, int> &mm) {
        if (idx == stones.size() - 1) return true;
        bool bingo = false;
        for (auto diff : idxDiff) {
            int next = stones[idx] + k + diff; 
            if (next <= stones[idx] || !mm.count(next)) continue;
            bingo = recurse(stones, mm[next], k + diff, mm);      
            if (bingo) break;
        }
        return bingo;
    }
};


// solution 3【accept】: brute force, traceback的基础上进行， 二分查找优化寻找下一跳
//              加上记忆化搜索进行pruning, 最终时间复杂度为O(N^2), 空间复杂度为O（N^2）
class Solution {
public:
    bool canCross(vector<int>& stones) {
        vector<vector<bool>> visit;
        for (int i = 0; i < stones.size(); ++i) visit.emplace_back(i + 1, false);
        return recurse(stones, 0, 0, visit);
    }

    bool recurse(const vector<int> &stones, int idx, int k, vector<vector<bool>> &visit) {
        if (idx == stones.size() - 1) return true;
        // pruning
        if (visit[idx][k]) return false; 
        visit[idx][k] = true; 
        
        bool bingo = false;
        auto it = lower_bound(stones.begin() + idx + 1, stones.end(), stones[idx] + k - 1);  
        for (; it != stones.end() && *it <= stones[idx] + k + 1 && !bingo; ++it) {
            bingo = recurse(stones, distance(stones.begin(), it), *it - stones[idx], visit); 
        }
        return bingo;
    }
};

// solution 3【accept】: brute force, traceback的基础上进行， 利用哈希表优化寻找下一跳
//              加上记忆化搜索进行pruning， 时间复杂度O(N^2)
class Solution {
public:
    vector<int> idxDiff = {-1, 0, 1};
    bool canCross(vector<int>& stones) {
        unordered_map<int, int> mm;
        vector<vector<bool>> visit; 
        for (int i = 0; i < stones.size(); ++i) {
            mm[stones[i]] = i;
            visit.emplace_back(i+1, false);
        }
        return recurse(stones, 0, 0, mm, visit);
    }

    bool recurse(const vector<int> &stones, int idx, int k, unordered_map<int, int> &mm, vector<vector<bool>> &visit) {
        if (idx == stones.size() - 1) return true;
        // pruning
        if (visit[idx][k]) return false;
        visit[idx][k] = true;

        bool bingo = false;
        for (auto diff : idxDiff) {
            int next = stones[idx] + k + diff; 
            if (next <= stones[idx] || !mm.count(next)) continue;
            bingo = recurse(stones, mm[next], k + diff, mm, visit);      
            if (bingo) break;
        }
        return bingo;
    }
};

// solution 4: dp
//    设 f(i, k) 表示从起点出发， 是否存在一条路劲到达下标i时， 上一跳为k
//    存在如下递推关系式：
//        f(i, k) = f(j, k+1) || f(j, k) || f(j, k+1) ; 其中j为 stones[i] - k 对应的下标 
//
//    f(i, k) 中，k <= i 才有意义;    故当k > i, f(i, k) = false;
//    且当i > 0时， k >= 1才有意义， 因为只能往前跳; 故当 i>0 && k <= 0, f(i, k) = false;
//    f(0, 0) = true;
//    
//    time complexity : O（N^2）
//    space complexity : O (N^2)
class Solution {
public:
    bool canCross(vector<int>& stones) {
        vector<vector<bool>> dp = {{true}}; 
        unordered_map<int, int> mm = {{stones[0], 0}}; 
        for (int i = 1; i < stones.size(); ++i) {
            // pruning
            if (stones[i] - stones[i-1] > i) return false;
            
            mm[stones[i]] = i;
            dp.emplace_back(i+1, false);  
            for (int k = 1; k <= i; ++k) {
                if (mm.count(stones[i] - k) == 0) continue;         // 没有找到j 
                int j = mm[stones[i] - k]; 
                for (int tmp = k-1; tmp <= j && tmp <= k+1; ++tmp) {
                    dp[i][k] = dp[i][k] || dp[j][tmp];  
                }
            }
        } 
        return find(dp.back().begin(), dp.back().end(), true) != dp.back().end();
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

// solution 5: 无环图最短路径解法借鉴： topology + BFS
//                  递归状态数抽象为无环图
//                  foreach stones 刚好是 topology result
//
//          Note:
//              k <= i
//
//          time complexity : O(N^2)
//          space complexity : O(N^2)
class Solution {
public:
    bool canCross(vector<int>& stones) {
        unordered_map<int, unordered_set<int>> mm;

        // INIT STONE MAP
        for (auto &e : stones) mm[e];
        mm[stones[0]].insert(0);

        // topology
        const vector<int> kDiff = {-1, 0, 1};
        for (auto &e : stones) {
            for (auto &k : mm[e]) {
                // adjacent vertex
                for (auto &diff : kDiff) {
                    auto next = e + k + diff;
                    if (next <= e || !mm.count(next)) continue;
                    mm[next].insert(k + diff);
                }
            }
        }

        return mm[stones.back()].size();
    }
};

int main(int argc, char *argv[]) {

	return 0;
}
