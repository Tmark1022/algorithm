/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Tue 23 Mar 2021 11:09:17 AM CST
 @ File Name	: 0056_merge.cpp
 @ Description	: 56. 合并区间 
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
	solution 1: 排序后合并区间
   */

// solution 1:
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
	sort(intervals.begin(), intervals.end());		
	vector<vector<int>> ans;
	for (int i = 0; i < intervals.size(); ++i) {
		if (ans.empty() || intervals[i][0] > ans.back()[1]) ans.push_back(intervals[i]);	
		else ans.back()[1] = max(ans.back()[1], intervals[i][1]); 
	}
	return ans;
    }
};

int main(int argc, char *argv[]) {

	return 0;
}
