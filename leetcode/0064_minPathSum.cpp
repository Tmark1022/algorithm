/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Mon 21 Dec 2020 11:08:52 AM CST
 @ File Name	: 0064_minPathSum.cpp
 @ Description	: 64. 最小路径和 
 ************************************************************************/
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
#include <deque>
#include <unordered_map>
#include <unordered_set>

using namespace std;

/*
	solution 1: 转化为图问题, dfs 回溯搜索, 指数级时间复杂度 O(2^N), 最大递归深度N+M-2，空间复杂度为O(N+M)

	solution 2: 转化为图问题（有向加权图），单源点加权最短路径问题，使用dijkstra算法, 顶点数为M*N，每个顶点最多有两条边, 边数e < 2*N*M
		1) 常规dijkstra算法, 每次需要在N*M的数组里边取最小值顶点为作为下一个计算顶点， 选取最小值顶点需要O(NM), 所以总时间复杂度为O(NM * NM),空间复杂度 O(NM)
		2) 因为图是无环图， 所以可以参考拓扑排序的方式， 每次选取入度为0的顶点作为下一个计算顶点， 选取顶点的时间复杂度为O(1), 所以最终时间复杂度为O(N*M + e)
		   e < 2*N*M, 所以最终时间复杂度为O(NM), 空间复杂度为O(NM)

	soluton 3: 动态规划, 状态转移方程为 f(i, j) = min(f(i-1, j), f(i, j-1)) + grid[i][j]; 最终时间复杂度为O(NM), 空间复杂度为O(NM)【可以优化为O(N)】
   */


/*
// solution 1: dfs 【超时】
class Solution {
public:
	int ans = INT_MAX;	
	void dfs(int i, int j, vector<vector<int>> &grid, int step) {
		int m = grid.size(), n = grid[0].size();
		if (step >= ans) return ;
		if (i == m-1 && j == n-1) {
			ans = min(ans, step);
			return ; 
		}
		
		if (j+1 < n) dfs(i, j+1, grid, step + grid[i][j+1]);
		if (i+1 < m) dfs(i+1, j, grid, step + grid[i+1][j]);
	}


    int minPathSum(vector<vector<int>>& grid) {
	dfs(0, 0, grid, grid[0][0]);
	return ans;
    }
};

// solution 2: 普通dijkstra 【超时, 不过比solution1 要好】
class Solution {
public:
	pair<int, int> FindMin(vector<vector<int>> &dist, vector<vector<bool>>& know) {
		int m = dist.size(), n = dist[0].size(), x, y, val = INT_MAX;	
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				if (know[i][j] || dist[i][j] >= val) continue;
				x = i;
				y = j;
				val = dist[i][j];
			}
		}
		return make_pair(x,  y);
	}

    int minPathSum(vector<vector<int>>& grid) {
	int m = grid.size(), n = grid[0].size();
	vector<vector<int>> dist(m, vector<int>(n, INT_MAX));		// 总共有m*n个顶点
	vector<vector<bool>> know(m, vector<bool>(n, false));		// 总共有m*n个顶点
	dist[0][0] = grid[0][0];
	for (int cnt = 1; cnt <= m*n; ++cnt) {
		// 找最小路径
		pair<int, int> cur = FindMin(dist, know); 		
		int x = cur.first, y = cur.second;		
		know[x][y] = true;
		
		// 找到目的顶点
		if (x == m-1 && y == n-1) return dist[x][y];

		// 更新邻接顶点
		if (y+1 < n) dist[x][y+1] = min(dist[x][y+1], dist[x][y] + grid[x][y+1]);
		if (x+1 < m) dist[x+1][y] = min(dist[x+1][y], dist[x][y] + grid[x+1][y]);
	}		
	return INT_MAX;	
    }
};

// solution 2: 拓扑排序优化版dijkstra 【通过】
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
	int m = grid.size(), n = grid[0].size();
	vector<vector<int>> dist(m, vector<int>(n, INT_MAX));		// 路径长度数组， 有m*n个顶点
	dist[0][0] = grid[0][0];

	vector<vector<int>> degree(m, vector<int>(n, 0));		// 顶点入度数组
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			if (j+1 < n) ++degree[i][j+1];
			if (i+1 < m) ++degree[i+1][j];
		}
	}

	deque<pair<int, int>> que;					// 当前入度为0 
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			if (!degree[i][j]) que.push_back(make_pair(i, j));
		}
	}

	while (que.size()) {
		// 找下一个顶点
		pair<int, int> cur = que.front(); 
		que.pop_front();
		int x = cur.first, y = cur.second;		
		// 找到目的顶点
		if (x == m-1 && y == n-1) return dist[x][y];
		// 更新邻接顶点
		if (y+1 < n) {
			dist[x][y+1] = min(dist[x][y+1], dist[x][y] + grid[x][y+1]);
			if (--degree[x][y+1] <= 0) que.push_back(make_pair(x, y+1));
		}
		if (x+1 < m) {
			dist[x+1][y] = min(dist[x+1][y], dist[x][y] + grid[x+1][y]);
			if (--degree[x+1][y] <= 0) que.push_back(make_pair(x+1, y));
		}
	}		
	return INT_MAX;	
    }
};


// solution 2: 拓扑排序优化版dijkstra 【通过】, 刚好顺序访问就是一种topology排序结果, 故代码可以优化为如下
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> dist(m, vector<int>(n, INT_MAX));
        dist[0][0] = grid[0][0];
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i + 1 < m) dist[i+1][j] = min(dist[i+1][j], dist[i][j] + grid[i+1][j]);
                if (j + 1 < n) dist[i][j+1] = min(dist[i][j+1], dist[i][j] + grid[i][j+1]);
            }
        }
        return dist[m-1][n-1];
    }
};
*/

// solution 3: 动态规划, 使用一维数组辅助空间； 状态转移方程为 f(i, j) = min(f(i-1, j), f(i, j-1)) + grid[i][j]; 最终时间复杂度为O(NM), 空间复杂度为O(NM)【可以优化为O(N)】
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
	int m = grid.size(), n = grid[0].size();
	vector<int> dp(n, 0);

	// 先构造第一行数据
	for (int i = 0; i < n; ++i) {
		if (i > 0) dp[i] = dp[i-1] + grid[0][i];  
		else dp[i] =  grid[0][i];
	}

	for (int i = 1; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			if (j) dp[j] = min(dp[j-1], dp[j]) + grid[i][j]; 
			else dp[j] = dp[j] + grid[i][j];
		}	
	}
	return dp[n-1];	
    }
};




int main(int argc, char *argv[]) {

	return 0;
}
