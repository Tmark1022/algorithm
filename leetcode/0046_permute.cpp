/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Wed 18 Nov 2020 09:00:05 PM CST
 @ File Name	: 0046_permute.cpp
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
// solution 1 : visit 辅助数组
class Solution {
public:
    void BackTracking(vector<int> nums, vector<bool> &visit, vector<int> &tmp, vector<vector<int>>& ans) {
        if (tmp.size() == nums.size()) {
            ans.push_back(tmp);
            return;
        }
        for (int i = 0; i < nums.size(); ++i) {
		if (visit[i]) continue;
		visit[i] = true;
		tmp.push_back(nums[i]);
		BackTracking(nums, visit, tmp, ans);
		visit[i] = false;
		tmp.pop_back();
        }
    }

    vector<vector<int>> permute(vector<int>& nums) {
        vector<int> tmp;
	vector<bool> visit(nums.size(), false);
        vector<vector<int>> ans;
        BackTracking(nums, visit, tmp, ans);
        return ans;
    }
};
*/

// solution 2: 无须辅助数组, 通过在原来的nums数组上划分已经使用 和 无使用区域 
class Solution {
public:
    void BackTracking(vector<int> nums, int start, vector<vector<int>>& ans) {
        if (start == nums.size()) {
            ans.push_back(nums);
            return;
        }

        for (int i = start; i < nums.size(); ++i) {
		std::swap(nums[start], nums[i]);
		BackTracking(nums, start+1, ans);
		std::swap(nums[start], nums[i]);
        }
    }

    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> ans;
        BackTracking(nums, 0,  ans);
        return ans;
    }
};

int main(int argc, char *argv[]) {

	return 0;
}
