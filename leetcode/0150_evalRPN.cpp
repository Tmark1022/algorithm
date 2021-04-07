/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Wed 07 Apr 2021 09:30:23 AM CST
 @ File Name	: 0150_evalRPN.cpp
 @ Description	: 150. 逆波兰表达式求值 
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
#include <functional>

using namespace std;


/*
	solution 1: 常规后缀表达式求值方式， 使用栈; <O(N), O(N)>
   */


// solution 1:
class Solution {
public:
    int evalRPN(vector<string>& tokens) {
	unordered_map<string, function<int (int, int)>> op = {
	    {"+", [](int a, int b){return a + b;}},
	    {"-", [](int a, int b){return a - b;}},
	    {"*", [](int a, int b){return a * b;}},
	    {"/", [](int a, int b){return a / b;}},
	};
	stack<int> stk;
	for (auto & elem : tokens) {
		if (op.count(elem)) {
			int operand = stk.top();
			stk.pop();
			stk.top() = op[elem](stk.top(), operand);
		} else {
			stk.push(std::stoi(elem));
		}
	}	
	return stk.top();
    }
};





int main(int argc, char *argv[]) {

	return 0;
}
