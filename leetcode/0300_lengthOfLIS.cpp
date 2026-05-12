/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Mon 11 May 2026 04:15:56 PM CST
 @ File Name	: 0300_lengthOfLIS.cpp
 @ Description	: 
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
	// solution 1: brute force， backtracking 枚举子序列， 提前pruning
			time complexity O(2^n), space complexity O(n) 
	
	// solution 2: dp
	        设 f(i) 表示从开始位置到到下标i且以下标i元素结尾的最长递增子序列的长度， 存在一下递推关系式：
	            f(i) = max{f(j)...} + 1;            0 <= j < i 且 nums[j] < nums[i];
		    time complexity O(N^2), space complexity O(N)

	// solution 3: 二分查找
	              定义tail数组， tail[x] 的值表示 所有长度为x+1的递增子序列中【nums数组能组成多个长度为x+1的子序列】结尾元素的最小值。
	              根据tail定义可知， tail数组一定是严格升序的。
	              
	              时间复杂度 O(nlogn), 空间复杂度 O(n)
	

*/


/*
// solution 1: brute force， backtracking 枚举子序列， 提前pruning
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> tmp;
        int res = 0;
        backtracking(0, nums, tmp, res);
        return res;
    }

    void backtracking(int idx, vector<int> &nums, vector<int> &tmp, int &res) {
        if (idx == nums.size()) {
            res = tmp.size();
            return ;
        }

        // pruning
        if (nums.size() - idx + tmp.size() <= res) return ;

        // non pick
        backtracking(idx + 1, nums, tmp, res);

        // pick
        if (tmp.empty() || nums[idx] > tmp.back()) {
            tmp.push_back(nums[idx]);
            backtracking(idx + 1, nums, tmp, res);
            tmp.pop_back();
        }
    }
};
*/

// solution 2: dp
/*
        设 f(i) 表示从开始位置到到下标i且以下标i元素结尾的最长递增子序列的长度， 存在一下递推关系式：
            f(i) = max{f(j)...} + 1;            0 <= j < i 且 nums[j] < nums[i];
*/
/*
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int len = nums.size(), res = 1;
        vector<int> dp(len, 1);
        for (int i = 1; i < len; ++i) {
            for (int j = 0; j < i; ++j) {
                if (nums[j] >= nums[i]) continue;
                dp[i] = max(dp[i], dp[j] + 1);
            }
            res = max(res, dp[i]);
        }
        return res;
    }
};
*/

// solution 3: 二分查找
//              定义tail数组， tail[x] 的值表示 所有长度为x+1的递增子序列中【nums数组能组成多个长度为x+1的子序列】结尾元素的最小值。
//              根据tail定义可知， tail数组一定是严格升序的。
//              
//              时间复杂度 O(nlogn), 空间复杂度 O(n)
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> tail;
        for (auto &val : nums) {
            auto it = lower_bound(tail.begin(), tail.end(), val);
            if (it == tail.end()) tail.push_back(val);
            else *it = val;
        }
        return tail.size();
    }
};

/*
// solution 3: 二分查找	【自己实现二分查找逻辑】
//              定义tail数组， tail[x] 的值表示 所有长度为x+1的递增子序列中【nums数组能组成多个长度为x+1的子序列】结尾元素的最小值。
//              根据tail定义可知， tail数组一定是严格升序的。
//
//              时间复杂度 O(nlogn), 空间复杂度 O(n)
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> tail;
        for (auto &val : nums) {
            auto idx = binarySearch(tail, val);
            if (idx == tail.size()) tail.push_back(val);
            else tail[idx] = val;
        }
        return tail.size();
    }

    int binarySearch(vector<int> &tail, int val) {
        if (tail.empty() || val > tail.back()) return tail.size();
        int l = 0, r = tail.size() - 1, m;
        while (l < r) {
            m = l + (r - l) / 2;
            if (tail[m] >= val) r = m;
            else l = m + 1;
        }
        return l;
    }
};
*/


int main(int argc, char *argv[]) {

	return 0;
}
