/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Fri 25 Dec 2020 08:24:43 PM CST
 @ File Name	: 0827_largestIsland.cpp
 @ Description	: 827. 最大人工岛
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
	solution 0: 暴力， 每一个0尝试填充为1后， 再通过DFS或BFS来计算最大面积, 时间复杂度O(MN * MN)【超时】
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

	int Dfs(vector<vector<int>>& grid, int x, int y, int idx) {
		if (!IsValidCoordinate(grid, x, y) || grid[x][y] != 1) return 0;
		grid[x][y] = idx;
		int ans = 1;
		for (auto &diff : xy_diff) ans += Dfs(grid, x+diff[0], y+diff[1], idx);
		return ans;
	}

    int largestIsland(vector<vector<int>>& grid) {
	// 先计算并保存每一个岛屿的面积
	int idx = 2, m = grid.size(), n = grid[0].size(); 
	vector<int> area = {0, 0};
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			if (1 != grid[i][j]) continue;
			area.push_back(Dfs(grid, i, j, idx++));	
		}
	}	

	// 尝试填充每一个岛屿, 计算最大值
	int ans = 0; 	
	unordered_set<int> island_set;
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			if (0 != grid[i][j]) continue;

			// 将不是同一个岛屿的面积累计起来
			island_set.clear();
			int tmp = 1;
			for (auto &diff : xy_diff) {
				int x = i + diff[0], y = j + diff[1];	
				if (IsValidCoordinate(grid, x, y) && grid[x][y] && !island_set.count(grid[x][y])) {
					island_set.insert(grid[x][y]);
					tmp += area[grid[x][y]]; 
				}		
			}
			ans = max(ans, tmp);	
		}	
	}	

	// 考虑全部都是1的情况
	return ans ? ans : m*n;
    }
};


// solution 2: bfs
class Solution {
public:
	vector<vector<int>> xy_diff = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
	bool IsValidCoordinate(vector<vector<int>>& grid, int x, int y) {
		return x >= 0 && x < grid.size() && y >= 0 && y < grid[0].size();
	}

    int largestIsland(vector<vector<int>>& grid) {
	// 先计算并保存每一个岛屿的面积
	int idx = 2, m = grid.size(), n = grid[0].size(); 
	vector<int> area = {0, 0};
    	for (int i = 0; i < m; ++i) {
    		for (int j = 0; j < n; ++j) {
    			if (1 != grid[i][j]) continue;
    			int cnt = 0;
    			deque<pair<int, int>> que;
    			grid[i][j] = idx;
    			que.push_back(make_pair(i, j));
    			while (que.size()) {
    				pair<int, int> cur = que.front();
    				que.pop_front();
    				++cnt;	

    				for (auto &diff : xy_diff) {
    					int x = cur.first + diff[0], y = cur.second + diff[1];
    					if (IsValidCoordinate(grid, x, y) && grid[x][y] && grid[x][y] == 1) {
    						grid[x][y] = idx;
    						que.push_back(make_pair(x, y));
    					}
    				}
    			}	
			area.push_back(cnt);	
			++idx;
    		}
    	}	

	// 尝试填充每一个岛屿, 计算最大值
	int ans = 0; 	
	unordered_set<int> island_set;
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			if (0 != grid[i][j]) continue;

			// 将不是同一个岛屿的面积累计起来
			island_set.clear();
			int tmp = 1;
			for (auto &diff : xy_diff) {
				int x = i + diff[0], y = j + diff[1];	
				if (IsValidCoordinate(grid, x, y) && !island_set.count(grid[x][y])) {
					island_set.insert(grid[x][y]);
					tmp += area[grid[x][y]]; 
				}		
			}
			ans = max(ans, tmp);	
		}	
	}	

	// 考虑全部都是1的情况
	return ans ? ans : m*n;
    }
};
*/

// solution 3: union-find set
class UnionFindSet {
public:
	UnionFindSet(vector<vector<int>> &grid) {
		int m = grid.size(), n = grid[0].size();
		vec.resize(m*n, -1);
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				if (!grid[i][j]) continue; 	
				if (i + 1 < m && grid[i+1][j]) Union(i*n+j, (i+1)*n+j);  
				if (j + 1 < n && grid[i][j+1]) Union(i*n+j, i*n+j+1);  
			}	
		}	
	}

	int Find(int id) {
		if (vec[id] < 0) return id;
		vec[id] = Find(vec[id]);
		return vec[id];
	}

	void Union(int id1, int id2) {
		int p1 = Find(id1);
		int p2 = Find(id2);
		if (p1 == p2) return ;

		// 注意节点个数是负数
		if (vec[p1] >= vec[p2]) {
			vec[p2] += vec[p1];		
			vec[p1] = p2;
		} else {
			vec[p1] += vec[p2];		
			vec[p2] = p1;
		}
	}

	int GetTreeNodes(int id) {
		return -vec[id];
	}
private:
	vector<int> vec;
};	

class Solution {
public:
	vector<vector<int>> xy_diff = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
	bool IsValidCoordinate(vector<vector<int>>& grid, int x, int y) {
		return x >= 0 && x < grid.size() && y >= 0 && y < grid[0].size();
	}
    int largestIsland(vector<vector<int>>& grid) {
	UnionFindSet ufs(grid);

	// 尝试填充每一个岛屿, 计算最大值
	int ans = 0, m = grid.size(), n = grid[0].size();
	unordered_set<int> island_set;
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			if (grid[i][j]) continue;
			// 将不是同一个岛屿的面积累计起来
			island_set.clear();
			int tmp = 1;
			for (auto &diff : xy_diff) {
				int x = i + diff[0], y = j + diff[1];	
				if (IsValidCoordinate(grid, x, y) && grid[x][y] && !island_set.count(ufs.Find(x*n+y))) {
					int p = ufs.Find(x*n+y);
					island_set.insert(p);
					tmp += ufs.GetTreeNodes(p); 
				}		
			}
			ans = max(ans, tmp);	
		}	
	}	

	// 考虑全部都是1的情况
	return ans ? ans : m*n;
    }
};







int main(int argc, char *argv[]) {

	return 0;
}
