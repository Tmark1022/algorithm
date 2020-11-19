/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Thu 19 Nov 2020 11:58:18 AM CST
 @ File Name	: 0031_nextPermutation.cpp
 @ Description	: 31. 下一个排列
 ************************************************************************/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;

class Solution {
public:
    void nextPermutation(vector<int>& nums) {
	int len = nums.size();			
	
	// 找到第一个小的数
	int i = len - 2;  
	while (i >= 0 && nums[i] >= nums[i+1]) --i;

	if (i < 0) {
		std::reverse(nums.begin(), nums.end());	
	} else {
		int k = len-1;	
		while(nums[k] <= nums[i]) --k;		
		std::swap(nums[k], nums[i]);
		std::reverse(nums.begin() + i + 1, nums.end());	
	}
    }
};

int main(int argc, char *argv[]) {

	return 0;
}
