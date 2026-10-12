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
using namespace std;

/*
// 朴素写法
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
*/


// solution 1:
/*
    step 1: 找idx
    step 2: 二分找比nums[idx]大的最小值， 并swap。
    step 3: reverse; 因为step找的是比nums[idx]大的最小值， 所以swap后， idx ~ len-1 还是有序的
*/
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int len = nums.size(), idx = len - 2;
        while (idx >= 0 && nums[idx] >= nums[idx+1]) --idx;
        if (idx >= 0) {
            int tidx = bs(nums, idx + 1, len - 1, nums[idx]);
            swap(nums[tidx], nums[idx]);
        }
        reverse(nums, idx+1, len-1);
    }

    int bs(vector<int> &nums, int l, int r, int val) {
        while (l < r) {
           int m = l + (r - l + 1) / 2;
           if (nums[m] > val) l = m;
           else r = m - 1;
        }
        return l;
    }

    void reverse(vector<int> &nums, int l, int r) {
        while (l < r) {
            swap(nums[l++], nums[r--]);
        }
    }
};


// solution 1.1: 使用标准库实现
/*
    step 2 和 step 3 顺序其实可以调换

    step 1: 找idx
    step 2: 二分找比nums[idx]大的最小值， 并swap。
    step 3: reverse; 因为step找的是比nums[idx]大的最小值， 所以swap后， idx ~ len-1 还是有序的
*/
/*
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int len = nums.size(), idx = len - 2;
        while (idx >= 0 && nums[idx] >= nums[idx+1]) --idx;
        std::reverse(nums.begin() + idx + 1, nums.end());
        if (idx >= 0) {
            auto it = upper_bound(nums.begin() + idx + 1, nums.end(), nums[idx]);
            swap(nums[idx], *it);
        }
    }
};
*/


int main(int argc, char *argv[]) {

	return 0;
}
