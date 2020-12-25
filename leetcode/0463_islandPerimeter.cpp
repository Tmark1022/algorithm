/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Fri 25 Dec 2020 11:10:23 AM CST
 @ File Name	: 0463_islandPerimeter.cpp
 @ Description	: 463. 岛屿的周长
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
	solution 1: 遍历每一个格子， 是1陆地周长就加4, 判断上下左右是否也是陆地， 是陆地周长就减1;
			这种方法只能用于求地图上所有岛屿的总周长（或地图只有一个岛屿时， 该岛屿的周长）

	solution 1【优化版】: 当然该计算周长方式可以改变一下，变更为对于每一个陆地， 只判断右和下是否为陆地， 如果是陆地， 周长减2


	solution 2: 遍历每一个格子， 是陆地就调用dfs/bfs， 遍历相邻的所有陆地， 求出所有陆地组合起来的周长， 该方法可以计算到地图中每一个岛屿的周长 
   */



/*
// soluton 1: 优化版
class Solution {
public:
    int islandPerimeter(vector<vector<int>>& grid) {
	int ans = 0, m = grid.size(), n = grid[0].size();		
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			if (!grid[i][j]) continue;
			ans += 4;	
			if (i + 1 < m && grid[i+1][j]) ans -= 2; 
			if (j + 1 < n && grid[i][j+1]) ans -= 2; 
		}
	}
	return ans;
    }
};
*/

// soluton 2: dfs
class Solution {
public:
	vector<vector<int>> xy_diff = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
	bool IsValidCoordinate(int x, int y, vector<vector<int>>& grid) {
		return x >= 0 && x < grid.size() && y >= 0 && y < grid[0].size();
	}

	void Dfs(vector<vector<int>>& grid, vector<vector<bool>>& visit, int x, int y, int &ans) {
		ans += 4;			
		for (auto &diff : xy_diff) {
			int r = x + diff[0], c = y + diff[1];
			if (IsValidCoordinate(r, c, grid) && grid[r][c]) {
				ans -= 1;
				if (!visit[r][c]) {
					visit[r][c] = true; 
					Dfs(grid, visit, r, c, ans);
				}
			}
		}	
	}

    int islandPerimeter(vector<vector<int>>& grid) {
	int ans = 0, m = grid.size(), n = grid[0].size();		
	vector<vector<bool>> visit(m, vector<bool>(n, false));
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			if (!grid[i][j] || visit[i][j]) continue;
			visit[i][j] = true;
			Dfs(grid, visit, i, j, ans);

			// 按照题意， 只有一个岛屿， 所以可以直接return
			// return ans;
		}
	}
	return ans;
    }
};




int main(int argc, char *argv[]) {

	return 0;
}
