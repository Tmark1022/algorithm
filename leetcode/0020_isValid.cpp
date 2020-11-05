/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Thu 05 Nov 2020 09:09:23 PM CST
 @ File Name	: 0020_isValid.cpp
 @ Description	: 20. 有效的括号
 ************************************************************************/
#include <iostream>
#include <unordered_map>
#include <stack>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::stack;

class Solution {
public:
	// solution 1 : 暴力， 每次replace 最内层的括号并替换为'\0'
	// solution 2 : 使用栈 
    bool isValid(string s) {
	stack<char> stk;
	for (auto ch : s) {
		if (ch == '(') stk.push(')');
		else if (ch == '[') stk.push(']');
		else if (ch == '{') stk.push('}');
		else {
			if (stk.empty() || stk.top() != ch) return false;
			else stk.pop();
		}
	}
	return stk.empty();
    }
};


int main(int argc, char *argv[]) {

	return 0;
}
