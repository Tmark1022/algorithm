/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Fri 05 Feb 2021 05:00:34 PM CST
 @ File Name	: 1091_shortestPathBinaryMatrix.cpp
 @ Description	: 1091. 二进制矩阵中的最短路径 
 ************************************************************************/
#include <cstdlib>
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
#include <deque>
#include <unordered_map>
#include <unordered_set>
#include <queue>

using namespace std;


/*
	solution 1: dfs回溯， 时间复杂度为O(8^(m*n)), m,n为行和列

	solution 2: bfs, 时间复杂度O(n+e), n 为顶点数， e为边数； 即 O(m*n + 8*m*n), 即O(m*n)

	solution 3: 双向bfs 

	solution 4: A*， 使用优先队列， 优先队列入队和出队元素的时间复杂度为log(m*n), 宽松的时间复杂度 O(m*n*log(mn))
   */


/*
// solution 1: dfs回溯
class Solution {
public:
	vector<vector<int>> xy_diff = {{-1, 0}, {1, 0}, {0, -1}, {0,1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};			
	bool IsValidCoordinate(vector<vector<int>> &grid, int x, int y) {
		return x >= 0 && x < grid.size() && y >= 0 && y < grid[0].size();
	}

	int ans = INT_MAX;	
	void BackTracking(vector<vector<int>> &grid, int r, int c, int step) {
		int m = grid.size(), n = grid[0].size();					
		if (r == m-1 && c == n-1) {
			ans = step;
			return ;
		}		
		if (!IsValidCoordinate(grid, r, c) || grid[r][c] || step >= ans) return ;
		grid[r][c] = 1;
		for (auto &diff : xy_diff) BackTracking(grid, r+diff[0], c+diff[1], step+1);
		grid[r][c] = 0;
	}

    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
	int m = grid.size(), n = grid[0].size();	 
	if (grid[0][0] || grid[m-1][n-1]) return -1;	
	BackTracking(grid, 0, 0, 1);
	return ans == INT_MAX ? -1 : ans;
    }
};

// solution 2: bfs
class Solution {
public:
	vector<vector<int>> xy_diff = {{-1, 0}, {1, 0}, {0, -1}, {0,1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};			
	bool IsValidCoordinate(vector<vector<int>> &grid, int x, int y) {
		return x >= 0 && x < grid.size() && y >= 0 && y < grid[0].size();
	}
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
	int m = grid.size(), n = grid[0].size();	 
	if (grid[0][0] || grid[m-1][n-1]) return -1;	
	if (m <= 2) return m;		
	
	vector<bool> visit(m*n, false); 									
	visit[0] = true;				
	deque<pair<int, int>> que = {{0, 0}};
	int step = 1;	
	while (que.size()) {
		++step;
		for(int cnt = que.size(); cnt; --cnt) {
			auto cur = que.front();
			que.pop_front();
			
			for (auto &diff : xy_diff) {
				int x = cur.first + diff[0], y = cur.second + diff[1]; 
				if (x == m-1 && y == n-1) return step; 				
				if (IsValidCoordinate(grid, x, y) && !grid[x][y] && !visit[x*n+y]) {
					visit[x*n+y] = true;
					que.push_back(make_pair(x, y));
				}	
			}		
		}
	}
	return -1;
    }
};

// solution 3: 双向bfs
class Solution {
public:
	vector<vector<int>> xy_diff = {{-1, 0}, {1, 0}, {0, -1}, {0,1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};			
	bool IsValidCoordinate(vector<vector<int>> &grid, int x, int y) {
		return x >= 0 && x < grid.size() && y >= 0 && y < grid[0].size();
	}

    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
	int m = grid.size(), n = grid[0].size();	 
	if (grid[0][0] || grid[m-1][n-1]) return -1;	
	if (m <= 2) return m;		
	
	vector<bool> visit(m*n, false); 									
	visit[0] = visit[m*n-1] = true;				
	unordered_set<int> bset = {0}, eset = {m*n-1}, *head = &bset, *tail = &eset; 
	int step = 1;	
	while (head->size() && tail->size()) {	
		++step;
		if (head->size() > tail->size()) swap(head, tail); 
		
		unordered_set<int> tmp_set;
		for (auto &idx : *head) {
			int r = idx/n, c = idx%n; 
			for (auto &diff : xy_diff) {
				int x = r + diff[0], y = c + diff[1]; 
				if (!IsValidCoordinate(grid, x, y) || grid[x][y]) continue;		// 这个判断必须提上来判断， 不然计算使用异常的坐标计算的adj可能与正常的坐标计算出来的一样， 如长和宽都是6, 坐标(4, -1) 和 (3, 5)计算的adj都是23 
				int adj = x*n +y;
				if (tail->count(adj)) return step;
				if (!visit[adj]) {
					visit[adj] = true;
					tmp_set.insert(adj);
				}	
			}			
		}	
		*head = tmp_set;		
	}
	return -1;
    }
};
*/

// solution 4: A*
class Solution {
public:
	struct Node {
		int priority, distance, x, y;			
		Node(int _p1, int _p2, int _p3, int _p4) : priority(_p1), distance(_p2), x(_p3), y(_p4) {}
		bool operator>(const Node &p) const {
			return this->priority > p.priority;	
		}
	}; 

	vector<vector<int>> xy_diff = {{-1, 0}, {1, 0}, {0, -1}, {0,1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};			
	bool IsValidCoordinate(vector<vector<int>> &grid, int x, int y) {
		return x >= 0 && x < grid.size() && y >= 0 && y < grid[0].size();
	}
	
	// 估价函数
	int Heuristic(vector<vector<int>> &grid, int x, int y) {
		int m = grid.size(), n = grid[0].size();
		return max(abs(m-1-x), abs(n-1-y));
	}	

    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
	int m = grid.size(), n = grid[0].size();	 
	if (grid[0][0] || grid[m-1][n-1]) return -1;	
	if (m <= 2) return m;		
	
	vector<vector<bool>> visit(m, vector<bool>(n, false)); 									
	std::priority_queue<Node, vector<Node>, greater<Node>> que;
	que.push(Node(0, 1, 0, 0));

	while (que.size()) {
		Node cur = que.top();
		que.pop();

		// 判断节点是否访问过 		
		if (visit[cur.x][cur.y]) continue;		
		visit[cur.x][cur.y] = true;		// 【需要到这里才设置为true， 因为可能有多个路径会更新当前节点的优先级】

		// 判断终点
		if (cur.x == m-1 && cur.y == n-1) return cur.distance;	

		for (auto &diff : xy_diff) {
			int x = cur.x + diff[0], y = cur.y + diff[1];	
			if (IsValidCoordinate(grid, x, y) && !grid[x][y] && !visit[x][y]) {
				que.push(Node(cur.distance + 1 + Heuristic(grid, x, y), cur.distance + 1, x, y));
			} 
		}	
	}
	return -1;
    }
};


int main(int argc, char *argv[]) {

	return 0;
}
