/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Mon 01 Feb 2021 08:27:08 PM CST
 @ File Name	: 0036_isValidSudoku.cpp
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

// solution 1: 直接遍历, 因为只有9个数， 直接使用数组来替代unordered_set
class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        vector<vector<bool>> rows(9, vector<bool>(9, false)), cols(9, vector<bool>(9, false)), blocks(9, vector<bool>(9, false));
        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < board[i].size(); ++j) {
                if (board[i][j] == '.') continue; 
		int idx = board[i][j] - '1';

                // rows 
                if (rows[i][idx]) return false;
                rows[i][idx] = true;

                // rows 
                if (cols[j][idx]) return false;
		cols[j][idx] = true;

                // blocks
                if (blocks[i/3*3+j/3][idx]) return false;
                blocks[i/3*3+j/3][idx] = true; 
            }
        }      
        return true;
    }
};


int main(int argc, char *argv[]) {

	return 0;
}
