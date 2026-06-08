/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Mon 08 Jun 2026 03:28:42 PM CST
 @ File Name	: 0044_isMatch.cpp
 @ Description	: 44. 通配符匹配 
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
// solution 1: brute force
class Solution {
public:
    bool isMatch(string s, string p) {
        return backtracking(s, 0, p, 0);
    }

    bool backtracking(string &s, int sidx, string &p, int pidx) {
        if (p.size() == pidx) return sidx == s.size();
        if (sidx == s.size()) {
            if (p[pidx] == '*') return backtracking(s, sidx, p, pidx + 1);
            else return false;
        }

        if (p[pidx] == '*') {
            return backtracking(s, sidx + 1, p, pidx) || backtracking(s, sidx, p, pidx + 1);
        } else {
            if (p[pidx] == '?' || p[pidx] == s[sidx]) return backtracking(s, sidx + 1, p, pidx + 1);
            else return false;
        }
    }
};
*/

// solution 2: dp
/*
    设 f(i, j) 表示长度为i的s子串和长度为j的p子串是否匹配, 存在如下状态转移方程

        p[j-1] == '*'
            f(i, j) = f(i-1, j) || f(i, j-1)

        p[j-1] != '*
            f(i, j) = f(i-1, j-1)   if match is true;
            f(i, j) = false         if match is false;

        f(0, 0) = true;
        f(i, 0) = false; i > 0;

        match is true when p[j-1] == '?' || p[j-1] == s[i-1]
*/
class Solution {
public:
    bool isMatch(string s, string p) {
        int m = s.size(), n = p.size(), prev = 0, cur = 1;
        vector<vector<bool>> dp(2, vector<bool>(n+1, false));

        // i == 0
        dp[prev][0] = true;
        for (int j = 1; j <= n; ++j) dp[prev][j] = p[j-1]  == '*' ? dp[prev][j-1] : false;

        for (int i = 1; i <= m; ++i) {
            dp[cur][0] = false;
            for (int j = 1; j <= n; ++j) {
                if (p[j-1] == '*') dp[cur][j] = dp[prev][j] || dp[cur][j-1];
                else {
                    if (p[j-1] == '?' || p[j-1] == s[i-1]) dp[cur][j] = dp[prev][j-1];
                    else dp[cur][j] = false;
                }
            }
            swap(prev, cur);
        }
        return dp[prev].back();
    }
};



int main(int argc, char *argv[]) {

	return 0;
}
