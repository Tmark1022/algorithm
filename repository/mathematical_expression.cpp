/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Thu 01 Apr 2021 04:06:57 PM CST
 @ File Name	: mathematical_expression.cpp
 @ Description	: 算术表达式相关代码 
 ************************************************************************/
#include <cstdlib>
#include <iostream>
#include <stdexcept>
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

// 清除expr里的所有空格字符
string StripSpace(const string &expr) {
	string ans;
	for (auto &e : expr) {
		if (e == ' ') continue;
		ans += e;
	} 
	return ans;
} 

// 从后往前提取元素， expr不能不包含空格
string ExtractElem(const string &expr, int &idx) {
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

// 分解表达式， 提取每一个部分, 保存在一个vector中返回
vector<string> SplitExpression(const string &expr) {
	string expr_strip = StripSpace(expr);
	vector<string> ans;
	if (expr_strip.size() <= 0) return ans;
	for (int i = expr_strip.size() - 1; i >= 0;){
		string elem = ExtractElem(expr_strip, i);
		if (elem.size() <= 0) continue;
		ans.push_back(elem);
	}

	std::reverse(ans.begin(), ans.end());
	return ans;
}  

/***************************************************
* 前缀表达式 polish notation 
***************************************************/
class PolishNotation {
public:	
	static vector<string> Transform(const string &expr) {
		// 去掉空格
		string expr_strip = StripSpace(expr);
		if (expr_strip.size() <= 0) return {};
		vector<string> ans;
		stack<string> op;
	
		// 从后往前提取
		for (int i = expr_strip.size() - 1; i >= 0;) {
			string elem = ExtractElem(expr_strip, i);
			if (elem.size() <= 0) continue;

			if (IsOperator(elem.back())) {
				// 运算符
				// 按优先级出栈运算符	
				while (!op.empty() && IsOperator(op.top().back()) && GetOperatorPriority(elem.back()) < GetOperatorPriority(op.top().back())) {
					ans.push_back(op.top());
					op.pop();
				}	
				op.push(elem);
			} else if (IsOpenParenthesis(elem.back())) {
				// 左括号
				// 出栈所有遇到的运算符， 直到遇到第一个close parenthesis	
				while (!op.empty() && !IsCloseParenthesis(op.top().back())) {
					ans.push_back(op.top());	
					op.pop();
				}
				if (!op.empty()) op.pop();			// 出栈 close parenthesis
			} else if (IsCloseParenthesis(elem.back())) {
				// 右括号
				op.push(elem);			// 直接加入到运算符栈中			
			}  else if (IsDigit(elem.back())) {
				// 数值
				ans.push_back(elem);		// 直接加入结果中	
			}	
		}

		// operator stack 所有元素出栈
		while (!op.empty()) {
			ans.push_back(op.top());
			op.pop();
		}

		// 翻转结果集	
		std::reverse(ans.begin(), ans.end());
		return ans;
	}
	
	static int CalcPN(const vector<string> &pn) {
		if (pn.size() <= 0) return 0;	
		stack<int> stk;
		for (auto it = pn.crbegin(); it != pn.crend(); ++it) {	
			if (IsOperator(it->back())) {
				// 运算符
				int operand1 = stk.top();    
				stk.pop();
				switch(it->back()) {
					case '+': stk.top() = operand1 + stk.top(); break;
					case '-': stk.top() = operand1 - stk.top(); break;
					case '*': stk.top() = operand1 * stk.top(); break;
					case '/': stk.top() = operand1 / stk.top(); break;
					case '%': stk.top() = operand1 % stk.top(); break;
					default : cout << "invalid operator" << endl; exit(EXIT_FAILURE);
				}	
			}  else if (IsDigit(it->back())) {
				// 数值
				stk.push(std::stoi(*it));
			}	
		}
		return stk.top();
	}
};

/***************************************************
* 后缀表达式 reverse polish notation 
***************************************************/
class ReversePolishNotation {
public:
	static vector<string> Transform(const string &expr) {
		// 去掉空格
		vector<string> elem_list = SplitExpression(expr), ans;
		stack<string> op;
	
		for (auto &elem : elem_list) {
			if (IsOperator(elem.back())) {
				// 运算符
				// 按优先级出栈运算符 (这里的运算符栈 priority 要大于 栈顶才能入栈， 而前缀表达式却是 大于等于)	
				while (!op.empty() && IsOperator(op.top().back()) && GetOperatorPriority(elem.back()) <= GetOperatorPriority(op.top().back())) {
					ans.push_back(op.top());
					op.pop();
				}	
				op.push(elem);
			} else if (IsOpenParenthesis(elem.back())) {
				// 左括号
				op.push(elem);			// 直接加入到运算符栈中		
			} else if (IsCloseParenthesis(elem.back())) {
				// 右括号
				// 出栈所有遇到的运算符， 直到遇到第一个open parenthesis		
				while (!op.empty() && !IsOpenParenthesis(op.top().back())) {
					ans.push_back(op.top());	
					op.pop();
				}
				if (!op.empty()) op.pop();			// 出栈 open parenthesis
			}  else if (IsDigit(elem.back())) {
				// 数值
				ans.push_back(elem);		// 直接加入结果中	
			}	
		}

		// operator stack 所有元素出栈
		while (!op.empty()) {
			ans.push_back(op.top());
			op.pop();
		}

		return ans;
	}
	
	static int CalcRPN(const vector<string> &rpn) {
		if (rpn.size() <= 0) return 0;	
		stack<int> stk;
		for (auto it = rpn.cbegin(); it != rpn.cend(); ++it) {	
			if (IsOperator(it->back())) {
				// 运算符
				int operand1 = stk.top();    
				stk.pop();
				switch(it->back()) {
					case '+': stk.top() = stk.top() + operand1; break;
					case '-': stk.top() = stk.top() - operand1; break;
					case '*': stk.top() = stk.top() * operand1; break;
					case '/': stk.top() = stk.top() / operand1; break;
					case '%': stk.top() = stk.top() % operand1; break;
					default : cout << "invalid operator" << endl; exit(EXIT_FAILURE);
				}	
			}  else if (IsDigit(it->back())) {
				// 数值
				stk.push(std::stoi(*it));
			}	
		}
		return stk.top();
	}
	
};

/***************************************************
* 表达式树 expression tree  
***************************************************/
class ExpressionTree {
public:
	struct ETNode {
		string elem;	
		ETNode *left, *right;
		ETNode(const string &s, ETNode *l = nullptr, ETNode *r = nullptr):elem(s), left(l), right(r) {}
	};
	ETNode *root;	

	ExpressionTree(const string &expr) {
		vector<string> rpn = ReversePolishNotation::Transform(expr);
		this->root = BuildTree(rpn);
	}

	~ExpressionTree() {
		if (!root) return ;		
		FreeTree(root);
	}

	void FreeTree(ETNode *cur) {
		if (!cur) return ;
		FreeTree(cur->left);
		FreeTree(cur->right);
		delete(cur);
	}

	ETNode *BuildTree(const vector<string> &rpn) {
		if (rpn.size() <= 0) return nullptr;	
		stack<ETNode *> stk;

		for (auto it = rpn.cbegin(); it != rpn.cend(); ++it) {	
			if (IsOperator(it->back())) {
				// 运算符
				ETNode *pr = stk.top();    
				stk.pop();
				ETNode *pl = stk.top();    
				stk.pop();
				stk.push(new ETNode(*it, pl, pr));
			}  else if (IsDigit(it->back())) {
				// 数值
				stk.push(new ETNode(*it));
			}	
		}
		return stk.top();
	}

	void PreOrder(ETNode *cur, string &ans) {
		if (!cur) return ;
		ans += cur->elem;
		ans += " ";
		PreOrder(cur->left, ans);
		PreOrder(cur->right, ans);
	} 

	void InOrder(ETNode *cur, string &ans) {
		if (!cur) return ;
		if (cur->left) ans += "( ";	
		InOrder(cur->left, ans);
		ans += cur->elem;
		ans += " ";
		InOrder(cur->right, ans);
		if (cur->left) ans += ") ";	
	}

	void PostOrder(ETNode *cur, string &ans) {
		if (!cur) return ;
		PostOrder(cur->left, ans);
		PostOrder(cur->right, ans);
		ans += cur->elem;
		ans += " ";
	}
};

/***************************************************
* test 
***************************************************/
void TestEntry() {
	string expr;
	while (getline(cin, expr)) {

		// 字符串提取测试
		/*
		expr = StripSpace(expr);
		cout << "expr : " << expr << endl;
		if (expr.size() <= 0) continue;

		for (int idx = expr.size() - 1; idx >= 0;) {
			string elem = ExtractElem(expr, idx);
			cout << (elem.size() ? elem : " ") << ",";
		}	
		cout << endl;
		*/

		/*
		// 前缀表达式
		vector<string> pn = PolishNotation::Transform(expr);
		std::for_each(pn.begin(), pn.end(), [](const string &str){cout << str << ", ";});
		cout << endl;

		int res = PolishNotation::CalcPN(pn);
		cout << "res is : " << res << endl;
		*/

		/*
		// 后缀表达式
		vector<string> rpn = ReversePolishNotation::Transform(expr);
		std::for_each(rpn.begin(), rpn.end(), [](const string &str){cout << str << ", ";});
		cout << endl;
		int res = ReversePolishNotation::CalcRPN(rpn);
		cout << "res is : " << res << endl;
		*/

		// 表达式树
		ExpressionTree tree(expr);
		string instr, prestr, poststr;
		tree.InOrder(tree.root, instr);
		tree.PreOrder(tree.root, prestr);
		tree.PostOrder(tree.root, poststr);
		cout << "InOrder : " << instr << endl;;
		cout << "PreOrder : " << prestr << endl;;
		cout << "PostOrder : " << poststr << endl;;

	}
}

int main(int argc, char *argv[]) {
	TestEntry();
	return 0;
}
