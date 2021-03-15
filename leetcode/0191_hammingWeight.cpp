/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Mon 15 Mar 2021 11:22:03 AM CST
 @ File Name	: 0191_hammingWeight.cpp
 @ Description	: 191. 位1的个数 
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
// solution 1: 直观，循环32遍计算bit 为1的个数
class Solution {
public:
    int hammingWeight(uint32_t n) {
	int ans = 0;	
	uint32_t mask = 1;
	for (int i = 1; i <= 32; ++i) {	
		(n & mask) && ++ans; 
		mask <<= 1;
	}	
	return ans;
    }
};
*/

// solution 2: n & (n-1) 计算二进制位数 
class Solution {
public:
    int hammingWeight(uint32_t n) {
	int ans = 0;	
	while (n) {	
		n &= n-1;
		++ans;
	}
	return ans;
    }
};

int main(int argc, char *argv[]) {

	return 0;
}
