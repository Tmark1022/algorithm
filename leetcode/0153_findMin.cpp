/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Wed 16 Dec 2020 11:19:47 AM CST
 @ File Name	: 0153_findMin.cpp
 @ Description	: 153. 寻找旋转排序数组中的最小值
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

// solution 1: 暴力， O（N）

// solution 2: 二分查找, O(logN)
class Solution {
public:
    int findMin(vector<int>& nums) {
	int lo = 0, hi = nums.size()-1;				
	while (lo < hi) {
		int mid = lo + (hi - lo) / 2;
		if (nums[mid] < nums[hi]) hi = mid;		
		else lo = mid + 1;	
	}	
	return nums[lo];
    }
};


int main(int argc, char *argv[]) {

	return 0;
}
