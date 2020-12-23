/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Fri 18 Dec 2020 12:14:00 PM CST
 @ File Name	: 0200_numIslands.cpp
 @ Description	: 200. 岛屿数量 
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
solution 1: flood fill算法 dfs实现, 时间复杂度为O(MN)
solution 2: flood fill算法 bfs实现, 时间复杂度为O(MN)
solution 3: 并查集, 使用加权合并和路径压缩的并查集， find操作常为常数级别
   */

/*
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

// solution 2: bfs
class Solution {
public:	
	vector<vector<int>> xy_diff = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
	bool IsValidCoordinate(vector<vector<char>>& grid, int x, int y) {
		int m = grid.size(), n = grid[0].size();
		return x >= 0 && x < m && y >= 0 && y < n;  

	}

    int numIslands(vector<vector<char>>& grid) {
	int ans = 0;
	for (int x = 0; x < grid.size(); ++x) {
		for (int y = 0; y < grid[0].size(); ++y) {
			if (grid[x][y] != '1') continue;
			++ans;
			grid[x][y] = '0';	

			deque<pair<int, int>> que;
			que.push_back(make_pair(x, y));	
			while (que.size()) {
				pair<int, int> cur = que.front();
				que.pop_front();	

				for (auto &diff : xy_diff) {
					int r = cur.first + diff[0], c = cur.second + diff[1];	
					if (IsValidCoordinate(grid, r, c) && grid[r][c] == '1') {
						grid[r][c] = '0';	
						que.push_back(make_pair(r, c));
					}
				}	
			}	
		}
	}	
	return ans;
    }
};
*/


// solution 3: union-find set, 统计共有多少个不相交集, 总不相交集个数 - 0的个数即为最终结果
class UnionFindSet{
public:
	explicit UnionFindSet(vector<vector<char>>& grid) {
		int m = grid.size(), n = grid[0].size();
		vec.resize(m*n, -1);
		cnt = m*n;

		for (int x = 0; x < m; ++x) {
			for (int y = 0; y < n; ++y) {
				if (x + 1 < m && grid[x][y] == '1' && grid[x+1][y] == '1') Union(x*n+y, (x+1)*n+y);	
				if (y + 1 < n && grid[x][y] == '1' && grid[x][y+1] == '1') Union(x*n+y, x*n+y+1);	
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
		if (p1 == p2) return ;			// 同一个集合		
		if (vec[p1] >= vec[p2]) {
			// 注意这是负数, 节点少的合并到节点多的一方
			vec[p2] += vec[p1];
			vec[p1] = p2;
		} else {
			vec[p1] += vec[p2];
			vec[p2] = p1;
		}
		--cnt;
	}		

	int GetSetCnt() const {
		return cnt;
	}
private:
	vector<int> vec;		// 非根存储其父节点下标， 根节点存储树的节点总数
	int cnt;			// 不相交集总个数 
};

class Solution {
public:	
    int numIslands(vector<vector<char>>& grid) {
	UnionFindSet set(grid);	
	int ans = set.GetSetCnt();
	for (auto &vec : grid) {
		for (auto &e : vec) {
			if (e == '0') --ans;
		}
	}
	return ans;
    }
};




int main(int argc, char *argv[]) {

	return 0;
}
