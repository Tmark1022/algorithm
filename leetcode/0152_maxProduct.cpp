/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Wed 30 Dec 2020 09:11:27 AM CST
 @ File Name	: 0152_maxProduct.cpp
 @ Description	: 152. 乘积最大子数组 
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
	solution 1:暴力, 枚举连续子序列的开始与结束位置
	solution 2: dp, 因为数值有正有负, 当当前数值为负数时， 最大值其实是与最小值相乘产生的
			假设 fmax(n) 代表以n结尾的子序列的乘积最大值， fmin(n)代表以n结尾的子序列的乘积最小值。
			状态转移方程为: 
				fmax(n) = max{n, fmax(n-1) * n, fmin(n-1)*n};
				fmin(n) = min{n, fmax(n-1) * n, fmin(n-1)*n};
   */


/*
// solution 1: 暴力 
class Solution {
public:
    int maxProduct(vector<int>& nums) {
	if (!nums.size()) return 0;			
	int ans = INT_MIN;
	for (int i = 0; i < nums.size(); ++i) {
		for (int j = i, tmp = 1; j < nums.size(); ++j) {
			tmp *= nums[j];	
			ans = max(tmp, ans);	
		}
	}	
	return ans;
    }
};
*/

// solution 2: dp
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        if (!nums.size()) return 0;
        int fmax = nums[0], fmin = nums[0], ans = fmax;
        for (int i = 1; i < nums.size(); ++i) {
                if (nums[i] < 0) swap(fmax, fmin);
                fmax = max(nums[i], fmax * nums[i]);
                fmin = min(nums[i], fmin * nums[i]);;
                ans = max(fmax, ans);
        }
        return ans;
    }
};

int main(int argc, char *argv[]) {

	return 0;
}
