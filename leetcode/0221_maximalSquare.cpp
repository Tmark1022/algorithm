/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Tue 12 Jan 2021 10:19:41 AM CST
 @ File Name	: 0221_maximalSquare.cpp
 @ Description	: 221. 最大正方形
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
	solution 1: brute force

	solution 2: dp, f(i, j) 代表以<i,j>坐标为右下角的最大正方形的边长 
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
	bool IsSquare(vector<vector<char>> &matrix, int r, int c, int n) {
		for (int i = r; i < r+n; ++i) {
			for (int j = c; j < c+n; ++j) { 
				if ('0' == matrix[i][j]) return false;
			}
		}		
		return true;
	}
    int maximalSquare(vector<vector<char>>& matrix) {
	int m = matrix.size(), n = matrix[0].size(), max_side = min(m, n);		
	for (int k = max_side; k >= 1; --k) {
		for (int i = 0; i < m - k + 1; ++i){
			for (int j = 0; j < n - k + 1; ++j) {
				if (IsSquare(matrix, i, j, k)) return k*k;
			}
		}
	}	
	return 0;
    }
};
*/

// soluton 2: dp, 空间优化 f(i,j) = min{f(i-1, j-1), f(i-1, j), f(i, j-1)} + 1;
class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
	int m = matrix.size(), n = matrix[0].size(), ans = 0;		
	vector<int> dp(n+1, 0);	
	for (int i = 1; i <= m; ++i){
		int north_east = 0;
		for (int j = 1; j <= n; ++j) {
			int tmp = dp[j];
			if ('0' == matrix[i-1][j-1]) dp[j] = 0;
			else dp[j] = min(dp[j], min(dp[j-1], north_east)) + 1; 
			north_east = tmp;
			ans = max(ans, dp[j]);
		}
	}
	return ans*ans;
    }
};



int main(int argc, char *argv[]) {

	return 0;
}
