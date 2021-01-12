/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Tue 12 Jan 2021 11:27:17 AM CST
 @ File Name	: 1277_countSquares.cpp
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
	这道题目与leetcode 221 题类似
	solution 1: brute force

	solution 2: dp, f(i, j) 代表以<i,j>坐标为右下角的最大正方形的边长【其实另一层隐含意思就是以i,j为右下角最多含有多少个正方形】
			存在如下状态转移方程:
				f(i,j) = min{f(i-1, j-1), f(i-1, j), f(i, j-1)} + 1;

			base case:
				1) 如果matrix[i][j] == 0, f(i,j) = 0;
				2) 如果 i == -1 或 j == -1, f(i,j) = 0;  
   */


/*
// solution 1:brute force 
class Solution {
public:
	bool IsSquare(vector<vector<int>> &matrix, int r, int c, int n) {
		for (int i = r; i < r+n; ++i) {
			for (int j = c; j < c+n; ++j) { 
				if (!matrix[i][j]) return false;
			}
		}		
		return true;
	}

    int countSquares(vector<vector<int>>& matrix) {
	int m = matrix.size(), n = matrix[0].size(), max_side = min(m, n), ans = 0;		
	for (int k = max_side; k >= 1; --k) {
		for (int i = 0; i < m - k + 1; ++i){
			for (int j = 0; j < n - k + 1; ++j) {
				if (IsSquare(matrix, i, j, k)) ++ans;
			}
		}
	}	
	return ans;
    }
};
*/

// soluton 2: dp, 空间优化 f(i,j) = min{f(i-1, j-1), f(i-1, j), f(i, j-1)} + 1;
class Solution {
public:
    int countSquares(vector<vector<int>>& matrix) {
	int m = matrix.size(), n = matrix[0].size(), ans = 0;		
	vector<int> dp(n+1, 0);	
	for (int i = 1; i <= m; ++i){
		int north_east = 0;
		for (int j = 1; j <= n; ++j) {
			int tmp = dp[j];
			if (!matrix[i-1][j-1]) dp[j] = 0;
			else {
				dp[j] = min(dp[j], min(dp[j-1], north_east)) + 1; 
				ans += dp[j];
			}
			north_east = tmp;
		}
	}
	return ans;
    }
};


int main(int argc, char *argv[]) {

	return 0;
}
