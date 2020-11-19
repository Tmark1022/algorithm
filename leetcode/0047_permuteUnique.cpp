/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Thu 19 Nov 2020 10:35:55 AM CST
 @ File Name	: 0047_permuteUnique.cpp
 @ Description	: 47. 全排列 II 
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


// solutin 1: 回溯 + 剪枝(剪去重复的元素), 使用辅助数组visit 
class Solution {
public:

	void BackTracking(vector<int> &nums, vector<bool>& visit, vector<int> &tmp, vector<vector<int>> &ans) {
		if (tmp.size() == nums.size()) {
			ans.push_back(tmp);	
			return ;
		}
		
		for (int i = 0, last = -1; i < nums.size(); ++i) {
			if (visit[i] || (last >= 0 && nums[last] == nums[i])) continue;	
			visit[i] = true;
			tmp.push_back(nums[i]);
			BackTracking(nums, visit, tmp, ans);
			tmp.pop_back();
			visit[i] = false;	
			last = i;
		}
	}	

    vector<vector<int>> permuteUnique(vector<int>& nums) {
	if (!nums.size()) return {{}};
	vector<int> tmp;
	vector<bool> visit(nums.size(), false);
	vector<vector<int>> ans;
	std::sort(nums.begin(), nums.end());		
	BackTracking(nums, visit, tmp, ans);	
	return ans;
    }
};


int main(int argc, char *argv[]) {

	return 0;
}
