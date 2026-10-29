/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Wed 25 Nov 2020 11:51:11 AM CST
 @ File Name	: 0026_removeDuplicates.cpp
 @ Description	: 26. 删除排序数组中的重复项 
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
// solution 1: 借助一个辅助数组
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        vector<int> tmp;
        for (auto &val : nums) {
            if (tmp.size() && tmp.back() == val) continue;
            tmp.push_back(val);
        }
        nums = tmp;
        return nums.size();
    }
};
*/

// solution 2: 原地修改
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int k = 1;
        for (int i = 1; i < nums.size(); ++i) {
            if (nums[i] == nums[i-1]) continue;
            nums[k++] = nums[i];
        }
        return k;
    }
};


int main(int argc, char *argv[]) {

	return 0;
}
