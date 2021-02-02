/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Tue 02 Feb 2021 10:48:55 AM CST
 @ File Name	: 0037_solveSudoku.cpp
 @ Description	: 37. 解数独 
 ************************************************************************/
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
#include <deque>
#include <list>
#include <unordered_map>
#include <unordered_set>

using namespace std;

/*
	solution 1: dfs回溯，赋值空间使用位来优化
	solution 2: solution 1 的基础上进行数据预处理， 先预处理处理唯一选择的空格，减少dfs 回溯递归状态树的规模
   */

/*
// solution 1: dfs 回溯
class Solution {
public:	
	bool visit = false;
	vector<int> rows = vector<int>(9,0), cols = vector<int>(9, 0), blocks = vector<int>(9, 0);
	void Flip(int r, int j, int val) {
		rows[r] ^= val;			
		cols[j] ^= val;
		blocks[r/3*3 + j/3] ^= val;
	}	

	void BackTracking(vector<vector<char>>& board, vector<pair<int,int>> &spaces, int idx) {
		if (idx == spaces.size()) {
			visit = true;
			return ;
		} 
		pair<int, int> cur = spaces[idx];
		int r = cur.first, c = cur.second;	
		int avail_val = ~(rows[r] | cols[c] | blocks[r/3*3 + c/3]) & 0x1ff;   	
		while (avail_val && !visit) {
			int val = avail_val & (-avail_val);
			avail_val &= avail_val - 1;

			Flip(r, c, val);
			board[r][c] = '1' + __builtin_ctz(val);
			BackTracking(board, spaces, idx+1);	
			Flip(r, c, val);
		}	
	}	

    void solveSudoku(vector<vector<char>>& board) {		 
	// step 1: 初始化一些数据
	vector<pair<int, int>> spaces;	
	for (int i = 0; i < board.size(); ++i) {
		for (int j = 0; j < board[i].size(); ++j) {
			if ('.' == board[i][j]) spaces.push_back(make_pair(i, j));
			else Flip(i, j, 1 << (board[i][j] - '1'));
		}
	}
	BackTracking(board, spaces, 0);
    }
};
*/

// solution 2: dfs 回溯, 数据预处理
class Solution {
public:	
	bool visit = false;
	vector<int> rows = vector<int>(9,0), cols = vector<int>(9, 0), blocks = vector<int>(9, 0);
	void Flip(int r, int j, int val) {
		rows[r] ^= val;			
		cols[j] ^= val;
		blocks[r/3*3 + j/3] ^= val;
	}	

	void BackTracking(vector<vector<char>>& board, vector<pair<int,int>> &spaces, int idx) {
		if (idx == spaces.size()) {
			visit = true;
			return ;
		} 
		pair<int, int> cur = spaces[idx];
		int r = cur.first, c = cur.second;	
		int avail_val = ~(rows[r] | cols[c] | blocks[r/3*3 + c/3]) & 0x1ff;   	
		while (avail_val && !visit) {
			int val = avail_val & (-avail_val);
			avail_val &= avail_val - 1;

			Flip(r, c, val);
			board[r][c] = '1' + __builtin_ctz(val);
			BackTracking(board, spaces, idx+1);	
			Flip(r, c, val);
		}	
	}	

    void solveSudoku(vector<vector<char>>& board) {		 
	// step 1: 初始化一些数据
	list<pair<int, int>> spaces_list;		// 因为涉及到删除spaces元素, 所以使用list结构	
	for (int i = 0; i < board.size(); ++i) {
		for (int j = 0; j < board[i].size(); ++j) {
			if ('.' == board[i][j]) spaces_list.push_back(make_pair(i, j));
			else Flip(i, j, 1 << (board[i][j] - '1'));
		}
	}

	// step 2: 预处理只有一个选择的空格， 减少dfs回溯状态树规模
	bool modified = true;	
	while (modified) {
		modified = false;
		auto it = spaces_list.cbegin();			
		while (it != spaces_list.cend()) {
			int r = it->first, c = it->second;	
			int avail_val = ~(rows[r] | cols[c] | blocks[r/3*3 + c/3]) & 0x1ff;   	
			if (!(avail_val & (avail_val-1))) {
				board[r][c] = '1' + __builtin_ctz(avail_val);	
				Flip(r, c, avail_val);
				it = spaces_list.erase(it); 
				modified = true;
			} else {
				++it;
			}	
		}
	}
	
	// step 3: 剩下的空格使用回溯来补全
	vector<pair<int, int>> spaces(spaces_list.begin(), spaces_list.end());
	BackTracking(board, spaces, 0);
    }
};




int main(int argc, char *argv[]) {

	return 0;
}
