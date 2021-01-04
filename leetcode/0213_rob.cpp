/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Mon 04 Jan 2021 02:23:55 PM CST
 @ File Name	: 0213_rob.cpp
 @ Description	: 213. 打家劫舍 II
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
	solution 1: 因为数组是环状的， 相对于leetcode 198, 该题目中第一个元素和最后一个元素不能同时选择
		    那么对于首尾元素的选择问题就有如下几种情况: 
			1) 首元素和尾元素都不选择, RobHelp(nums, 1, len - 2)
			2) 选择首元素， 不选择尾元素, nums[0] + RobHelp(nums, 2, len-2)
			3) 选择尾元素， 不选择首元素, RobHelp(nums, 1, len-3) + nums[len-1]
	
			于是， 可以将三种情况分别计算处理， 最终结果为三者中的最大值

	solution 2: 可以将solution1 中的三种情况简化为如下两种情况:
			1) 不选首元素， 尾元素选择或不选, RobHelp(nums, 1, len-1)
			2) 不选尾元素， 首元素选择或不选, RobHelp(nums, 0, len-2)

			于是， 可以将两种情况分别计算处理， 最终结果为两者中的最大值	
   */

/*
// solution 1:
class Solution {
public:
	// leetcode 198 解题方式
	int RobHelp(vector<int>& nums, int b, int e) {
		int prev = 0, cur = 0;
		for (int i = b; i <= e; ++i) {
			int tmp = max(cur, prev + nums[i]);	
			prev = cur;
			cur = tmp;
		}
		return cur;
	}
	
    int rob(vector<int>& nums) {
	int len = nums.size();
	if (1 == len) return nums[0];			// nums.size() >= 1
	return max(max(RobHelp(nums, 1, len - 2), nums[0] + RobHelp(nums, 2, len-2)), RobHelp(nums, 1, len-3) + nums[len-1]); 	
    }
};
*/

// solution 2:
class Solution {
public:
	// leetcode 198 解题方式
	int RobHelp(vector<int>& nums, int b, int e) {
		int prev = 0, cur = 0;
		for (int i = b; i <= e; ++i) {
			int tmp = max(cur, prev + nums[i]);	
			prev = cur;
			cur = tmp;
		}
		return cur;
	}
	
    int rob(vector<int>& nums) {
	int len = nums.size();
	if (len == 1) return nums[0];
	return max(RobHelp(nums, 1, len - 1), RobHelp(nums, 0, len - 2));	
    }
};




int main(int argc, char *argv[]) {

	return 0;
}
