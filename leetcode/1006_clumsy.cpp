/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Thu 01 Apr 2021 10:12:35 AM CST
 @ File Name	: 1006_clumsy.cpp
 @ Description	: 1006. 笨阶乘 
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
	solution 1: 乘除除法立刻计算， 剩余加减法; 使用vector记录剩余的加减法数值; 最后剩余的加减法数值累起来即最终结果
	solution 2: 后缀表达式方式, 使用两个栈。 <O(N), O(N)>
	solution 3: 数学方式， 寻找规律， 进行消除。 <O(1), O(1)>
   */


/*
// solution 1:
class Solution {
public:
    int clumsy(int n) {
        vector<int> vec = {n--};
        for (int op = 0; n; --n, op = (op + 1) % 4) {
            if (0 == op) vec.back() *= n; 
            else if (1 == op) vec.back() /= n;
            else if (2 == op) vec.push_back(n);
            else vec.push_back(-n);
        }
        return accumulate(vec.begin(), vec.end(), 0);
    }
};


// solution 2:
class Solution {
public:
    int clumsy(int N) {
	vector<int> priority = {2, 2, 1, 1};
	int op = 0;
	stack<int> oper, nums; 	
	nums.push(N);
	for (int i = N-1; i >= 1; --i, ++op) {
		// 运算符	
		int opno = op % 4;	
		while (oper.size() && priority[opno] <= priority[oper.top()]) {
			DoOp(nums, oper.top());
			oper.pop();
		}
		oper.push(opno);

		// 操作数
		nums.push(i);
	}	
	// 剩余的运算符
	while (oper.size()) {
		DoOp(nums, oper.top());
		oper.pop();
	}	
	return nums.top();
    }

    void DoOp(stack<int> &nums, int opno) {
	    int operand = nums.top();
	    nums.pop();
	    switch(opno) {
		    case 0: nums.top() *= operand; break;
		    case 1: nums.top() /= operand; break;
		    case 2: nums.top() += operand; break;
		    case 3: nums.top() -= operand; break;
	    }	
    }
};
*/


// solution 3:
class Solution {
public:
    int clumsy(int N) {
	if (1 == N) return 1;	
	else if (2 == N) return 2;
	else if (3 == N) return 6;
	else if (4 == N) return 7; 
	else {
		if (0 == N % 4) return N+1;
		else if (3 == N % 4) return N-1;
		else  return N+2;
	}
    }
};





int main(int argc, char *argv[]) {

	return 0;
}
