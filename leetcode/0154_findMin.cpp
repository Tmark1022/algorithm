/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Wed 16 Dec 2020 12:05:22 PM CST
 @ File Name	: 0154_findMin.cpp
 @ Description	:  154. 寻找旋转排序数组中的最小值 II
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

// 相对153题，差别在于数组中存在重复元素, 当计算的mid 与 high 数值相等时， 那就不能判断当前mid 在大的有序边（左边） 还是 小的有序边(右边)), 这时需要特殊处理 


// solution 1: 二分查找, 极端情况下每次问题规模缩小1, 时间复杂度为O(N)
class Solution {
public:
    int findMin(vector<int>& nums) {
	int low = 0, high = nums.size() - 1;
	while (low < high) {
		int mid = low + (high - low) / 2;
		if (nums[mid] < nums[high]) {
			// mid -> high 是右边有序段， mid为当前最小值
			high = mid;
		} else if (nums[mid] > nums[high]) {
			// low -> mid 是左边有序段, 值都比high要打
			low = mid + 1;
		} else {
			// 相等情况， 不能区分mid到底在哪一边有序段， 需要特殊处理;
			
			// 不能采取low + 1的方法来处理; 对于有平移过的数组， 当nums[mid] == nums[high]时, nums[low]肯定 >= nums[high]; 
			// 但是对于没有平移过的数组, 其实nums[low] 才是最小的值， 故low + 1会错误。
			
			// 但是可以采取 high - 1 的方法来处理， 因为存在nums[mid] == nums[high], 且有low < high的前置要求， mid != high
			// 如果high的值就是最后的结果， 那么就算high - 1， 还是有mid的存在，所以最后结果还是正确的

			// 故使用high - 1来缩小1个规模，(平时都是二分查找缩小一半的)
			--high;
		}	
	}	
	return nums[low];
    }
};



int main(int argc, char *argv[]) {

	return 0;
}
