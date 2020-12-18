/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Fri 18 Dec 2020 12:14:00 PM CST
 @ File Name	: 0200_numIslands.cpp
 @ Description	: 200. 岛屿数量 
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
solution 1: flood fill算法 dfs实现, 时间复杂度为O(MN)
solution 2: flood fill算法 bfs实现, 时间复杂度为O(MN)
solution 3: 并查集, 利用加权合并和路径压缩， find操作常为常数级别
   */

// solution 1: dfs
class Solution {
public:	
	vector<vector<int>> xy_diff = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
	bool IsValidCoordinate(vector<vector<char>>& grid, int x, int y) {
		int m = grid.size(), n = grid[0].size();
		return x >= 0 && x < m && y >= 0 && y < n;  

	}

	void Dfs(vector<vector<char>>& grid, int x, int y) {	
		for (auto &diff : xy_diff) {
			int r = x + diff[0], c = y + diff[1];	
			if (IsValidCoordinate(grid, r, c) && grid[r][c] == '1') {
				grid[r][c] = '0';
				Dfs(grid, r, c);	
			}
		}	
	}

    int numIslands(vector<vector<char>>& grid) {
	int ans = 0;
	for (int x = 0; x < grid.size(); ++x) {
		for (int y = 0; y < grid[0].size(); ++y) {
			if (grid[x][y] != '1') continue;
			++ans;
			grid[x][y] = '0';
			Dfs(grid, x, y);
		}
	}	
	return ans;
    }
};


int main(int argc, char *argv[]) {

	return 0;
}
