/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Thu 21 Jan 2021 02:33:45 PM CST
 @ File Name	: 0005_longestPalindrome.cpp
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
	需要注意： 字符串子串是连续的， 不像子集
	与leetcode 647 题目一样
	
	solution 1: brute force; 枚举子串左右边界, 然后判断子串是否为回文子串; 时间O(N^3), 空间O(1)

	solution 2: 中心拓展; 枚举子串中心， 然后同时左右拓展; 需要注意区分奇数长度子串的中心和偶数长度子串的中心; 时间O(N^2), 空间O(1)

	solution 3: dp;	设f(i, j) 表示s[i:j] 子串是否为回文子串，存在如下状态转移方程:
			f[i,j] = s[i] == s[j] && (j - i < 2 || f(i+1, j-1))		// 其中i <= j 

			时间 O(N^2), 空间O(N^2)

			空间优化： 因为j 状态只与 j-1 有关， 可以使用滚动数组来进行空间优化; 时间O(N^2), 空间O(1)
			
	solution 4: manacher 算法【线性时间复杂度求最大长度子串问题】;
			核心思想: 相对于朴素的中心拓展算法， 加入dp数值记录之前计算的子串中心的回文子串长度， 利用对称性， 加速后续子串中心的拓展长度进程
			解题步骤:
				1) 插入占位符(使所有回文子串长度都是奇数的, 统一中心点)
				2) 初始化dp数值值 
				3) 中心拓展计算dp值

			这里dp[i]记录的是以坐标i为中心的子串的最长回文子串半径;
			需要辅助变量 rm (表示以计算到回文串的最右端点下标), im (rm 对应的回文串的下标)

			时间复杂度O(N), 空间复杂度O(N)
   */


/*
// soluton 1: brute force 
class Solution {
public:
	bool IsPalindrome(string &s, int b, int e) {
		for (int l = b, r = e; l < r; ++l, --r) {
			if (s[l] != s[r]) return false; 
		}
		return true;
	}
    string longestPalindrome(string s) {
	    int pos = 0, max_len = 1, len = s.size();
	    for (int i = 0; i < len; ++i) {
		    for (int j = len - 1; j-i >= max_len; --j) {			// 做一个max_len的剪枝
			if (IsPalindrome(s, i, j)) pos = i, max_len = j - i + 1;
		    }
	    }				
	    return s.substr(pos, max_len);
    }
};

// soluton 2: 中心拓展   
class Solution {
public:
    string longestPalindrome(string s) {
	    int pos = 0, max_len = 1, len = s.size();
	    for (int i = 0; i < len; ++i) {
		    for (int j = 0; j <= 1; ++j) {
			int l = i, r = i+j; 		
			while (l >= 0 && r < len && s[l] == s[r]) --l, ++r;
			if (r-l-1 > max_len) max_len = r-l-1, pos = l+1;
		    }	
	    }				
	    return s.substr(pos, max_len);
    }
};

// soluton 3: dp; f[i,j] = s[i] == s[j] && (j - i < 2 || f(i+1, j-1))		// 其中i <= j 
class Solution {
public:
    string longestPalindrome(string s) {
	    int pos = 0, max_len = 1, len = s.size();
	    vector<bool> dp(len, false);	 
	    for (int j = 0; j < len; ++j) {
		    for (int i = 0; i <= j; ++i) {
			dp[i] = s[i] == s[j] && (j - i < 2 || dp[i+1]); 	
			if (dp[i] && j-i+1 > max_len) pos = i, max_len = j-i+1;
		    }
	    }
	    return s.substr(pos, max_len);
    }
};
*/

// solution 4: manacher 算法【线性时间复杂度求最大长度子串问题】;
		// 为了避免判断边界问题， 可以在首尾插入原字符串中不可能存在的字符当作哨兵;
class Solution {
public:
    string longestPalindrome(string s) {
	    // step 1: 插入占位符， 构造新的字符串
	    string str = "?#";
	    for (auto &e : s) {
		// str = str + e + "#";		// 注意区分 =  和 += 这种写法很慢， N^2时间复杂度
		str += e;
		str += "#";
	    }
	    str += "!";

	    int pos = 1, max_len = 3, len = str.size(), rm = 0, im = 0;
	    vector<int> dp(len, 0);
	    for (int i = 1; i < len - 1; ++i) {
		// step 2: 初始化dp[i]
		dp[i] = i >= rm ? 1 : min(dp[2*im-i], rm - i + 1); 
		// step 3: 拓展dp[i]
		while (str[i-dp[i]] == str[i+dp[i]]) ++dp[i];
		if (i + dp[i] - 1 > rm) rm = i + dp[i] - 1, im = i;	
		// 记录最长回文子串
		if (2*dp[i]-1 > max_len) max_len = 2*dp[i]-1, pos = i - (dp[i] - 1);				
	    }
		
	    // 构造返回值
	    string ans;
	    for (int i = pos; i < pos + max_len; ++i) {
		   if (str[i] != '#') ans += str[i]; 
	    }
	    return ans;
    }
};


int main(int argc, char *argv[]) {

	return 0;
}
