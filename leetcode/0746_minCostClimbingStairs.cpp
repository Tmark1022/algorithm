/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Tue 12 May 2026 11:59:03 AM CST
 @ File Name	: 0746_minCostClimbingStairs.cpp
 @ Description	: 746. 使用最小花费爬楼梯
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
	// solution 1: backtracking
	// solution 2: dijkstra; O(N^2)
	// soltuion 3: topology 优化 dijkstra 选点逻辑;	O(N)
	// solution 4: dp; O(N)

*/

/*
// solution 1: backtracking
class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int res = INT_MAX;
        backtracking(0, cost, 0, res);
        backtracking(1, cost, 0, res);
        return res;
    }

    void backtracking(int idx, vector<int> &cost, int tmp, int &res) {
        if (idx >= cost.size()) {
            res = min(tmp, res);
            return ;
        }

        // pruning
        if (tmp >= res) return ;
        backtracking(idx + 1, cost, tmp + cost[idx], res);
        backtracking(idx + 2, cost, tmp + cost[idx], res);
    }
};


// solution 2: dijkstra; O(N^2)
class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int len = cost.size();
        vector<int> dst(len + 2, INT_MAX);
        dst[0] = dst[1] = 0;
        while (true) {
            // pick not visited, lowest dst
            int idx = -1;
            for (int i = 0; i < dst.size(); ++i) {
                if (dst[i] < 0) continue;
                if (idx < 0 || dst[idx] > dst[i]) idx = i;
            }

            // bingo
            if (idx >= len) break;

            dst[idx + 1] = min(dst[idx + 1], dst[idx] + cost[idx]);
            dst[idx + 2] = min(dst[idx + 2], dst[idx] + cost[idx]);

            // visited flag
            dst[idx] = -1;
        }
        return min(dst[len], dst[len + 1]);
    }
};

// soltuion 3: topology 优化 dijkstra 选点逻辑;
//              time complexty O(N), 最优解法
class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int len = cost.size();
        vector<int> dst(len + 2, INT_MAX);
        dst[0] = dst[1] = 0;
        for (int i = 0; i < len; ++i) {
            dst[i+1] = min(dst[i+1], dst[i] + cost[i]);
            dst[i+2] = min(dst[i+2], dst[i] + cost[i]);
        }
        return min(dst[len], dst[len + 1]);
    }
};
*/


// solution 4: dp;
/*
    状态定义：
        f(i) 表示调到i台阶最小的花费

    状态转移方程：
        f(i) = min(f(i-1) + cost[i-1], f(i-2) + cost[i-2]);

    time complexity : O(N)
    space complexity: O(N)      ==> rotating variable O(1)

    时间空间最优
*/
class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int dp0 = 0, dp1 = 0, dp;
        for (int i = 2; i <= cost.size(); ++i) {
            dp = min(dp0 + cost[i-2], dp1 + cost[i-1]);
            dp0 = dp1;
            dp1 = dp;
        }
        return dp1;
    }
};




int main(int argc, char *argv[]) {

	return 0;
}
