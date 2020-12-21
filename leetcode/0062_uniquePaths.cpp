/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Mon 21 Dec 2020 11:32:36 AM CST
 @ File Name	: 0062_uniquePaths.cpp
 @ Description	: 62. 不同路径 
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
	solution 1: 转换为图问题，dfs 递归回溯搜索, 时间复杂度为指数级 
	solution 2: 动态规划(记忆化递归); f(i,j)表示从起点到达grid[i][j]共有多少种路径, 状态转移方程为f(i,j) = f(i-1, j) + f(i, j-1); 其中f(0, 0) = 1;
	solution 3: 动态规划(bottom up)
	solution 4: 数学公式
   */


/*
// solution 1: dfs【超时】
class Solution {
public:
	vector<vector<int>> xy_diff = {{0, 1}, {1, 0}};
	bool IsValidCoordinate(int i, int j, int m, int n) {
		return i >= 1 && i <= m && j >= 1 && j <= n;
	}

    void dfs(int i, int j, int m, int n, int &ans) {
	if (!IsValidCoordinate(i, j, m, n)) return ;
	if (i == m && j == n) {
		// 到达终点
		++ans;
		return ;
	}

	// 当前顶点所有边
	for (auto &diff : xy_diff) {
		dfs(i+diff[0], j+diff[1], m, n, ans);
	}
    }

    int uniquePaths(int m, int n) {
	int ans = 0;	
	dfs(1, 1, m, n, ans);
	return ans;
    }
};

// solution 2: 记忆化递归 
class Solution {
public:
	bool IsValidCoordinate(int i, int j, int m, int n) {
		return i >= 1 && i <= m && j >= 1 && j <= n;
	}

    int uniquePaths(int m, int n, vector<vector<int>>& dp) {
	if (m < 0 || n < 0) return 0;
	if (dp[m][n]) return dp[m][n];
	dp[m][n] = uniquePaths(m-1, n, dp) + uniquePaths(m, n-1, dp);	
	return dp[m][n];
    }

    int uniquePaths(int m, int n) {
	vector<vector<int>> dp(m, vector<int>(n));
	dp[0][0] = 1;
	return uniquePaths(m-1, n-1, dp);
    }
};

// solution 3: 动态规划 bottom up ,空间复杂度优化为只使用一维数组 
class Solution {
public:
    int uniquePaths(int m, int n) {
	vector<int> dp(n, 1);
	for (int i = 1; i < m; ++i) {
		for (int j = 1; j < n; ++j) {
			dp[j] += dp[j-1]; 
		}
	}
	return dp[n-1];
    }
};
*/

// solution 4:  数学公式法, 注意整数溢出和整数除法问题， 这里需要从小到大的除
class Solution {
public:
    int uniquePaths(int m, int n) {
	    long long  ans = 1;
	    for (int i = 1, j = m; i < n; ++i, ++j) ans = ans * j / i;
	    return ans;
    }
};




int main(int argc, char *argv[]) {

	return 0;
}
