/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Mon 04 Jan 2021 12:37:28 PM CST
 @ File Name	: 0198_rob.cpp
 @ Description	: 198. 打家劫舍 
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
	solution 1: 暴力(brute force), 回溯搜索
	solution 2: dp, 根据状态表不同的含义， 会有不同的状态转移方程
			1) f(i, 0) 代表第i个元素不选时最大偷窃金额, f(i, 1) 代表第i个元素选择时最大偷窃金额
			有如下状态转移方程:
				f(i, 0) = max(f(i-1, 0), f(i-1, 1))
				f(i, 1) = f(i-1, 0) + nums[i]

				最终结果为 max(f(n, 0), f(n, 1)), n为数组长度

			2) 我们对1)的状态转移方程优化一下， f(i) 代表0~i元素中最大的偷窃金额数，不规定第i个元素是否偷窃。
				如果不抢i， 收益就是 f(i-1)
				如果抢i，收益就是 f(i-2) + nums[i]
			故有如下状态转移方程:
				f(i) =  max(f(i-1), f(i-2) + nums[i]) 

				最终结果为 f(n)

			3) f(i) 代表第i个元素选择偷窃情况下的偷窃金额数
			有如下状态转移方程:
				f(i) =  max{f(0), f(1), ..., f(i-2)} + nums[i]

				又因 f(i-2) = max{f(0), f(1), ..., f(i-4)} + nums[i-2];
				即 f(i-2) 必定比 f(0) ... f(i-4) 都大， 故上述状态转移方程可以简化为:

				f(i) = max{f(i-2), f(i-3)} + nums[i];

				最终结果为 max{f(0), f(1), ... f(n-1), f(n)};
   */


/*
// solution 1: 回溯搜索【超时】
class Solution {
public:
	int ans = 0;
	// @select : 上一个idx是否选择
	void BackTracking(vector<int>& nums, int idx, int sum, int select) {
		if (idx == nums.size()) {
			ans = max(ans, sum);		
			return ;
		}

		// non select, 任何时候都可以不选择 
		BackTracking(nums, idx + 1, sum, 0);

		// select， 上一个idx没有选择， 当前才能选择
		if (!select) {	
			BackTracking(nums, idx+1, sum + nums[idx], 1);
		}
	}

    int rob(vector<int>& nums) {
	BackTracking(nums, 0, 0, 0);
	return ans;
    }
};

// solution 2.1: dp, 二维状态数组, 因为i状态只跟i-1状态相关， 故可以使用滚动变量来优化空间
class Solution {
public:
    int rob(vector<int>& nums) {
	int prev0 = 0, prev1 = 0;		
	for (auto &e : nums) {
		int cur0 = max(prev0, prev1);
		int cur1 = prev0 + e;  
		prev0 = cur0;
		prev1 = cur1;
	}	
	return max(prev0, prev1);
    }
};

// solution 2.2: dp, f(i) =  max(f(i-1), f(i-2) + nums[i]), 可以使用滚动变量来优化空间 
class Solution {
public:
    int rob(vector<int>& nums) {
	int prev = 0, cur = 0;		
	for (auto &e : nums) {
		int tmp  = max(cur, prev + e);
		prev = cur;
		cur = tmp;
	}	
	return cur;
    }
};
*/

/*
// solution 2.3: dp, f(i) =  max{f(0), f(1), ..., f(i-2)} + nums[i], 可以使用滚动变量来优化空间 	
//			m 代表 max{f(0), f(1), ..., f(i-2)}
class Solution {
public:
    // f(i) = max{f(i-2), .. f(0)} + nums[i];
    int rob(vector<int>& nums) {
        int m = 0, prev = 0, cur;
        for (auto &e : nums) {
            cur = m + e;
            m = max(m, prev);
            prev = cur;
        }
        return max(m, cur);
    }
};
*/

// solution 2.3 : dp,f(i) = max(f(i-2), f(i-3)) + nums[i];
class Solution {
public:
    int rob(vector<int>& nums) {
        int f, f1 = 0, f2 = 0, f3 = 0, res = INT_MIN;
        for (auto &e : nums) {
            f = max(f2, f3) + e;
            res = max(f, res);
            f3 = f2, f2 = f1, f1 = f;
        }
        return res;
    }
};

int main(int argc, char *argv[]) {

	return 0;
}


