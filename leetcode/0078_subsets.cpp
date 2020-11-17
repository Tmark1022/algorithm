/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Tue 17 Nov 2020 02:25:45 PM CST
 @ File Name	: 0078_subsets.cpp
 @ Description	: 
 ************************************************************************/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

/*
solution 1: 回溯
solution 2: 二进制枚举, 迭代实现
solution 3: 二进制枚举, 递归实现(回溯) 
solution 4: 借鉴二进制枚举，根据n取与不取， 可以得出递推关系式 f(n) = f(n-1) + (f(n-1)结果中加上元素n)  
	    这是一个动态规划问题， 因为f(n) 只与 f(n-1)的结果有关， 那么可以只取一个变量vector<vector<int>> last 作为上一个问题的解
	    这里使用迭代实现
solution 5: 借鉴二进制枚举，根据n取与不取， 可以得出递推关系式 f(n) = f(n-1) + (f(n-1)结果中加上元素n)  
	    这是一个动态规划问题， 因为f(n) 只与 f(n-1)的结果有关， 那么可以只取一个变量vector<vector<int>> last 作为上一个问题的解
	    这里使用递归实现
*/


/*
// solution 1: 回溯
class Solution {
public:

	void BackTracking(int start, vector<int> &nums, vector<int>& tmp, vector<vector<int>> &ans) {	
		ans.push_back(tmp);

		// terminator, 可以省略,下面确定范围时就已经排除了终结条件了
		//if (start >= nums.size()) {
		//	return ;
		//}
		
		// 确定范围(剪枝？)	
		for (int i = start; i < nums.size(); ++i) {
			// process logic of this level
			tmp.emplace_back(nums[i]);	

			// drill down
			BackTracking(i + 1, nums, tmp, ans);	
			// reverse env
			tmp.pop_back();
		}	
	}

    vector<vector<int>> subsets(vector<int>& nums) {
	vector<int> tmp;	
	vector<vector<int>> ans; 
	BackTracking(0, nums, tmp, ans);	
	return ans;
    }
};
*/
/*
// solution 2: 二进制枚举, 迭代实现
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
	vector<int> tmp;	
	vector<vector<int>> ans; 
	int len = nums.size();

	for (int i = 0; i < (1 << len); ++i) {
		tmp.clear();
		for (int j = 0; j < len; ++j) {
			if (i & (1 << j)) tmp.push_back(nums[j]);					
		}	
		ans.push_back(tmp);
	}	
	return ans;
    }
};
*/

/*
// solution 3: 二进制枚举, 递归实现(回溯) 
class Solution {
public:
	void BackTracking(int start, vector<int>&nums, vector<int> &tmp, vector<vector<int>>& ans) {
		// terminator	
		if (start == nums.size()) {
			ans.push_back(tmp);
			return ;
		}			

		// 每一层递归要处理的问题: 是否要择当前start元素
		
		// non pick
		BackTracking(start + 1, nums, tmp, ans);	

		// pick	
		tmp.emplace_back(nums[start]);	
		BackTracking(start + 1, nums, tmp, ans);	
		tmp.pop_back();
	}

    vector<vector<int>> subsets(vector<int>& nums) {
	vector<int> tmp;	
	vector<vector<int>> ans; 
	BackTracking(0, nums, tmp, ans);
	return ans;
    }
};
*/

/*
// solution 4: dp, 迭代实现 
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
	vector<vector<int>> last = {{}};			// 初始, 有一个空集合	
	vector<vector<int>> tmp;			
	for (int i = 0; i < nums.size(); ++i) {
		tmp.clear();	
		for(auto elem : last) {
			elem.push_back(nums[i]);	
			tmp.push_back(elem);
		}
		last.insert(last.end(), tmp.begin(), tmp.end());
	}	
	return last;
    }
};
*/

// solution 5: dp, 递归实现
class Solution {
public:
	vector<vector<int>> Help(int n, vector<int> &nums) {
		// terminator
		if (n <	0) {
			return {{}};
		}

		// 每一层递归的问题 : n-1的解 最后加上n元素
		vector<vector<int>> last = Help(n-1, nums); 		
		vector<vector<int>> ans;			
		for (auto e : last) {
			e.push_back(nums[n]);
			ans.push_back(e);
		}
		ans.insert(ans.end(), last.begin(), last.end());
		return ans;
	}

    vector<vector<int>> subsets(vector<int>& nums) {
	    return Help(nums.size() - 1, nums);
    }
};

int main(int argc, char *argv[]) {

	return 0;
}
