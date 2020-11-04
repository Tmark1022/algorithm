/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Wed 04 Nov 2020 12:57:44 PM CST
 @ File Name	: 0050_myPow.cpp
 @ Description	: 50. Pow(x, n) 
 ************************************************************************/
#include <iostream>

using std::cin;
using std::cout;
using std::endl;




class Solution {
public:

	/*
	// solution 1： 暴力, 需要注意有符号整型-n溢出问题, 使用unsigned 防止溢出问题, long long 类型提升，防止溢出
	// time complexity : O(N)
	// space complexity : O(1)
	double MyPowCore(double x, unsigned int n) {
		double res = 1.0;	
		for (int i = 1; i <= n; ++i) {
			res *= x;
		}
		return res;
	}
	*/

	/*
	// solution 2：递归快速幂算法，  
	//  如果|N| 偶数， f(x, n) =  f(x*x, n/2)
	//  如果|N| 是奇数， f(x, n) = f(x*x, n/2) * x
	// time complexity : O(logn)
	// space complexity : O(logn), 也就是递归的次数
	double MyPowCore(double x, unsigned int n) {
		if (0 == n) {
			return 1.0;
		}
		
		if (n & 1) return MyPowCore(x * x, n >> 1) * x;	
		else return MyPowCore(x*x, n>>1); 
	}
	*/

	// solution 3：迭代快速幂算法
	// 
	// 将指数N 转化为2进制看， 如 x ^ 11  ==> x^(00001011)  ==> x^(00001000) * x^(00000010) * x^(00000001)
	//
	// time complexity : O(logn)
	// space complexity : O(1)
	double MyPowCore(double x, unsigned int n) {
		double res = 1.0, tmp = x;
		while (n) {
			if (n & 1) {
				// 当前二进制位为1
				res *= tmp;
			}	
			tmp *= tmp;	// 计算x ^ (000... 1 ...0) 次方
			n >>= 1;
		}

		return res;
	}

    double myPow(double x, int n) {
	    // long long 类型提升， 防止溢出
	long long n2 = n;

	// MyPowCore 为计算非负整数的幂
	return n < 0 ? 1.0/ MyPowCore(x, -n2) : MyPowCore(x, n); 	
    }
};

int main(int argc, char *argv[]) {
	Solution obj;
	cout << obj.myPow(2.0, 10) << endl;
	return 0;
}
