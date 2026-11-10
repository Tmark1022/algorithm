/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Tue 10 Nov 2026 12:06:00 PM CST
 @ File Name	: 0238_productExceptSelf.cpp
 @ Description	: 238. 除了自身以外数组的乘积 
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
// solution 1: brute force
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int len = nums.size();
        vector<int> res(len, 1);
        for (int i = 0; i < len; ++i) {
            for (int j = 0; j < len; ++j) {
                if (i == j) continue;
                res[j] *= nums[i];
            }
        }
        return res;
    }
};

// solution 2: 前后缀
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int len = nums.size();
        vector<int> prefix(len, 1), suffix(len, 1), res(len);
        for (int i = 1; i < len; ++i) {
            prefix[i] = prefix[i-1] * nums[i-1];
            suffix[len-i-1] = suffix[len - i] * nums[len - i];
        }
        for (int i = 0; i < len; ++i) {
            res[i] = prefix[i] * suffix[i];
        }
        return res;
    }
};
*/

// solution 3: 前后缀（空间上的优化）, O(1) 空间复杂度【不算res数组空间】
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int len = nums.size();
        vector<int> res(len, 1);
        for (int i = len-2; i >= 0; --i) {
            res[i] = res[i+1] * nums[i+1];
        }

        int lp = 1;
        for (int i = 0; i < len; ++i) {
            res[i] *= lp;
            lp *= nums[i];
        }
        return res;
    }
};

int main(int argc, char *argv[]) {

	return 0;
}
