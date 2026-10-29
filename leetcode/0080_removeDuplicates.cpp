/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Thu 29 Oct 2026 02:18:37 PM CST
 @ File Name	: 0080_removeDuplicates.cpp
 @ Description	: 80. 删除有序数组中的重复项 II 
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

// 原地修改
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int k = 1;
        for (int i = 1, cnt = 1; i < nums.size(); ++i) {
            if (nums[i] == nums[i-1]) ++cnt;
            else cnt = 1;
            if (cnt > 2) continue;
            nums[k++] = nums[i];
        }
        return k;
    }
};

int main(int argc, char *argv[]) {

	return 0;
}
