/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Wed 04 Nov 2020 09:31:48 PM CST
 @ File Name	: 0070_climbStairs.cpp
 @ Description	: 70. 爬楼梯 

该问题其实就是斐波那契数列问题， 所以用于求解斐波那契数列的问题都能用于解决该问题

 ************************************************************************/
#include <iostream>
#include <cmath>

using namespace std;

class Solution {
public:
	/*
	// solution 1: dp, f(n) = f(n-1) + f(n-2)
	// 因为n 只与 n-1 和 n-2 有关， 所以不需要一整个数组， 只需要两个辅助变量即可
    int climbStairs(int n) {
	if (1 == n) return 1;	
	if (2 == n) return 2;

	int i = 3, tmp_1 = 1, tmp_2 = 2, res;
	while (i++ <= n) {
		res = tmp_1 + tmp_2;		
		tmp_1 = tmp_2;
		tmp_2 = res;
	}	

	return res;
    }
    */
	
	// solution 2: 数列通项公式 	
	// 需要注意的是这里比 斐波那契数列提前了一项。
    int climbStairs(int n) {	
	return (1.0 / std::sqrt(5)) * (std::pow((1 + std::sqrt(5)) / 2, n+1) - std::pow((1 - std::sqrt(5)) / 2, n+1));
    }

};


int main(int argc, char *argv[]) {

	return 0;
}
