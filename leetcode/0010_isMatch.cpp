/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Fri 05 Jun 2026 04:03:25 PM CST
 @ File Name	: 0010_isMatch.cpp
 @ Description	: 10. 正则表达式匹配 
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
        bool match = sidx < s.size() && (p[pidx] == '.' || s[sidx] == p[pidx]); 
        if (pidx + 1 < p.size() && p[pidx + 1] == '*') {
            if (match) return  backtracking(s, sidx + 1, p, pidx) || backtracking(s, sidx, p, pidx + 2);
            else return backtracking(s, sidx, p, pidx + 2);
        } else {
            if (match) return backtracking(s, sidx + 1, p, pidx + 1);
            else return false;
        }
    }
};
*/

/*
// soution 1: brute force，反向遍历， 跟符合后续dp思维
class Solution {
public:
    bool isMatch(string s, string p) {
        return backtracking(s, s.size() - 1, p, p.size() - 1);
    }

    bool backtracking(string &s, int sidx, string &p, int pidx) {
        if (pidx < 0) return sidx < 0;

        if (p[pidx] == '*') {
            char ch = p[pidx-1];
            if (sidx >= 0 && (ch == '.' || ch == s[sidx]))
                return backtracking(s, sidx-1, p, pidx) || backtracking(s, sidx, p, pidx-2);
            else return backtracking(s, sidx, p, pidx-2);
        } else {
            if (sidx >= 0 && (p[pidx] == '.' || p[pidx] == s[sidx]))
                return backtracking(s, sidx-1, p, pidx - 1);
            else return false;
        }
    }
};
*/

// solution 2: dp; 设f(i, j) 表示s前i个字符子串 和 p前j个字符子串 是否匹配。
//                  根据solution 1的解法可以得出状态转移方程:
/*
            match 表示字符是否匹配， 例如'.'和任意字符匹配， 否则的话 s[i] == p[j] 表示匹配。
            p[j] == '*':
                if match is true : f(i,j) = f(i-1, j) || f(i, j-2)
                else             : f(i,j) = f(i, j-2)

            p[j] != '*'
                if match is true : f(i,j) = f(i-1, j-1)
                else             : f(i,j) = false
*/
class Solution {
public:
    bool isMatch(string s, string p) {
        int m = s.size(), n = p.size(), prev = 0, cur = 1, match;
        vector<vector<bool>> dp(2, vector<bool>(n+1,false));

        // i == 0 状态初始化
        dp[prev][0] = true;
        for (int j = 1; j <= n; ++j) {
            if (p[j-1] == '*') dp[prev][j] = dp[prev][j-2];
        }

        for (int i = 1; i <= m; ++i) {
            dp[cur][0] = false;
            for (int j = 1; j <= n; ++j) {
                if (p[j-1] == '*') {
                    match = p[j-2] == '.' || s[i-1] == p[j-2];
                    dp[cur][j] = match ? (dp[prev][j] || dp[cur][j-2]) : dp[cur][j-2];
                } else {
                    match = p[j-1] == '.' || s[i-1] == p[j-1];
                    dp[cur][j] = match ? dp[prev][j-1] : false;
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
