/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Thu 08 Apr 2021 11:05:13 AM CST
 @ File Name	: 0224_calculate.cpp
 @ Description	: 224. 基本计算器  
 ************************************************************************/
#include <exception>
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
	solution 1: 前缀表达式（波兰式）, 双栈 
	solution 2: 后缀表达式（逆波兰式）, 双栈; 考虑到操作数可能存在如 -100 和 +18 等情况，所以需要先从后往前提取所有elem出来 
	
	solution 3: 单栈, 使用栈保存;因为表达式中只存在 +/- 法，即 a-(b-c)  其实可以去掉括号转变成 a - b + c 的从左到右运算。
			【官方解法有bug, 只能处理 第一个operand是是负数的情况, 如 1 - -1 的情况确实不能解决】
   */


/*
// solution 1: 波兰式
class Solution {
public:
        bool IsDigit(const char &ch) {return '0' <= ch && ch <= '9';}
	bool IsOperator(const char &ch) {return '-' == ch || '+' == ch;}
	string ExtractElem(const string &expr, int &idx) {
		string elem;		
		if (IsDigit(expr[idx])) {
			while (idx >= 0 && IsDigit(expr[idx])) elem += expr[idx--];
			if (idx >= 0 && IsOperator(expr[idx])) {	// 操作数是否包含一元运算符 +/-
				if (0 == idx || '(' == expr[idx-1] || IsOperator(expr[idx-1])) elem += expr[idx--];
			}
			std::reverse(elem.begin(), elem.end());	
		} else {
			elem += expr[idx--];
		}
		return elem;
	}

	void DoOp(stack<int> &num, char op) {
		int operand = num.top();	
		num.pop();
		switch(op) {
			case '+': num.top() = operand + num.top(); break;
			case '-': num.top() = operand - num.top(); break;
		}
	}

    int calculate(string s) {
	unordered_map<char, int> priority = {
	    {'+', 1},
	    {'-', 1},
	};
        stack<int> num;
	stack<char> op;

	// 去掉空格
        string expr;
        for (auto &e : s) {
                if (e != ' ') expr += e;
        }
	if (expr.size() <= 0) return 0;

	// 增加操作数0 应对 -(10 + 20) 等情况
	if (expr[0] == '+' || expr[0] == '-') expr = "0" + expr;

	// 考虑到存在如 +100等操作数, 需要从后往前提取elem
	for (int idx = expr.size() - 1; idx >= 0;) {
		string elem = ExtractElem(expr, idx);
		if (IsDigit(elem.back())) num.push(stoi(elem));
		else if (IsOperator(elem.back())) {
			while (op.size() && IsOperator(op.top()) && priority.at(elem.back()) < priority[op.top()]) {
				DoOp(num, op.top());
				op.pop();
			}
			op.push(elem.back());
		} else if ('(' == elem.back()) {
			while (op.size() && op.top() != ')') {
				DoOp(num, op.top());
				op.pop();	
			}
			if (op.size()) op.pop();			// 出栈')'
		} else if (')' == elem.back()) op.push(elem.back()); 	
	}

	// 处理op栈中剩下的运算符
	while (op.size()) {
		DoOp(num, op.top());
		op.pop();		
	}

	return num.top();
    }
};
*/

// solution 2: 逆波兰式
class Solution {
public:
        bool IsDigit(const char &ch) {return '0' <= ch && ch <= '9';}
	bool IsOperator(const char &ch) {return '-' == ch || '+' == ch;}
	// 提取单个elem
	string ExtractElem(const string &expr, int &idx) {
		string elem;		
		if (IsDigit(expr[idx])) {
			while (idx >= 0 && IsDigit(expr[idx])) elem += expr[idx--];
			if (idx >= 0 && IsOperator(expr[idx])) {	// 操作数是否包含一元运算符 +/-
				if (0 == idx || '(' == expr[idx-1] || IsOperator(expr[idx-1])) elem += expr[idx--];
			}
			std::reverse(elem.begin(), elem.end());	
		} else {
			elem += expr[idx--];
		}
		return elem;
	}
	
	// 反向提取所有elem
	vector<string> ExtractAllElem(const string &expr) {
		vector<string> ans;
		for (int idx = expr.size() - 1; idx >= 0;) ans.push_back(ExtractElem(expr, idx));
		return ans;
	}	

	void DoOp(stack<int> &num, char op) {
		int operand = num.top();	
		num.pop();
		switch(op) {
			case '+': num.top() = num.top() + operand; break;
			case '-': num.top() = num.top() - operand; break;
		}
	}

    int calculate(string s) {
	unordered_map<char, int> priority = {
	    {'+', 1},
	    {'-', 1},
	};
        stack<int> num;
	stack<char> op;

	// 去掉空格
        string expr;
        for (auto &e : s) {
                if (e != ' ') expr += e;
        }
	if (expr.size() <= 0) return 0;

	// 增加操作数0 应对 -(10 + 20) 等情况
	if (expr[0] == '+' || expr[0] == '-') expr = "0" + expr;
	
	vector<string> elem_list = ExtractAllElem(expr);
	for (auto it = elem_list.crbegin(); it != elem_list.crend(); ++it) {	
		if (IsDigit(it->back())) num.push(stoi(*it));
		else if (IsOperator(it->back())) {
			while (op.size() && IsOperator(op.top()) && priority.at(it->back()) <= priority[op.top()]) { //注意后缀表达式这里使用<= 
				DoOp(num, op.top());
				op.pop();
			}
			op.push(it->back());

		} else if (')' == it->back()) {
			while (op.size() && op.top() != '(') {
				DoOp(num, op.top());
				op.pop();	
			}
			if (op.size()) op.pop();			// 出栈'('
		} else if ('(' == it->back()) op.push(it->back()); 	
	}

	// 处理op栈中剩下的运算符
	while (op.size()) {
		DoOp(num, op.top());
		op.pop();		
	}

	return num.top();
    }
};






/*
// solution 3: 单栈
class Solution {
public:
	bool IsDigit(const char &ch) {
		return '0' <= ch && ch <= '9';
	}

    int calculate(string s) {
	stack<int> op; 
	op.push(1);
	int ans = 0, sign = op.top();		// sign 默认符号
	for (int idx = 0; idx < s.size(); ++idx) {
		if (IsDigit(s[idx])) {
			int num = 0;
			while (idx < s.size() && IsDigit(s[idx])) num = 10 * num + (s[idx++] - '0');
			--idx;			// for loop 已经存在自增
			ans += sign * num;	
			sign = op.top();	// reset default sign
		} else if ('(' == s[idx]) {
			op.push(sign);		// 新的默认符号入栈
		} else if (')' == s[idx]) {
			op.pop();
			sign = op.top();	// reset default sign
		} else if ('-' == s[idx]) {
			sign = -sign;		// flip sign
		}	
	}
	return ans;
    }
};
*/




int main(int argc, char *argv[]) {

	return 0;
}
