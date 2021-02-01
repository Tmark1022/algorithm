/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Mon 01 Feb 2021 11:26:29 AM CST
 @ File Name	: 0130_solve.cpp
 @ Description	: 
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
	solution 1: dfs, O(N^2)  
	solution 2: bfs, O(N^2)
	solution 3: 并查集, O(N^2)
   */


/*
// solution 1: DFS
class Solution {
public:
	vector<vector<int>> xy_diff = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; 
	bool IsValidCoordinate(vector<vector<char>> &board, int x, int y) {
		return x >= 0 && x < board.size() && y >= 0 && y < board[0].size();
	}

	void Dfs(vector<vector<char>> &board, int r, int c) {
		if (!IsValidCoordinate(board, r, c) || board[r][c] != 'O') return ;
		board[r][c] = 0;
		for (auto &diff : xy_diff) Dfs(board, r+diff[0], c+diff[1]);  
	}

    void solve(vector<vector<char>>& board) {
	if (!board.size() || !board[0].size()) return ;
	int m = board.size(), n = board[0].size();			
	for (int i = 0; i < m; ++i) {
		Dfs(board, i, 0);
		Dfs(board, i, n-1);
	} 
	for (int i = 1; i < n-1; ++i) {
		Dfs(board, 0, i);
		Dfs(board, m-1, i);
	} 

	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			board[i][j] = board[i][j] ? 'X' : 'O';
		} 
	}			
    }
};


// solution 2: BFS
class Solution {
public:
	vector<vector<int>> xy_diff = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; 
	bool IsValidCoordinate(vector<vector<char>> &board, int x, int y) {
		return x >= 0 && x < board.size() && y >= 0 && y < board[0].size();
	}
    void solve(vector<vector<char>>& board) {
	if (!board.size() || !board[0].size()) return ;

	// 查找所有起点
	int m = board.size(), n = board[0].size();				
	deque<pair<int, int>> que;
	for (int i = 0; i < m; ++i) {
		if (board[i][0] == 'O') board[i][0] = 0, que.push_back(make_pair(i, 0));   
		if (board[i][n-1] == 'O') board[i][n-1] = 0, que.push_back(make_pair(i, n-1));   
	} 
	for (int i = 1; i < n-1; ++i) {
		if (board[0][i] == 'O') board[0][i] = 0, que.push_back(make_pair(0, i));   
		if (board[m-1][i] == 'O') board[m-1][i] = 0, que.push_back(make_pair(m-1, i));   
	} 
	
	// BFS	
	while (que.size()) {
		pair<int, int> cur = que.front();
		que.pop_front();
		for (auto &diff : xy_diff) {
			int x = cur.first + diff[0], y = cur.second + diff[1];	
			if (IsValidCoordinate(board, x, y) && board[x][y] == 'O') {
				board[x][y] = 0;
				que.push_back(make_pair(x, y));
			}		
		}		
	}
	
	// 构造结果
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			board[i][j] = board[i][j] ? 'X' : 'O';
		} 
	}			
    }
};
*/

// solution 3: 并查集 
class UnionFindSet{
public:
	UnionFindSet(int size):vec(size, -1) {}
	int Find(int idx) {
		if (vec[idx] < 0) return idx;
		vec[idx] = Find(vec[idx]);
		return vec[idx];
	}	

	void Union(int idx1, int idx2) {
		int p1 = Find(idx1), p2 = Find(idx2);
		if (p1 == p2) return ;
		if (vec[p1] <= vec[p2]) {
			vec[p1] += vec[p2];
			vec[p2] = p1;
		} else {
			vec[p2] += vec[p1];
			vec[p1] = p2;
		}
	}
private:
	vector<int> vec;
};

class Solution {
public:
	vector<vector<int>> xy_diff = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; 
	bool IsValidCoordinate(vector<vector<char>> &board, int x, int y) {
		return x >= 0 && x < board.size() && y >= 0 && y < board[0].size();
	}
    void solve(vector<vector<char>>& board) {
	if (!board.size() || !board[0].size()) return ;
	int m = board.size(), n = board[0].size();				

	// 构造并查集
	UnionFindSet ufs(m*n);
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			if (i + 1 < m && board[i+1][j] == board[i][j]) ufs.Union(i*n+j, (i+1)*n+j);  
			if (j + 1 < n && board[i][j+1] == board[i][j]) ufs.Union(i*n+j, i*n+j+1);  
		}
	}

	// 找出所有需要转换为O的并查集代表	
	unordered_set<int> representor;  
	for (int i = 0; i < m; ++i) {
		if (board[i][0] == 'O') representor.insert(ufs.Find(i*n));   
		if (board[i][n-1] == 'O') representor.insert(ufs.Find(i*n + n-1)); 
	} 

	for (int i = 1; i < n-1; ++i) {
		if (board[0][i] == 'O') representor.insert(ufs.Find(i)); 
		if (board[m-1][i] == 'O') representor.insert(ufs.Find((m-1)*n + i)); 
	} 
		
	// 构造结果
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			board[i][j] = representor.count(ufs.Find(i*n+j)) ? 'O' : 'X';
		} 
	}			
    }
};






int main(int argc, char *argv[]) {

	return 0;
}
