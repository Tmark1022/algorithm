/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Wed 25 Nov 2020 11:51:11 AM CST
 @ File Name	: 0026_removeDuplicates.cpp
 @ Description	: 26. 删除排序数组中的重复项 
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

// solution 1: 双指针
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
	if (!nums.size()) return 0;
	int p = 0;
	for (int i = 1; i < nums.size(); ++i) {
		if (nums[i] == nums[p]) continue;
		nums[++p] = nums[i]; 
	}
	return p+1;
    }
};


int main(int argc, char *argv[]) {

	return 0;
}
