/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Fri 06 Dec 2024 07:26:46 PM CST
 @ File Name	: 1979_findGCD.cpp
 @ Description	: 1979. 找出数组的最大公约数
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
// solution 1: 暴力, 找最大最小数 O(N), 暴力法求两数的最大公约数 O(M) 【假设两数中的小数为M】
//		故time complexity O(N + M), space complexity O(1)
class Solution {
public:
    int findGCD(vector<int>& nums) {
	    int minIdx = 0, maxIdx = 0;
	    for (int i = 1; i < nums.size(); ++i) {
		    if (nums[i] < nums[minIdx]) minIdx = i;
		    if (nums[i] > nums[maxIdx]) maxIdx = i;
	    }
	    return gcd(nums[maxIdx], nums[minIdx]);
    }

    int gcd(int m, int n) {
	    for (int i = n; i >= 1; --i) {
		    if (0 == m % i && 0 == n % i) return i;
	    }
	    return 0;
    }
};
*/


// solution 2: 欧几里得算法求最大公约数, 找最大最小数 O(N), 欧几里得求两数的最大公约数 O(logM) 【假设两数中的大数为M】
//		故time complexity 为 O(N + logM), space complexity 为 O(1)
//
//		欧几里得算法：
//			gcd(m, n) = gcd(n, m mod n);
//		
//		note:	
//			1) terminator 为 n == 0, 因为0能被任何数整除, 故0 和 任何数x 的最大公约数都为 x
//			2) m % n 的值肯定是小于 m / 2的 (其中m 大于 n); 故时间复杂度为对数级
//				证明： 当 n <= m/2 时， 取模的结果一定是小于 m / 2
//				       当 n > m/2 时， m / n 的除数为1， 余数也是小于 m / 2 
//
//
class Solution {
public:
    int findGCD(vector<int>& nums) {
	    int minIdx = 0, maxIdx = 0;
	    for (int i = 1; i < nums.size(); ++i) {
		    if (nums[i] < nums[minIdx]) minIdx = i;
		    if (nums[i] > nums[maxIdx]) maxIdx = i;
	    }
	    return gcd(nums[maxIdx], nums[minIdx]);
    }

    int gcd(int m, int n) {
	    if (!n) return m;
	    return gcd(n, m % n);
    }
};




int main(int argc, char *argv[]) {

	return 0;
}
