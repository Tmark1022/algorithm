/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Mon 28 Dec 2020 02:30:38 PM CST
 @ File Name	: 1143_longestCommonSubsequence.cpp
 @ Description	: 1143. 最长公共子序列 
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

// solution 1: dp, 时间复杂度O(MN), 空间复杂度O(MN);
//		i/j 分别是text1 和 text2的下标, f(i,j) 表示 text1[1...i] 和 text2[1...j]的最大公共子序列长度（下标从1开始）
//		状态转移方程如下： 
//			if text1[i] == text2[j]: f(i,j) = f(i-1, j-1) + 1	
//			if text1[i] != text2[j]: f(i,j) = max{f(i-1, j), f(i, j-1)} 
//			
//			其中 i <= 0 || j <= 0 时， f(i, j) = 0;			
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
	vector<vector<int>> dp(text1.size() + 1, vector<int>(text2.size() + 1, 0));		
	for (int i = 1; i <= text1.size(); ++i) {
		for (int j = 1; j <= text2.size(); ++j) {
			if (text1[i-1] == text2[j-1]) dp[i][j] = dp[i-1][j-1] + 1;
			else dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
		}
	}
	return dp[text1.size()][text2.size()]; 
    }
};


int main(int argc, char *argv[]) {

	return 0;
}
