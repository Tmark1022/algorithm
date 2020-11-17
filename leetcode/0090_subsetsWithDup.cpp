/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Tue 17 Nov 2020 06:36:17 PM CST
 @ File Name	: 0090_subsetsWithDup.cpp
 @ Description	: 
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

/*
参考链表 : https://leetcode-cn.com/problems/subsets-ii/solution/xiang-xi-tong-su-de-si-lu-fen-xi-duo-jie-fa-by-18/
solution 1: 回溯 + 剪枝
solution 2: f(n) = f(n-1) + [f(n-1).push_back(n)], 指定startIndex
solution 3: f(n) = f(n-1) + [f(n-1).push_back(n)], 统计重复元素的个数, 普通不重复元素有选与不选， 而重复的元素的整体有多种选择，如重复元素aa当做的一个整体， 有不选， 有选一个元素a， 有选二个元素aa
   */


/*
// solution 1: 回溯 + 剪枝
class Solution {
public:

	void BackTracking(int start, vector<int>& nums, vector<int>& tmp, vector<vector<int>>& ans) {
		ans.push_back(tmp);

		for (int i = start; i < nums.size(); ++i) {
			// 剪枝
			if (i > start && nums[i] == nums[i-1]) continue; 	

			tmp.push_back(nums[i]);
			BackTracking(i + 1, nums, tmp, ans);
			tmp.pop_back();
		}
	}

    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
	vector<int> tmp;	        
	vector<vector<int>> ans;
	std::sort(nums.begin(), nums.end());
	BackTracking(0, nums, tmp, ans);

	return ans;
    }
};
*/

/*
// solution 2: f(n) = f(n-1) + [f(n-1).push_back(n)], 指定startIndex， 迭代实现
class Solution {
public:

    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
	vector<vector<int>> ans = {{}}, tmp;
	int cacheIndex = 0;

	std::sort(nums.begin(), nums.end());
	for (int i = 0; i < nums.size(); ++i) {
		tmp.clear();
		int startIdx = 0;
		if (i > 0 && nums[i] == nums[i-1]) startIdx = cacheIndex;		
		for (int j = startIdx; j < ans.size(); ++j) {
			tmp.push_back(ans[j]);
			tmp.back().push_back(nums[i]);
		}	
		cacheIndex = ans.size();
		ans.insert(ans.end(), tmp.begin(), tmp.end());			
	}	

	return ans;
    }
};
*/

/*
// solution 2: f(n) = f(n-1) + [f(n-1).push_back(n)], 指定startIndex, 递归实现
class Solution {
public:

	vector<vector<int>> Generate(int n, int& startIdx, vector<int> &nums) {
		if (n < 0) {
			return {{}};
		}
	
		int lastStartIdx;
		vector<vector<int>> ans =  Generate(n-1, lastStartIdx, nums);  
		vector<vector<int>> tmp; 
		for (int j = (n > 0 && nums[n] == nums[n-1]) ? lastStartIdx: 0 ; j < ans.size(); ++j) {
			tmp.push_back(ans[j]);
			tmp.back().push_back(nums[n]);
		}			
		startIdx = ans.size();
		ans.insert(ans.end(), tmp.begin(), tmp.end());			
		return ans;	
	}	

    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
	std::sort(nums.begin(), nums.end());
	int startIdx;
	return Generate(nums.size()-1, startIdx, nums);
    }
};
*/

/*
// solution 3: f(n) = f(n-1) + [f(n-1).push_back(n)], 统计重复元素, 迭代实现
class Solution {
public:

    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
	vector<vector<int>> ans = {{}}, tmp;
	int count, len = nums.size(); 
	std::sort(nums.begin(), nums.end());

	for (int i = 0; i < len; i+=count) {
		// 计算重复元素个数， 组成一个整体
		count = 1;	
		while (i+count < len && nums[i] == nums[i+count]) ++count;

		vector<vector<int>> tmp;
		for (auto e: ans) {
			for (int j = 1; j <= count; ++j) {
				e.emplace_back(nums[i]);	
				tmp.emplace_back(e);
			}
		}	
		ans.insert(ans.end(), tmp.begin(), tmp.end());			
	}
	return ans;
    }
};
*/

// solution 3: f(n) = f(n-1) + [f(n-1).push_back(n)], 统计重复元素, 递归实现
class Solution {
public:
	vector<vector<int>> Generate(int n, vector<int> &nums) {
		if (n < 0) {
			return {{}};
		}
	
		// 计算重复元素个数
		int count = 1;	
		while (n - count >= 0 && nums[n] == nums[n-count]) ++count; 

		vector<vector<int>> ans =  Generate(n-count, nums);  
		vector<vector<int>> tmp; 
		for (auto e: ans) {
			for (int j = 1; j <= count; ++j) {
				e.emplace_back(nums[n]);
				tmp.emplace_back(e);
			}
		}	
		ans.insert(ans.end(), tmp.begin(), tmp.end());			
		return ans;	
	}	

    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
	std::sort(nums.begin(), nums.end());
	return Generate(nums.size()-1, nums);
    }
};


int main(int argc, char *argv[]) {

	return 0;
}
