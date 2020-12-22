/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Mon 21 Dec 2020 11:36:35 AM CST
 @ File Name	: 0063_uniquePathsWithObstacles.cpp
 @ Description	: 63. 不同路径 II 
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
	solution 1: 转换为图问题， dfs 回溯搜索
	solution 2: 动态规划(bottom up), O(MN)
   */

/*
// solution 1: dfs 回溯, 指数级时间复杂度
class Solution {
public:
	void dfs(int i, int j, vector<vector<int>> &obstacleGrid, int &ans) {
		int m = obstacleGrid.size(), n = obstacleGrid[0].size();
		if (i >= m || j >= n || obstacleGrid[i][j]) return ;
		// 终点有可能也是一个障碍， 所以要先判断障碍
		if (i == m-1 && j == n-1) {
			++ans;
			return ;
		}
		dfs(i, j+1, obstacleGrid, ans);	
		dfs(i+1, j, obstacleGrid, ans);	
	}	
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
	    int ans = 0;
	    dfs(0, 0, obstacleGrid, ans);
	    return ans;
    }
};
*/


// solution 2: 动态规划， bottom up
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
	// 起点就是障碍
	if (obstacleGrid[0][0]) return 0;
	int m = obstacleGrid.size(), n = obstacleGrid[0].size();
	vector<int> dp(n, 0);  	
	dp[0] = 1;
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			if (obstacleGrid[i][j])	dp[j] = 0;
			else if (j) dp[j] += dp[j-1];				// j == 0时不是障碍， 直接取上一行的首位结果
		}
	}	
	return dp[n-1];
    }
};



int main(int argc, char *argv[]) {

	return 0;
}
