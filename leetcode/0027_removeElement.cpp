/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Wed 28 Oct 2026 12:01:54 PM CST
 @ File Name	: 0027_removeElement.cpp
 @ Description	: 27. 移除元素
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

// 直接记录不等于val的指针下边k
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int k = 0;
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] == val) continue;
            nums[k++] = nums[i];
        }
        return k;
    }
};


int main(int argc, char *argv[]) {

	return 0;
}
