/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Thu 17 Dec 2020 10:07:17 AM CST
 @ File Name	: 0081_search.cpp
 @ Description	: 81. 搜索旋转排序数组 II 
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

// solution 1: 暴力
// solution 2: 二分查找， 当nums[mid] == nums[low] 时， 要特殊处理; 极端情况下（所有值相等）, 时间复杂度为O(N)

// solution 2:
class Solution {
public:
    bool search(vector<int>& nums, int target) {
        if (!nums.size()) return false;
        int low = 0, high = nums.size() - 1;
        while (low <= high) {
                int mid = low + (high - low) / 2;
                if (nums[mid] == target) return true;

                if (nums[mid] > nums[low]) {
                        // low ~ mid 是单调的
                        if (nums[low] <= target && target < nums[mid]) high = mid - 1;
                        else low = mid + 1;
                } else if (nums[mid] < nums[low]) {
                        // mid ~ high 是单调的
                        if (nums[mid] < target && target <= nums[high]) low = mid + 1;
                        else high = mid - 1;
                } else {
                        // nums[low] == nums[mid], 且low不会是答案， 所以可以排除
                        ++low;
                }
        }
        return false;
    }
};



int main(int argc, char *argv[]) {

	return 0;
}
