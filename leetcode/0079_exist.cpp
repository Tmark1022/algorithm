/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Thu 28 Jan 2021 07:22:33 PM CST
 @ File Name	: 0079_exist.cpp
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
	solution 1: dfs 回溯搜索; 时间复杂度为O(M*N*4^k), 其中 M和N为二维数组的行和列， k为word长度, 4^K是回溯搜索的时间复杂度 
   */


// solution 1: dfs 回溯搜索
class Solution {
public:
	vector<vector<int>> xy_diff = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
	bool IsValidCoordinate(vector<vector<char>>& board, int x, int y) {
		return x >= 0 && x < board.size() && y >= 0 && y < board[0].size();
	}		
	bool BackTracking(vector<vector<char>> &board, int r, int c, string &word, int idx) {
		if (idx == word.size()) return true;		
		if (!IsValidCoordinate(board, r, c) || board[r][c] != word[idx]) return false; 

		char tmp = board[r][c];		
		board[r][c] = 0;
		bool flag = false;			
		for (auto &diff : xy_diff) {
			flag = BackTracking(board, r+diff[0], c+diff[1], word, idx+1); 
			if (flag) break; 
		}
		board[r][c] = tmp;
		return flag;
	}	

    bool exist(vector<vector<char>>& board, string word) {
	    for (int i = 0; i < board.size(); ++i) {
		    for (int j = 0; j < board[i].size(); ++j) {
			if (BackTracking(board, i, j, word, 0)) return true;
		    }
	    }
	    return false;
    }
};


int main(int argc, char *argv[]) {

	return 0;
}
