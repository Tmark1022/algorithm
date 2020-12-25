/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Fri 25 Dec 2020 01:37:27 PM CST
 @ File Name	: 0695_maxAreaOfIsland.cpp
 @ Description	: 695. 岛屿的最大面积 
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
	solution 1: dfs	 
	solution 2: bfs	
	solution 3: union-find set 
   */

/*
// solution 1: dfs
class Solution {
public:
	vector<vector<int>> xy_diff = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
	bool IsValidCoordinate(vector<vector<int>>& grid, int x, int y) {
		return x >= 0 && x < grid.size() && y >= 0 && y < grid[0].size();
	}

	int Dfs(vector<vector<int>>& grid, int x, int y) {
		if (!IsValidCoordinate(grid, x, y) || !grid[x][y]) return 0;
		grid[x][y] = 0;
		int ans = 1;
		for (auto &diff : xy_diff) ans += Dfs(grid, x+diff[0], y+diff[1]);
		return ans;
	}

    int maxAreaOfIsland(vector<vector<int>>& grid) {
	int ans = 0; 	
	for (int i = 0; i < grid.size(); ++i) {
		for (int j = 0; j < grid[i].size(); ++j) {
			if (!grid[i][j]) continue;
			ans = max(ans, Dfs(grid, i, j));
		}
	}	
	return ans;
    }
};

// solution 2: bfs
class Solution {
public:
	vector<vector<int>> xy_diff = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
	bool IsValidCoordinate(vector<vector<int>>& grid, int x, int y) {
		return x >= 0 && x < grid.size() && y >= 0 && y < grid[0].size();
	}
    int maxAreaOfIsland(vector<vector<int>>& grid) {
	int ans = 0; 	
	for (int i = 0; i < grid.size(); ++i) {
		for (int j = 0; j < grid[i].size(); ++j) {
			if (!grid[i][j]) continue;
			int cnt = 0;
			deque<pair<int, int>> que;
			grid[i][j] = 0;
			que.push_back(make_pair(i, j));
			while (que.size()) {
				pair<int, int> cur = que.front();
				que.pop_front();
				++cnt;	

				for (auto &diff : xy_diff) {
					int x = cur.first + diff[0], y = cur.second + diff[1];
					if (IsValidCoordinate(grid, x, y) && grid[x][y]) {
						grid[x][y] = 0;
						que.push_back(make_pair(x, y));
					}
				}
			}	
			ans = max(ans, cnt);
		}
	}	
	return ans;
    }
};
*/

// solution 3: union-find set
class UnionFindSet {
public:
	UnionFindSet(vector<vector<int>> &grid) {
		int m = grid.size(), n = grid[0].size();
		vec.resize(m*n, -1);
		max_tree_cnt = 0;

		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				if (!grid[i][j]) continue; 	
				max_tree_cnt = max(max_tree_cnt, 1);	
				if (i + 1 < m && grid[i+1][j]) max_tree_cnt = max(max_tree_cnt, Union(i*n+j, (i+1)*n+j));  
				if (j + 1 < n && grid[i][j+1]) max_tree_cnt = max(max_tree_cnt, Union(i*n+j, i*n+j+1));  
			}	
		}	
	}

	int Find(int id) {
		if (vec[id] < 0) return id;
		vec[id] = Find(vec[id]);
		return vec[id];
	}

	int Union(int id1, int id2) {
		int p1 = Find(id1);
		int p2 = Find(id2);
		if (p1 == p2) return vec[p1];

		// 注意节点个数是负数
		int ret;
		if (vec[p1] >= vec[p2]) {
			vec[p2] += vec[p1];		
			vec[p1] = p2;
			ret = -vec[p2];
		} else {
			vec[p1] += vec[p2];		
			vec[p2] = p1;
			ret = -vec[p1];
		}
		return ret;
	}

	int GetMaxTreeCnt() {
		return max_tree_cnt;
	}

private:
	vector<int> vec;
	int max_tree_cnt;
};	

class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
	UnionFindSet ufs(grid);
	return ufs.GetMaxTreeCnt();
    }
};



int main(int argc, char *argv[]) {

	return 0;
}
