/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Wed 17 Mar 2021 05:57:24 PM CST
 @ File Name	: 0338_countBits.cpp
 @ Description	: 338. 比特位计数 
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

/*
	solution 1: 常规解法, n & (n-1) 计算单个数的比特位; 对于每一个数， 时间复杂度为k, k为该数的1比特位数
			时间复杂度 O(N*k), 空间复杂度O(1)
	solution 2: 模仿__builtin_popcount函数的实现(类似分治思想), 计算单个数的比特位; 对于每一个数， 时间复杂度为O(logm), m 为数值的总位数， 如int为32位, log(32) == 5
			时间复杂度 O(N*logm), 空间复杂度O(1)
	
	solution 3: dp 1; 从最高1比特位角度思考， 设dp[i] 为数值为i的1比特位数目, highest_bit 为当前值为i时， 对饮最高的比特位值; 
			存在状态转移方程: dp[i] = dp[i-highest_bit] + 1;
			时间复杂度 O(N), 空间复杂度O(N)【将dp数值当做是返回值返回， 可以当做空间复杂度为O(1)】

	solution 4: dp 2; 从最低比特位思考， 设dp[i] 为数值为i的1比特位数目;
			存在状态转移方程: dp[i] = dp[(i >> 1)] - (i&1);
			时间复杂度 O(N), 空间复杂度O(N)【将dp数值当做是返回值返回， 可以当做空间复杂度为O(1)】

	solution 5: dp 3; 从最低1比特位思考【注意solution 4 是最低比特位】， 设dp[i] 为数值为i的1比特位数目;
			存在状态转移方程: dp[i] = dp[i & (i-1)] + 1;
			时间复杂度 O(N), 空间复杂度O(N)【将dp数值当做是返回值返回， 可以当做空间复杂度为O(1)】

   */

/*
// solution 1:
class Solution {
public:
	int help(int n) {
		int ans = 0;
		while (n) {
			n &= n-1;	
			++ans;
		}
		return ans;	
	}

    vector<int> countBits(int num) {
	    vector<int> ans(num+1, 0);
	    for (int i = 1; i <= num; ++i) {
		ans[i] = help(i);		
	    }
	    return ans;
    }
};

// solution 2:
class Solution {
public:
	int help(int n) {	
		// 假定 int 为32个字节
		n = ((n >> 1) & 0x55555555) + (n & 0x55555555); 
		n = ((n >> 2) & 0x33333333) + (n & 0x33333333); 
		n = ((n >> 4) & 0x0f0f0f0f) + (n & 0x0f0f0f0f); 
		n = ((n >> 8) & 0x00ff00ff) + (n & 0x00ff00ff); 
		n = ((n >> 16) & 0x0000ffff) + (n & 0x0000ffff); 
		return n;
	}

    vector<int> countBits(int num) {
	    vector<int> ans(num+1, 0);
	    for (int i = 1; i <= num; ++i) {
		ans[i] = help(i);		
	    }
	    return ans;
    }
};

// solution 3:
class Solution {
public:
    vector<int> countBits(int num) {
	    vector<int> dp(num+1, 0);
	    int highest_bit = 0;
	    for (int i = 1; i <= num; ++i) {
		if ((i & (i-1)) == 0) highest_bit = i; 
		dp[i] = dp[i - highest_bit] + 1;	
	    }
	    return dp;
    }
};

// solution 4:
class Solution {
public:
    vector<int> countBits(int num) {
	    vector<int> dp(num+1, 0);
	    for (int i = 1; i <= num; ++i) {
		dp[i] = dp[i >> 1] + (i&1);	
	    }
	    return dp;
    }
};
*/

// solution 5:
class Solution {
public:
    vector<int> countBits(int num) {
	    vector<int> dp(num+1, 0);
	    for (int i = 1; i <= num; ++i) {
		dp[i] = dp[i & (i-1)] + 1;	
	    }
	    return dp;
    }
};

int main(int argc, char *argv[]) {

	return 0;
}
