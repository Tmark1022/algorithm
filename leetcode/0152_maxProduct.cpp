/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Wed 30 Dec 2020 09:11:27 AM CST
 @ File Name	: 0152_maxProduct.cpp
 @ Description	: 152. 乘积最大子数组 
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
	solution 1:暴力, 枚举连续子序列的开始与结束位置
	solution 2: divide & conquer
	solution 3: dp, 因为数值有正有负, 当当前数值为负数时， 最大值其实是与最小值相乘产生的
			假设 fmax(n) 代表以n结尾的子序列的乘积最大值， fmin(n)代表以n结尾的子序列的乘积最小值。
			状态转移方程为: 
				fmax(n) = max{n, fmax(n-1) * n, fmin(n-1)*n};
				fmin(n) = min{n, fmax(n-1) * n, fmin(n-1)*n};
   */


/*
// solution 1: 暴力 
class Solution {
public:
    int maxProduct(vector<int>& nums) {
	if (!nums.size()) return 0;			
	int ans = INT_MIN;
	for (int i = 0; i < nums.size(); ++i) {
		for (int j = i, tmp = 1; j < nums.size(); ++j) {
			tmp *= nums[j];	
			ans = max(tmp, ans);	
		}
	}	
	return ans;
    }
};
*/

/*
// solution 2: divide & conquer
struct Node{
    int sP;
    int lMinP, lMaxP;
    int rMinP, rMaxP;
    int tP; 
    Node(int s, int l1, int l2, int r1, int r2, int t):sP(s), lMinP(l1), lMaxP(l2), rMinP(r1), rMaxP(r2), tP(t) {}
};

class Solution {
public:
    int maxProduct(vector<int>& nums) {
        auto ret = recurse(nums, 0, nums.size() - 1);
        return ret.sP;
    }

    Node recurse(vector<int> &nums, int low, int high) {
        if (low == high) return {nums[low], nums[low], nums[low], nums[low], nums[low], nums[low]};

        int mid = low + (high - low) / 2;
        auto lRet = recurse(nums, low, mid);
        auto rRet = recurse(nums, mid + 1, high);

        int s = max({lRet.sP, rRet.sP, lRet.rMinP * rRet.lMinP, lRet.rMaxP * rRet.lMaxP}); 
        int l1 = min(lRet.lMinP, lRet.tP >= 0 ? lRet.tP * rRet.lMinP : lRet.tP * rRet.lMaxP); 
        int l2 = max(lRet.lMaxP, lRet.tP >= 0 ? lRet.tP * rRet.lMaxP : lRet.tP * rRet.lMinP); 
        int r1 = min(rRet.rMinP, rRet.tP >= 0 ? rRet.tP * lRet.rMinP : rRet.tP * lRet.rMaxP); 
        int r2 = max(rRet.rMaxP, rRet.tP >= 0 ? rRet.tP * lRet.rMaxP : rRet.tP * lRet.rMinP); 
        int t = lRet.tP * rRet.tP;
        return {s, l1, l2, r1, r2, t};
    }
};
*/

// solution 2: dp
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        if (!nums.size()) return 0;
        int fmax = nums[0], fmin = nums[0], ans = fmax;
        for (int i = 1; i < nums.size(); ++i) {
                if (nums[i] < 0) swap(fmax, fmin);
                fmax = max(nums[i], fmax * nums[i]);
                fmin = min(nums[i], fmin * nums[i]);;
                ans = max(fmax, ans);
        }
        return ans;
    }
};

int main(int argc, char *argv[]) {

	return 0;
}
