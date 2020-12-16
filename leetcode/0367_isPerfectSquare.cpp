/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Wed 16 Dec 2020 08:08:07 PM CST
 @ File Name	: 0367_isPerfectSquare.cpp
 @ Description	: 367. 有效的完全平方数
 ************************************************************************/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
#include <deque>
#include <unordered_map>
#include <unordered_set>

using namespace std;

// solution 1: 暴力，遍历每一个数， 直到 x^2 >= num 


/*
// solution 2: 二分法
class Solution {
public:
    bool isPerfectSquare(int num) {
	int l = 0, h = num;
	while (l <= h) {
		long mid = l + (h - l) / 2;
		long square = mid * mid;		
		if (square == num) return true;
		else if (square < num) l = mid + 1; 
		else h = mid - 1;
	}
	return false;
    }
};
*/

// solution 3: 牛顿迭代法, 参考leetcode 69
class Solution {
public:
    bool isPerfectSquare(int num) {
        long r = num;
        while (r*r > num) {
                r = (r + num/r)>>1;
        }
        return r*r == num;
    }
};


int main(int argc, char *argv[]) {

	return 0;
}
