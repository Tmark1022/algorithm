/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Tue 12 Jan 2021 07:39:25 PM CST
 @ File Name	: 0091_numDecodings.cpp
 @ Description	: 91. 解码方法 
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
	solution 1: 回溯搜索, 每次要么解析一个字符， 要么解析两个字符(如果能够解析的话) 对于'0' 特殊处理

	solution 2: dp, 设dp[i] 表示 s[0...i] 字符串的 解码方法
			对于'0' 特殊处理
				
			存在如下状态转移方程:
				if (s[i] == 0)【只能解码两个字符】	dp[i] = dp[i-2];
				只能解码一个字符			dp[i] = dp[i-1];
				既能解码一个字符， 又能解码两个字符	dp[i] = dp[i-1] + dp[i-2];

			使用滚动变量进行优化
   */


/*
// solution 1: 回溯搜索
class Solution {
public:
	int ans = 0; 
	void BackTracking(string &s, int idx) {
		if (idx == s.size()) {
			++ans;
			return ;
		}	
		if ('0' == s[idx]) return ;	

		// 解析一个字符 【对于10, 20 情况， 解析一个字符并不合法， 不过会在下一个调用中因为0开头而终止， 所以结果还是正确的】
		BackTracking(s, idx+1);

		// 解析两个字符
		if (s.size() - idx >= 2 && std::stoi(s.substr(idx, 2)) <= 26) BackTracking(s, idx+2); 
	}

    int numDecodings(string s) {
	BackTracking(s, 0);
	return ans;	
    }
};
*/

/*
// solution 2: dp
//			存在如下状态转移方程:
//				if (s[i] == 0)【只能解码两个字符】	dp[i] = dp[i-2];
//				只能解码一个字符			dp[i] = dp[i-1];
//				既能解码一个字符， 又能解码两个字符	dp[i] = dp[i-1] + dp[i-2];
class Solution {
public:
    int numDecodings(string s) {
	if (s[0] == '0') return 0;
	int cur = 1, prev = 1, pprev = 1;
	for (int i = 1; i < s.size(); ++i) {
		if ('0' == s[i]) {
			// 异常情况
			if (s[i-1] != '1' && s[i-1] != '2') return 0;	
			// 只能两个一起解析
			cur = pprev;	
		} else if ('0' != s[i-1] && std::stoi(s.substr(i-1, 2)) <= 26) cur = prev + pprev;
		else cur = prev;			// 只能一个解析

		pprev = prev;
		prev = cur;
	}		
	return prev;
    }
};
*/


// solution 2: dp;  f(i) = f(i-1) + f(i-2), tc O(N), sc O(1)
//	当 s[i] != '0' 时， 能用一个字符进行解码
//	当 i > 0 && (s[i-1] == '1' || (s[i-1] == '2' && s[i] <= '6')) 时， 能用两个字符进行解码
class Solution {
public:
    int numDecodings(string s) {
        int dp = 1, dp1 = 1, dp2 = 1;
        for (int i = 0; i < s.size() && dp; ++i) {		// dp 为0 提前结束循环
            dp = 0;
            if (s[i] != '0') dp += dp1; 
            if (i > 0 && (s[i-1] == '1' || (s[i-1] == '2' && s[i] <= '6'))) dp += dp2;
            dp2 = dp1, dp1 = dp; 
        }
        return dp;
    }
};


int main(int argc, char *argv[]) {

	return 0;
}
