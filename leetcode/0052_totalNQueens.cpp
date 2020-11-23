/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Mon 23 Nov 2020 03:27:36 PM CST
 @ File Name	: 0052_totalNQueens.cpp
 @ Description	: 
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
// solutin 1:  与leetcode 51一样， 就是这里只用count
class Solution {
public:
    int  BackTracking(int row, int n, long long col, long long diagonal1, long long diagonal2) {
        if (row == n) {
            return 1;
        }

        int count = 0;
        long long available_pos = ((1<<n) - 1) & ~(col | diagonal1 | diagonal2);
        while (available_pos) {
            long long pos_val = available_pos & (-available_pos);
            int pos = __builtin_ctz(pos_val);
            count += BackTracking(row+1, n, col | pos_val, (diagonal1 | pos_val) << 1, (diagonal2 | pos_val) >> 1);
            available_pos &= available_pos - 1;
        }
        return count;
    }

    int totalNQueens(int n) {
        if (n <= 0) return 0;
        return BackTracking(0, n, 0, 0, 0);
    }
};
*/


//solution 2: 在solutin 1的基础上， 使用栈来模拟递归 
class Solution {
public:	
	struct Status {
		int row;
		long long col, xy_diff, xy_sum;
		Status(int a, long long b, long long c, long long d): row(a), col(b), xy_diff(c), xy_sum(d) {}
	};

    int totalNQueens(int n) {
        if (n <= 0) return 0;
	int count = 0;
	stack<Status> stk;
	stk.push(Status(0, 0, 0, 0));

	while (!stk.empty()) {
		Status cur = stk.top();	
		stk.pop();	

		// terminator
		if (cur.row == n) {
			count += 1;
			continue;
		}

		// push all child status into stack
		long long valid_position = ((1 << n) - 1) & ~(cur.col | cur.xy_diff | cur.xy_sum); // 所有可行的位
		while (valid_position) {
			long long pos_val = valid_position & (-valid_position); 	
			int pos = __builtin_ctz(pos_val);					
			stk.push(Status(cur.row +1, cur.col|pos_val, (cur.xy_diff|pos_val) >> 1, (cur.xy_sum|pos_val) << 1)); 
			valid_position &= valid_position - 1;
		}
	}	
	return count;
    }
};



int main(int argc, char *argv[]) {

	return 0;
}
