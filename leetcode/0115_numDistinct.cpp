/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Mon 18 May 2026 11:36:56 AM CST
 @ File Name	: 0115_numDistinct.cpp
 @ Description	: 115. 不同的子序列
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
	solution 1: brute force; backtracking 枚举子序列， 并且提前pruning; O(2^n)
	solution 1.1: brute force; solution 1 反过来遍历的实现 
	solution 2: dp, 参考solution 1.1 的实现， 可得状态转移方程。
			设 f(i, j) 表示s前i个字符子串 中出现 t的前j个字符子串 的子序列的次数 

			f(i, j) = f(i-1, j-1) + f(i-1, j); if (s[i] == s[j])
			f(i, j) = f(i-1, j);	if (s[i] != s[j])	

			其中	i == 0, f(i, j) = 0;
				j == 0, f(i, j) = 1;

   */

/*
// solution 1:
class Solution {
public:
    int numDistinct(string s, string t) {
	    int res = 0;
	    backtracking(0, s, 0, t, res);
	    return res;
    }

    void backtracking(int si, string &s, int ti, string &t, int &res) {
	    if (ti == t.size()) {
		    ++res;
		    return ;
	    }

	    if (si == s.size() || s.size() - si < t.size() - ti) return ;

	    // 不选
	    backtracking(si + 1, s, ti, t, res); 

	    // 选择
	    if (s[si] == t[ti]) backtracking(si+1, s, ti + 1, t, res);
    }
};
*/

/*
// solution 1.1:
class Solution {
public:
    int numDistinct(string s, string t) {
	    int res = 0;
	    backtracking(s.size() - 1, s, t.size() - 1, t, res);
	    return res;
    }

    void backtracking(int si, string &s, int ti, string &t, int &res) {
	    if (ti < 0) {
		    ++res;
		    return ;
	    }

	    if (si < 0 || si < ti) return ;

	    // 不选
	    backtracking(si-1, s, ti, t, res); 

	    // 选择
	    if (s[si] == t[ti]) backtracking(si-1, s, ti-1, t, res);
    }
};
*/

/*
	solution 2: dp, 参考solution 1.1 的实现， 可得状态转移方程。
			设 f(i, j) 表示s前i个字符子串 中出现 t的前j个字符子串 的子序列的次数 

			f(i, j) = f(i-1, j-1) + f(i-1, j); if (s[i] == s[j])
			f(i, j) = f(i-1, j);	if (s[i] != s[j])	

			其中	i == 0, f(i, j) = 0;
				j == 0, f(i, j) = 1;
*/

// solution 2: dp
class Solution {
public:
    int numDistinct(string s, string t) {
        int m = s.size(), n = t.size();
	// unsigned long long 避免有些测试用例溢出
        vector<unsigned long long> dp(n+1, 0);
        dp[0] = 1;
        for (int i = 1; i <= m; ++i) {
            for (int j = n; j > 0; --j) {
                if (s[i-1] != t[j-1]) continue;
                dp[j] += dp[j-1];
            }
        }
        return dp.back();
    }
};

int main(int argc, char *argv[]) {
	Solution obj;
	cout << obj.numDistinct("rabbbit", "rabbit") << endl;
	cout << obj.numDistinct("babgbag", "bag") << endl;

	return 0;
}
