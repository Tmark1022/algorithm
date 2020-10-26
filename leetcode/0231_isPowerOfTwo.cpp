/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Mon 26 Oct 2020 07:24:32 PM CST
 @ File Name	: 0231_isPowerOfTwo.cpp
 @ Description	: 231. 2的幂 
 ************************************************************************/
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

class Solution {
public:
	

	/*
	// 发现tmp * 2 的方式会有溢出可能, 在leetcode 中过不了
	// solution1: 暴力, 时间复杂度 log(n)
	bool isPowerOfTwo(int n) {
		int tmp = 1;	
		while (tmp <= n) {
			if (tmp == n) {
				return true;
			}

			tmp *= 2;
		}
		return false;
   	}
	*/

	/*
	// solution1: 暴力, 时间复杂度 log(n)
	bool isPowerOfTwo(int n) {
		// tmp * 2 的方式会有溢出可能, 那么就反过来除n，能够一直被整除， 知道最后只剩下1
	
		if (n < 1) {
			return false;
		}

		while (0 == n%2) {
			n /= 2;			
		}
		return n == 1;
   	}
	*/

	/*
	// solution2: 投机方法，如果一个n是2的幂， 那么n的质因数全是2;
	// 可知int 为32位, 那么int内最大的2的幂为 log2(INT_MAX), 这个值其实就是0x40000000 
	// 如果n是2的幂， 那么n 一定能整除0x40000000【包含2的0次方1】
	// 如果n不是2的幂， 那么肯定拥有非2质因子， 那么肯定不能整除0X40000000
	bool isPowerOfTwo(int n) {
		return n >= 1 && (0x40000000 % n) == 0;	
   	}
	*/

	/*
	// solution3: 从二进制位上着手， 可以发现如果n是2的幂， 那么n的二进制位有且仅有一位是1 【在这里要排除最高位是1的情况, 负数】  
	// 可以使用 x & (x - 1) 来统计1位数的方式来完成判断
	bool isPowerOfTwo(int n) {
		// 只有一位1, 所以去掉最右位1后， 值肯定就是0
		return n >= 1 && (n & (n - 1)) == 0;
   	}
	*/

	// solution4: 从二进制位上着手， 可以发现如果n是2的幂， 那么n的二进制位有且仅有一位是1 【在这里要排除最高位是1的情况, 负数】  
	// 可以使用 x & (-x) 来提取最右位1的值来判断， 
	bool isPowerOfTwo(int n) {
		// 只有一位1, 所以提取最右位1后， 值肯定等于自身
		return n >= 1 && (n & (-n)) == n;
   	}
};

int main(int argc, char *argv[]) {

	return 0;
}
