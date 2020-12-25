/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Fri 25 Dec 2020 11:53:12 AM CST
 @ File Name	: 0892_surfaceArea.cpp
 @ Description	: 
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
	solution 1: 计算重叠的面， result = 总面数 - 重叠面数
			向右和下计算重叠面数， 
	
	solution 2: 直接计算每一个坐标拥有的面数

   */


/*
// solution 1:
class Solution {
public:
    int surfaceArea(vector<vector<int>>& grid) {
	int cube = 0, overlap = 0, m = grid.size(), n = grid[0].size();
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {		
			cube += grid[i][j];
			overlap += max(grid[i][j] - 1, 0);	
			if (i+1 < m) overlap += min(grid[i][j], grid[i+1][j]); 
			if (j+1 < n) overlap += min(grid[i][j], grid[i][j+1]); 
		}
	}
	return cube * 6 - overlap * 2;
    }
};
*/

// solution 2:
class Solution {
public:
	vector<vector<int>> xy_diff = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
	bool IsValidCoordinate(vector<vector<int>>& grid, int x, int y) {
		return x >= 0 && x < grid.size() && y >= 0 && y < grid[0].size();
	}

    int surfaceArea(vector<vector<int>>& grid) {
	int ans = 0, m = grid.size(), n = grid[0].size();
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {		
			if (!grid[i][j]) continue;
			ans += 2;
			for (auto &diff : xy_diff) {
				int x = i + diff[0], y = j + diff[1];
				ans += max(0, grid[i][j] - (IsValidCoordinate(grid, x, y) ? grid[x][y] : 0));
			}	
		}
	}
	return ans;
    }
};


int main(int argc, char *argv[]) {

	return 0;
}
