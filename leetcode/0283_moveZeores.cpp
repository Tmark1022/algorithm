/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Mon 02 Nov 2020 10:07:23 AM CST
 @ File Name	: 0283_moveZeores.cpp
 @ Description	: 
 ************************************************************************/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
	// solution 1: 暴力
	
	// solution 2: 使用辅助数组


	/*
	// solution 3: 双指针
    void moveZeroes(vector<int>& nums) {
        int len = nums.size();
        int pos = 0;			// pos前的都是非0值
        for (int i = 0; i < len; ++i) {
            if (nums[i]) {
                nums[pos++] = nums[i];
            }
        }
        while (pos < len) {
            nums[pos++] = 0;
        }
    }
    */

	// 双指针优化版， 一个循环
    void moveZeroes(vector<int>& nums) {
        int len = nums.size();
        for (int i = 0, j = 0; i < len; ++i) {
            if (nums[i]) {
		if (i != j) {
			// swap, 这种情况下j下标的值一定是0, 所以swap可以简化为赋值0
			nums[j] = nums[i];
			nums[i] = 0;
		}
		++j;
            }
        }
    }

};

int main(int argc, char *argv[]) {

	return 0;
}
