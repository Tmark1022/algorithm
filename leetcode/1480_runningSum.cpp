/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Fri 18 Dec 2020 12:02:15 PM CST
 @ File Name	: 1480_runningSum.cpp
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



// solution 1: 没有什么技巧可言， 不过需要在面试时注意弄清楚能否修改nums数组
class Solution {
public:
    vector<int> runningSum(vector<int>& nums) {
	for (int i = 1; i < nums.size(); ++i) nums[i] += nums[i-1]; 
	return nums;
    }
};

int main(int argc, char *argv[]) {

	return 0;
}
