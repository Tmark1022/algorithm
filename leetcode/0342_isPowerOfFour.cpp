/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Mon 26 Oct 2020 08:11:55 PM CST
 @ File Name	: 0342_isPowerOfFour.cpp
 @ Description	: 342. 4的幂
 ************************************************************************/
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

class Solution {
public:
	/*
	// solution 1: 暴力 
	bool isPowerOfFour(int num) {
		if (num < 1) {
			return false;
		}
		while (num %4 == 0) {
			num /= 4;
		}
		return num == 1;
	}
	*/

	// solution 2: 直接求log4(num) 的值是否为整数
	

	// solution 3: 观察二进制位， 4 = 2的平方, 4的幂 其实就是2 的偶数幂， 二进制中只有一个1位并且是偶数位值
	// 判断只有一个1可以使用leetcode 2的幂判断方法， 判断是1是在偶数位置中， 只需要与 0x55555555 &运算不为0即可 	
	bool isPowerOfFour(int num) {
		if (num < 1) {
			return false;
		}
		return (num & (num-1)) == 0 && (num & 0x55555555);
	}
	
};






int main(int argc, char *argv[]) {

	return 0;
}
