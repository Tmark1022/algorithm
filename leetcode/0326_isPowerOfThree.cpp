/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Mon 26 Oct 2020 08:01:44 PM CST
 @ File Name	: 0326_isPowerOfThree.cpp
 @ Description	: 326. 3的幂 
 ************************************************************************/
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

class Solution {
public:

	/*
	// solution1: 暴力
	bool isPowerOfThree(int n) {
		if (n < 1) {
			return false;	
		}
		while (n % 3 == 0) {
			n /= 3;
		}
		return 1 == n;
	}
	*/

	// solution2 : 参考leetcode 2的幂， 将n转换为3进制数， 那么进制中有且仅有一位1
	// 但是转换数制较为麻烦， 还不如直接暴力
	


	// solution3 : 其实可以直接判断 log3(n) 是否为整数 来判断 n是否为3的幂 
	
	// solution 4 : 投机取巧方法， 同leetcode 2的幂
	bool isPowerOfThree(int n) {
		return n >= 1 && 1162261467 % n == 0; 
	}
};






int main(int argc, char *argv[]) {

	return 0;
}
