/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Fri 13 Nov 2020 03:30:10 PM CST
 @ File Name	: 0022_generateParenthesis.cpp
 @ Description	: 22. 括号生成 
 ************************************************************************/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stack>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::stack;

/*
solution 1: 暴力， "()" 全排列， 然后判断合法性
solution 2: 回溯 + 剪枝, 
solution 3: 用栈实现solution2的递归 , 栈记录递归每一层的状态
solution 4: 动态规划 【迭代】, 递推公式(不是很明白推导过程): dp[i] = (dp[a])dp[b];
solution 5: 动态规划 【递归】, 原理同上
*/

/*
class Solution {
public:
	// 重复全排列
	void GenerateAllArrangement(int level, int max_level, string &str, vector<string> &ans) {
		// terminator	
		if (level == max_level) {
			if (IsValid(str)) ans.push_back(str);
			return ;
		}	
		
		// open	 parenthese
		str[level] = '(';
		GenerateAllArrangement(level+1, max_level, str, ans);

		// close parenthese
		str[level] = ')';
		GenerateAllArrangement(level+1, max_level, str, ans);
	}
	
	bool IsValid(string &str) {
		int open = 0;	
		for (auto &ch : str) {
			if ('(' == ch) ++open;
			else if (--open < 0) return false;
		}
		return 0 == open;
	}

	// solution 1
    vector<string> generateParenthesis(int n) {
	// 异常条件
	if (n <= 0) {
		return {};
	}

	if (1 == n) {
		return {"()"};
	}
	
	string str(2*n, '\0');	
	vector<string> ans;
	GenerateAllArrangement(0, 2*n, str, ans);	
	return ans; 
    }

};
*/


/*
// solution 2
class Solution {
public:
	void Helper(int open, int close, int n, string &str, vector<string> &ans) {
		// terminator
		if (open == n && close == n) {
			ans.push_back(str);
			return ;
		}

		// open parenthese
		if (open < n) {
			str[open+close] = '(';
			Helper(open + 1, close, n, str, ans);
		} 

		// close parenthese
		if (close < open) {
			str[open+close] = ')';
			Helper(open, close+1, n, str, ans);
		} 	
	}
	
    vector<string> generateParenthesis(int n) {
	// 异常条件
	if (n <= 0) {
		return {};
	}

	if (1 == n) {
		return {"()"};
	}
	
	string str(2*n, '\0');	
	vector<string> ans;
	Helper(0, 0, n, str, ans);	
	return ans; 
    }
};
*/

/*
// solution 3
class Solution {
public:	
	struct Node{
		int open;	
		int close;
		string str;	// 这里要保存当时状态

		Node(int a = 0, int b = 0, string str = ""):open(a), close(b), str(str){}
	};

    vector<string> generateParenthesis(int n) {
	// 异常条件
	if (n <= 0) {
		return {};
	}
	if (1 == n) {
		return {"()"};
	}
	
	vector<string> ans;
	stack<Node> stk;
	stk.emplace();		// 插入初始默认值, 即开始状态
	while(!stk.empty()) {
		Node node = stk.top();		
		stk.pop();

		// terminator
		if (node.open == n && node.close == n) {
			cout << node.str << endl;
			ans.push_back(node.str);
			continue;
		}			
		// 原来函数调用的反向顺序入栈
		// close parenthese	
		if (node.close < node.open) stk.push({node.open, node.close + 1, node.str + ")"});	

		// open parenthese	
		if (node.open < n) stk.push({node.open + 1, node.close, node.str + "("});	
	}
	return ans; 
    }

};
*/

/*
// solution 4: 动态规划 【迭代】, 递推公式(不是很明白推导过程): dp[i] = (dp[a])dp[b];
class Solution {
public:	
    vector<string> generateParenthesis(int n) {
	// 异常条件
	if (n <= 0) {
		return {};
	}
	if (1 == n) {
		return {"()"};
	}
	
	vector<vector<string>> dp(n+1);
	dp[0] = {""};
	dp[1] = {"()"};
	
	// 枚举所有可能的a 和 b
	for (int i = 2; i <= n; ++i) {
		for (int a = 0; a < i; ++a) {
			int b = i - 1 - a;
			for (string &stra : dp[a]) 
				for(string &strb : dp[b]) {
					dp[i].push_back("(" + stra + ")" + strb);
				}
		}
	}		

	return dp[n];
    }
};
*/

// solution 5: solution 4 递归解法
class Solution {
public:	
	const vector<string>& Generate(int n, vector<vector<string>> &dp) {		
		if (!dp[n].empty()) {
			return dp[n];
		}

		for (int a = 0; a < n; ++a) {
			const vector<string> &veca = Generate(a, dp);
			const vector<string> &vecb = Generate(n-1-a, dp);
			for (const string &stra : veca) 
				for(const string &strb : vecb) {
					dp[n].push_back("(" + stra + ")" + strb);
				}
		}
		return dp[n];
	}

    vector<string> generateParenthesis(int n) {
	// 异常条件
	if (n <= 0) {
		return {};
	}	
	vector<vector<string>> dp(n+1);
	dp[0] = {""};
	dp[1] = {"()"};
	return Generate(n, dp);
    }
};

int main(int argc, char *argv[]) {
	Solution obj;
	obj.generateParenthesis(3);

	return 0;
}
