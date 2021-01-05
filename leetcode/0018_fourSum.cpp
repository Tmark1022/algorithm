/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Tue 05 Jan 2021 02:50:27 PM CST
 @ File Name	: 0018_fourSum.cpp
 @ Description	: 18. 四数之和 
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
	solution 1: 暴力, 四层for循环每组所有可能组合, 时间复杂度O(n^4) 

	solution 2: 两层循环枚举前两个元素， 后两个元素使用左右夹逼的方式, 时间复杂度O(n^3)
*/

// solution 2:
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> ans;
        int len = nums.size();
        if (len < 4) return ans;
        sort(nums.begin(), nums.end());
        for (int i = 0; i <= len - 4; ++i) {
		// pruning
		if (i > 0 && nums[i] == nums[i-1]) continue;	
	    	if (nums[i] + nums[i+1] + nums[i+2] + nums[i+3] > target) break;
	    	if (nums[i] + nums[len-3] + nums[len-2] + nums[len-1] < target) continue;
	    
		for (int j = i+1; j <= len - 3; ++j) {
	    		// pruning
			if (j > i+1 && nums[j] == nums[j-1]) continue;	
	    		if (nums[i] + nums[j] + nums[j+1] + nums[j+2] > target) break;
	    		if (nums[i] + nums[j] + nums[len-2] + nums[len-1] < target) continue;

			// 左右夹逼
			int low = j+1, high = len-1;
            		while (low < high) {
            		    int sum = nums[i] + nums[j] + nums[low] + nums[high];
            		    if (sum > target) {
            		        --high;
            		    } else if (sum < target) {
            		        ++low;
            		    } else {
            		        ans.push_back({nums[i], nums[j], nums[low], nums[high]});
            		        --high;
            		        while (low < high && nums[high] == nums[high+1]) --high;
            		        ++low;
            		        while (low < high && nums[low] == nums[low-1]) ++low;
            		    }
            		}
		}
        }
        return ans;
    }
};



int main(int argc, char *argv[]) {

	return 0;
}
