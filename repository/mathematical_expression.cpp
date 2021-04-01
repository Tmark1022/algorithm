/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Thu 01 Apr 2021 04:06:57 PM CST
 @ File Name	: mathematical_expression.cpp
 @ Description	: 算术表达式相关代码 
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
	涉及内容:
		1. 前缀表达式 
			1) 中缀表达式 转为 前缀表达式
			2) 前缀表达式求值 
			
		2. 后缀表达式
			1) 中缀表达式 转为 后缀表达式
			2) 后缀表达式求值 

		3. 表达式树
			1) 构造表达式树 (类似后缀表达式求值过程)
			2) 表达式树的前序/中序/后序遍历
	
	前提:	
		提供的中缀表达式总是合法的 （该算法中不做合法性检查）
		中缀表达式允许存在空格（这里当做没有任何作用, 开始提取前， 先去掉所有空格）
	
	支持operator:
		优先级1	: '+' | '-'
		优先级2 : '*' | '/' | '%'

		仅支持32位整型数值
		允许一目运算符 + 和 -, 这里将一目运算符当做是操作数的一部分
   */


/***************************************************
* 辅助函数 
***************************************************/
unordered_map<char, int> oper_priority = {
	{'+', 1}, {'-', 1},
	{'*', 2}, {'/', 2}, {'%', 2},
};

int GetOperatorPriority(char oper) {
	return oper_priority.at(oper);
}

bool IsOperator(char ch) {
	return oper_priority.count(ch);
}

bool IsDigit(char ch) {
	return '0' <= ch && ch <= '9';
}

bool IsOpenParenthesis(char ch) {
	return '(' == ch; 
}

bool IsCloseParenthesis(char ch) {
	return ')' == ch; 
}

string StripSpace(const string &expr) {
	string ans;
	for (auto &e : expr) {
		if (e == ' ') continue;
		ans += e;
	} 
	return ans;
} 

/***************************************************
* 前缀表达式 polish notation 
***************************************************/
class PolishNotation {
public:	
	// 提取元素， 不包含空格
	static string ExtractElem(const string &expr, int &idx) {
		string elem;
		if (IsDigit(expr[idx])) {
			// 提取数字
			while (idx >= 0 && IsDigit(expr[idx])) elem += expr[idx--];	
			
			// 是否包含一目运算符 + 或 -
			if (expr[idx] == '+' || expr[idx] == '-') {
				if (idx == 0 || (IsOperator(expr[idx - 1]) || IsOpenParenthesis(expr[idx-1]))) elem += expr[idx--];
			}
		} else if (IsOperator(expr[idx])||IsOpenParenthesis(expr[idx])||IsOpenParenthesis(expr[idx])||IsCloseParenthesis(expr[idx])) {
			// 其他合法字符
			elem += expr[idx--];
		} else {
			// 不合法字符，直接跳过
			--idx;	
		}
		reverse(elem.begin(), elem.end());
		return elem;
	} 

	static vector<string> Transform(const string &expr) {
		// 去掉空格
		string expr_strip = StripSpace(expr);
		if (expr_strip.size() <= 0) return {};
		vector<string> ans;
		stack<string> op;
	
		// 从后往前提取
		for (int i = expr_strip.size() - 1; i >= 0;) {
			



		}
		
		std::reverse(ans.begin(), ans.end());
		return ans;
	}
	


	static int CalcPN(const vector<string> &pn) {
		return 0;
	}
};

/***************************************************
* 后缀表达式 reverse polish notation 
***************************************************/
class ReversePolishNotation {
	

};

/***************************************************
* 表达式树 expression tree  
***************************************************/
class ExpressionTree {


};


/***************************************************
* test 
***************************************************/
void TestEntry() {
	string expr;
	while (getline(cin, expr)) {
		expr = StripSpace(expr);
		cout << "expr : " << expr << endl;
		if (expr.size() <= 0) continue;
		for (int idx = expr.size() - 1; idx >= 0;) {
			string elem = PolishNotation::ExtractElem(expr, idx);
			cout << (elem.size() ? elem : " ") << ",";
		}	
		cout << endl;
	}

}

int main(int argc, char *argv[]) {
	TestEntry();
	return 0;
}
