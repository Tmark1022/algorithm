/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Mon 12 Apr 2021 10:44:23 AM CST
 @ File Name	: 0227_calculate.cpp
 @ Description	: 227. 基本计算器 II 
 ************************************************************************/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
#include <deque>
#include <unordered_map>
#include <unordered_set>
#include <numeric>
#include <stack>

using namespace std;


/*
Note:
	1) 1 <= s.length <= 3 * 105
	2) s 由整数和算符 ('+', '-', '*', '/') 组成，中间由一些空格隔开
	3) s 表示一个 有效表达式
	4) 表达式中的所有整数都是非负整数，且在范围 [0, 231 - 1] 内, 题目数据保证答案是一个 32-bit 整数

solution 1: 单栈; 参考leetcode 1006 笨阶乘， 表达式内只有+ - * /, 且没有括号, 可以遇到* 或 / 就马上计算， 其他运算符就将操作数处理入栈，
			最后再累加栈中剩余的操作数。<O(N), O(N)>

solution 2: 双栈, 阉割版前缀表达式(波兰式), 这里不用考虑操作数为 -100 等的情况， 所以-(a+b) 的情况【表达式转换成0 - (a+b)】也不用处理了

solution 3: 双栈, 阉割版后缀表达式 (逆波兰式), 这里不用考虑操作数为 -100 等的情况， 所以-(a+b) 的情况【表达式转换成0 - (a+b)】也不用处理了
*/

/*
// solution 1: 单栈（其使用vector模拟即可）
class Solution {
public:	
	bool IsDigit(char ch) { return '0' <= ch && ch <= '9';}
    int calculate(string s) {
	vector<int> stk;		
	char pre_sign = '+';
	for (int i = 0; i < s.size(); ++i) {
		if (IsDigit(s[i])) {
			int nums = 0;	
			while (i < s.size() && IsDigit(s[i])) nums = nums * 10 + (s[i++] - '0');
			--i;
			switch (pre_sign) {
				case '+': stk.push_back(nums); break;
				case '-': stk.push_back(-nums); break;
				case '*': stk.back() *= nums; break;
				case '/': stk.back() /= nums; break;
			}
		} else if (' ' == s[i]) continue; 
		else pre_sign = s[i];	
	}
	return std::accumulate(stk.begin(), stk.end(), 0);
    }
};
*/


/***************************************************
* 求波兰式/逆波兰式的一些辅助 
***************************************************/
unordered_map<char, int> priority = {
	{'+', 1},	
	{'-', 1},	
	{'*', 2},	
	{'/', 2},	
};

bool IsDigit(char ch) { 
	return '0' <= ch && ch <= '9';
}

bool IsOperator(char ch) { 
	return '+' == ch || '-' == ch || '*' == ch || '/' == ch; 
}


/*
// solution 2: 波兰式
class Solution {
public:	
	string ExtractElem(const string &s, int &idx) {
		string ans;
		if (IsDigit(s[idx])) {
			while (idx >= 0 && IsDigit(s[idx])) ans += s[idx--];
			std::reverse(ans.begin(), ans.end());
		} else if (IsOperator(s[idx])) {
			ans += s[idx--];
		} else {
			// others, ie. space	
			--idx;
		}	
		return ans;
	}

	void EvalPN(stack<int> &nums, char sign) {
		int operand = nums.top();	
		nums.pop();
		switch(sign) {
			case '+': nums.top() = operand + nums.top(); break;  
			case '-': nums.top() = operand - nums.top(); break;  
			case '*': nums.top() = operand * nums.top(); break;  
			case '/': nums.top() = operand / nums.top(); break;  
		}
	}

    int calculate(string s) {
	stack<char> op;	
	stack<int> nums;
	for (int idx = s.size() - 1; idx >= 0; ) {
		string elem = ExtractElem(s, idx);
		if (!elem.size()) continue;			// 空格
		if (IsDigit(elem.back())) nums.push(stoi(elem));
		else if (IsOperator(elem.back())) {
			while(op.size() && priority.at(elem.back()) < priority.at(op.top())) {
				EvalPN(nums, op.top());
				op.pop();
			} 	
			op.push(elem.back());
		} 
	}	
	while (op.size()) {
		EvalPN(nums, op.top());
		op.pop();
	}	
	return nums.top();
    }
};
*/

// solution 3: 逆波兰式
class Solution {
public:	
	string ExtractElem(const string &s, int &idx) {
		string ans;
		if (IsDigit(s[idx])) {
			while (idx < s.size() && IsDigit(s[idx])) ans += s[idx++];
		} else if (IsOperator(s[idx])) {
			ans += s[idx++];
		} else {
			// others, ie. space	
			++idx;
		}	
		return ans;
	}

	void EvalRPN(stack<int> &nums, char sign) {
		int operand = nums.top();	
		nums.pop();
		switch(sign) {
			case '+': nums.top() += operand; break;  
			case '-': nums.top() -= operand; break;  
			case '*': nums.top() *= operand; break;  
			case '/': nums.top() /= operand; break;  
		}
	}

    int calculate(string s) {
	stack<char> op;	
	stack<int> nums;
	for (int idx = 0; idx < s.size(); ) {
		string elem = ExtractElem(s, idx);
		if (!elem.size()) continue;			// 空格
		if (IsDigit(elem.back())) nums.push(stoi(elem));
		else if (IsOperator(elem.back())) {
			while(op.size() && priority.at(elem.back()) <= priority.at(op.top())) {
				EvalRPN(nums, op.top());
				op.pop();
			} 	
			op.push(elem.back());
		} 
	}	
	while (op.size()) {
		EvalRPN(nums, op.top());
		op.pop();
	}	
	return nums.top();
    }
};






int main(int argc, char *argv[]) {

	return 0;
}
