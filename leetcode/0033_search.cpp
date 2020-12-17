/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Wed 16 Dec 2020 08:27:28 PM CST
 @ File Name	: 0033_search.cpp
 @ Description	: 33. 搜索旋转排序数组 
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

// solution 1: 暴力， O(N)  
// solution 2: 参考leetcode 153, 使用二分查找快速找到两个有序数组的分割点pivot, 然后进行常规的二分查找得到最后结果
// solution 3: 直接二分查找

/*
// solution 2:
class Solution {
public:
    int search(vector<int>& nums, int target) {
	int l = 0, h = nums.size()-1;		
	while (l < h) {
		int mid = l + (h-l)/2;
		if (nums[mid] < nums[h]) h = mid;	
		else l = mid + 1;
	}

	int pivot = l;	// 指向最小值
	if (target >= nums[0]) {
		// 位于左边有序数组
		l = 0;
		h = pivot ?  pivot - 1 : nums.size() - 1;			// pivot是0 特殊处理一下
	} else {
		// 位于右边有序数组
		l = pivot;	
		h = pivot ? nums.size()	- 1 : -1;				// pivot是0， 还要比nums[0] 小， 那么就是不可能存在	
	}
	while (l <= h) {
		int mid = l + (h-l)/2;
		if (nums[mid] == target) return mid;	
		else if (nums[mid] < target) l = mid + 1; 
		else h = mid - 1;
	}	
	return -1;
    }
};
*/

// solution 3:
class Solution {
public:
    int search(vector<int>& nums, int target) {
	int l = 0, h = nums.size()-1;		
	while (l <= h) {
		int mid = l + (h-l)/2;
		if (nums[mid] == target) return mid;		

		if (nums[mid] >= nums[l]) {
			// 左边 l ~ mid 是有序的	
			if (target < nums[mid] && target >= nums[l]) h = mid - 1;	
			else l = mid + 1; 
		} else {
			// 右边 mid ~ h 是有序的 
			if (target > nums[mid] && target <= nums[h]) l = mid + 1;	
			else h = mid - 1;
		}
	}
	return -1;
    }
};


int main(int argc, char *argv[]) {

	return 0;
}
