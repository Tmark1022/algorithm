/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Sat 24 Oct 2020 11:16:47 PM CST
 @ File Name	: common_divisor_common_mutiple.cpp
 @ Description	: 求a, b 的最大公约数 和 最小公倍数
 ************************************************************************/
#include <iostream>

using std::cin;
using std::cout;
using std::endl;


class Solution {
public : 
	Solution(unsigned param1, unsigned param2) {
		param1_ = param1;	
		param2_ = param2;	
	}


	// 求最大公约数， 欧几里得算法
	unsigned GetCommonDivisor() {
		unsigned m = param1_;		
		unsigned n = param2_;

		unsigned rem;
		while (n) {
			rem = m % n;
			m = n;
			n = rem;
		}

		return m;
	}


	// a,b的最大公约数为p, 最小公倍数为q, 有公式 ab = pq
	unsigned GetCommonMutiple() {
		// 先求出最大公约数
		
		unsigned common_divisor = GetCommonDivisor();

		// return param1_ * param2_ / common_divisor;
		return param1_ * (param2_ / common_divisor);	// 减少溢出风险， 可以先除公约数， 在乘
	}

private:
	unsigned param1_;
	unsigned param2_;
};


int main(int argc, char *argv[]) {
	int a, b;	
	while (cin >> a >>b) {
		Solution obj(a,b);
		cout << "common divisor : " << obj.GetCommonDivisor() << endl; 
		cout << "common multiple: " << obj.GetCommonMutiple() << endl; 
	}

	return 0;
}
