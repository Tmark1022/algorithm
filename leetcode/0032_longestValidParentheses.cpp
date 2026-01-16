/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Wed 13 Jan 2021 07:34:10 PM CST
 @ File Name	: 0032_longestValidParentheses.cpp
 @ Description	: 32. 最长有效括号 
 ************************************************************************/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
#include <deque>
#include <unordered_map>
#include <unordered_set>
#include <stack>

using namespace std;


/* 
	solution 1: 暴力， 枚举连续子串的开始与结束下标, 判断子串合法性; 时间复杂度 O(N^3)

	solution 2: dp;
			设 g(i) 表示以下标为i的字符结尾的子串中，具有多少个空闲（待匹配）的 左括号'(', g(i) 最小值为0
				g(i)存在如下状态转移方程:
					if (s[i] == '(')	: g(i) = g(i-1) + 1;
					else			: g(i) = max(g(i-1) - 1, 0);

			该 g(i) 其实可以简化为一个变量open, 用于表示i （不包含i）之前还有多少个未被匹配的open parenthese 符号。

			
			设 f(i) 表示一下标为i的字符结尾的子串中最大的合法匹配子串的长度;
				f(i)存在如下状态转移方程:
					
					if (s[i] == ')' && open > 0)	: f(i) = 2 + f(i-1) + f(i - f(i-1) - 2) 
					else				: f(i) = 0			// 包括 s[i] == '(' 和 s[i] == ')' 但 open == 0 两种情况

			
			时间复杂度O(N), 空间复杂度O(N)


	solution 3: dp【Depreicated! 其实就是solution2】; 设 f(i) 表示一下标为i的字符结尾的子串中最大的合法匹配子串的长度; 分析 当前下标的字符的所有可能组合情况以及联系
			f(i) 存在如下状态转移方程:
				if (s[i] == '(')					: f(i) = 0
				
				当 if (s[i] == ')') 时:
					if (s[i-1] == '(')				: f(i) = f(i-2) + 2;
					if (s[i-1] == ')' && s[i-f(i-1)-1] == '(')	: f(i) = f(i-1) + 2 + f(i-f(i-1)-2)	
					else  即等价于(s[i-1] == ')' && s[i-f(i-1)-1] == ')')	: f(i) = 0

			时间复杂度O(N), 空间复杂度O(N)



	solution 4: 使用栈; 时间复杂度O(N), 空间复杂度O(N)

	solution 5: 正向逆向扫描结合; 时间复杂度O(N), 空间复杂度O(1)
*/

/*
// solution 1: brute force
class Solution {
public:
	bool IsValid(string &s, int b, int e) {
		int cnt = 0;		
		for (int i = b; i <= e; ++i) {
			if ('(' == s[i]) ++cnt;
			else --cnt;
			if (cnt < 0) break;
		}	
		return cnt == 0;
	}

    int longestValidParentheses(string s) {
	    int ans = 0;
	    for (int i = 0; i < s.size(); ++i) {
		    for (int j = i+1; j < s.size(); j += 2) {		// 奇数长度子串肯定不合法
			if (IsValid(s, i, j)) ans = max(ans, j-i+1); 
		    }	    
	    }	
	    return ans;
    }
};
*/

/*
// solution 2: dp
class Solution {
public:
    int longestValidParentheses(string s) {
        int open = 0, res = 0;           // 表示前边还有多少个未匹配的open parenthese
        vector<int>dp(s.size(), 0);

        for (int i = 0; i < s.size(); ++i) {
            if ('(' == s[i]) ++open;
            else {
                if (open) dp[i] = 2 + dp[i-1] + (i-dp[i-1]-2 >= 0 ? dp[i-dp[i-1]-2] : 0), res = max(res, dp[i]);
                open = max(open - 1, 0);
            }
        }
        return res;
    }
};


// solution 3: dp
class Solution {
public:
    int longestValidParentheses(string s) {
	    int len = s.size(), ans = 0;
	    if (!len) return ans;
	    vector<int> dp(len, 0);	 

	    for (int i = 1; i < len; ++i) {
		if (s[i] == '(') continue;
		if (s[i-1] == '(') dp[i] = (i >= 2 ? dp[i-2] : 0) + 2;
		else if (i-dp[i-1]-1 >= 0 && s[i-dp[i-1]-1] == '(') dp[i] = dp[i-1] + 2 + (i-dp[i-1]-2 >= 0 ? dp[i-dp[i-1]-2] : 0);
		ans = max(ans, dp[i]);
	    } 
	    return ans;
    }
};

// solution 4: stack
class Solution {
public:
    int longestValidParentheses(string s) {
	    int ans = 0;
	    stack<int> stk;
	    stk.push(-1);
	    for (int i = 0; i < s.size(); ++i) {
		    if (s[i] == '(') stk.push(i);
		    else {
			stk.pop();
			if (stk.empty()) stk.push(i);
			else ans = max(ans, i - stk.top());
		    }
	    }
	    return ans;
    }
};

*/

/*
// solution 5: 正逆向扫描结合
class Solution {
public:
    int longestValidParentheses(string s) {
	    int ans = 0, open = 0, close = 0, len = s.size();
	    if (!len) return ans;
	    for (int i = 0; i < len; ++i) {
		    if (s[i] == '(') ++open;
		    else {
			++close;
			if (close == open) ans = max(ans, close + open);
			else if (close > open) open = close = 0;
		    }
	    }
	    
	    open = close = 0;
	    for (int i = len - 1; i >= 0; --i) {
		    if (s[i] == '(') {
			++open;
			if (close == open) ans = max(ans, close + open);
			else if (close < open) open = close = 0;
		    }
		    else ++close;
	    }
	    return ans;
    }
};
*/


// solution 5: 正逆向扫描结合, 模版写法
class Solution {
public:
    int longestValidParentheses(string s) {
        int res = 0;
        res = max(res, help(s.begin(), s.end(), '('));
        res = max(res, help(s.rbegin(), s.rend(), ')'));
	return res;
    }

    template<class Iter, class Ch>
    int help(Iter b, Iter e, Ch flag) {
        int open = 0, close = 0, res = 0;
        for (Iter it = b; it != e; ++it) {
            if (flag == *it) ++open;
            else {
                ++close;
                if (open == close) res = max(res, open + close);
                else if (close > open) close = open = 0;
            }
        }
        return res;
    }
};





int main(int argc, char *argv[]) {

	return 0;
}
