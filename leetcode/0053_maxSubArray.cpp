/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Sun 25 Oct 2020 11:39:34 AM CST
 @ File Name	: 0053_maxSubArray.cpp
 @ Description	:  53. 最大子序和
 ************************************************************************/
#include <cstdint>
#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::max;



class Solution {
public:
	/*
	// solution 1 : 暴力
	int maxSubArray(vector<int>& nums) {
		int size = nums.size();	
		int sum = INT_MIN, sub_sum = 0;	

		for (int i = 0; i < size; ++i) {
			sub_sum = 0;
			for (int j = i; j < size; ++j) {
				sub_sum += nums[j];
				if (sub_sum > sum) sum = sub_sum;	
			}
		}
		return sum;
    	}
	*/


	// solution 2 : 分治
	// 求解MaxSubArray(arr, low, high), 可分解为求解 MaxSubArray(arr, low, mid)、MaxSubArray(arr, mid + 1, high) 和 最大子序列cross跨越mid 三种情况下的最大解
	// 	
	// 求解cross mid 的最大子序列   (mid -> low 的最大区间和) + (mid+1 -> high的最大区间和), 时间复杂度为O(N);
	// 整个问题的递推关系式为 : T(N) = 2T(N/2) + O(N), 根据master theorem, 最终时间复杂度为 O(NlogN)  
	//
	//
	// 优化, 参考leetcode官方解法， 可以简化求解cross mid 的最大子序列的过程， cross mid 的最大子序列和 其实等价于 l.rsum + r.lsum;只要在递归中维护好rsum 和 lsum的两个值， 那么就可以使用O（1）替代 O（N）, 
	// 故整个问题的递推关系式为 : T(N) = 2T(N/2) + O(1), 根据master theorem, 最终时间复杂度为 O(N)

         // Status 类在 Solution类的命名空间下
         // Solution::Status
         struct Status {
                 int msum;               // 当前序列中最大子序列和

                 // 下面几个用于辅助计算 cross mid 最大子序列和
                 int lsum;               // 包含左边界的最大子序列和
                 int rsum;               // 包含右边界的最大子序列和
                 int isum;               // 当前序列的左右元素和 (用于辅助计算lsum, rsum)
         };

         Status CalStatus(const Status &l, const Status &r) {
                 Status res;
                 res.msum = max(max(l.msum, r.msum), l.rsum + r.lsum);
                 res.lsum = max(l.lsum, l.isum + r.lsum);
                 res.rsum = max(r.rsum, l.rsum + r.isum);
                 res.isum = l.isum +r.isum;

                 return res;
         }

         Status GetMaxSubArray(vector<int>& nums, int low, int high) {
                 if (low == high) {
                         return Status{nums[low], nums[low], nums[low], nums[low]};
                 }

                 int mid =(low + high) >> 1;
                 Status l = GetMaxSubArray(nums, low, mid);
                 Status r = GetMaxSubArray(nums, mid + 1, high);
                 return CalStatus(l, r);
         }

	/*
        int maxSubArray(vector<int>& nums) {
                 int size = nums.size();
                 if (size <= 0) {
                         return INT_MIN;
                 }

                 return GetMaxSubArray(nums, 0, size - 1).msum;
         }
	 */

	// solution 3: DP
        // 有动态规划数组dp, dp[i] 为 以i元素为结尾的最大子序列, 存在递推关系式 dp[x] = max(nums[x] + dp[x-1], nums[x])
        //
        // 从关系式中得知， 又因为x 只与x-1 的dp[x-1]有关， 所以可以使用一个变量tmp_sum(代表以上一个元素结尾的最大子序列和)来替代dp数组
        int maxSubArray(vector<int>& nums) {
                int tmp_sum = 0;
                int sum = INT_MIN;
                for (int elem : nums) {
                        tmp_sum = tmp_sum > 0 ? tmp_sum + elem : elem;
                        sum = max(sum, tmp_sum);
                }
                return sum;
        }
};


int main(int argc, char *argv[]) {
	vector<int> vec{-2,1,-3,4,-1,2,1,-5,4};
	Solution obj;
	cout << obj.maxSubArray(vec) << endl;
	
	return 0;
}
