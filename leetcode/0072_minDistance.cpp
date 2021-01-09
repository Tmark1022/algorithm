/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Sat 09 Jan 2021 11:50:18 AM CST
 @ File Name	: 0072_minDistance.cpp
 @ Description	: 72. 编辑距离 
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
	相等 : 跳过当前字符	

	不相等 : 
		1) 字符串1 替换
		2) 字符串2 插入目标字符 
		3) 字符串3 删除目标字符

	solution 1: 回溯，试探所有可能

	solution 2: dp, 借鉴solution1 的思路， 可以得出如下状态转移方程:
			设 f(i, j) 代表 word1[1:i] 和 word2[1:j] 的最小转换次数, 这里假设字符串的第一个字符下标为1

			if word1[i] == word2[j] : f(i, j) = f(i-1, j-1);
			if word1[i] != word2[j] : f(i, j) = min(f(i-1, j-1), f(i, j-1), f(i-1, j)) + 1;
	
			base case:
				i == 0 || j == 0, f(i, j) = max(i, j);


			使用两个一维数组来进行空间优化	
   */


/*
// solution 1: 回溯 【超时】
class Solution {
public:
	int ans = INT_MAX;
	void BackTracking(string &word1, string &word2, int idx1, int idx2, int step) {
		if (idx1 == word1.size() || idx2 == word2.size()) {
			ans = min(ans, static_cast<int>(max(word1.size() - idx1, word2.size() - idx2)) + step);
			return ;
		}			
		
		if (word1[idx1] == word2[idx2]) BackTracking(word1, word2, idx1+1, idx2+1, step);		
		else {
			// 替换
			BackTracking(word1, word2, idx1+1, idx2+1, step + 1);	
			// 插入
			BackTracking(word1, word2, idx1, idx2+1, step + 1);	
			// 删除
			BackTracking(word1, word2, idx1+1, idx2, step + 1);	
		}
	}

    int minDistance(string word1, string word2) {
	BackTracking(word1, word2, 0, 0, 0);
	return ans;
    }
};
*/

// solution 2: dp, 时间复杂度O(NM), 空间复杂度 O(M)
//                      if word1[i] == word2[j] : f(i, j) = f(i-1, j-1);
//                      if word1[i] != word2[j] : f(i, j) = min(f(i-1, j-1), f(i, j-1), f(i-1, j)) + 1;
//
//                      base case:
//                              i == 0 || j == 0, f(i, j) = max(i, j);
class Solution {
public:
    int minDistance(string word1, string word2) {
        int len1 = word1.size(), len2 = word2.size();
        if (!len1 || !len2) return max(len1, len2);
        vector<vector<int>> dp(2, vector<int>(len2 + 1));

        // init
        dp[0][0] = 0;
        for (int j = 1; j <= len2; ++j) dp[0][j] = j;

        // do it
        int cur = 1, prev = 0;
        for (int i = 1; i <= len1; ++i) {
                dp[cur][0] = i;
                for (int j = 1; j <= len2; ++j) {
                        if (word1[i-1] == word2[j-1]) dp[cur][j] = dp[prev][j-1];
                        else dp[cur][j] = min(min(dp[prev][j-1], dp[cur][j-1]), dp[prev][j]) + 1;
                }
                swap(cur, prev);
        }

        return dp[prev][len2];
    }
};



int main(int argc, char *argv[]) {
	

	return 0;
}
