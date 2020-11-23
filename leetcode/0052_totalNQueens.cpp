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

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;

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



int main(int argc, char *argv[]) {

	return 0;
}
