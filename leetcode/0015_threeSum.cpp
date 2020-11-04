/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Tue 03 Nov 2020 08:06:21 PM CST
 @ File Name	: 0003_threeSum.cpp
 @ Description	: 15. 三数之和
	
 思路：
	相对于1.两数之和， a + b = target， 三数之和 a + b + c = 0 其实可以转换为 a + b = -c;
	只不过对于两数之和固定的target值， -c是变化的， 我们可以尝试用一层循环遍历固定c的值，那么也就转换为两数之和的求解方式。
	求剩余的数组中是否能找到两个数之和 a + b = -c;
 ************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

class Solution {
public:
	// 获取下一个不重复的idx, 超出数组长度就返回尾后一个下标
	// len 指定最后一个元素的下一个位置
	int GetNextNonRepeatIdx(vector<int> &nums, int idx, int len) {
		int res = idx + 1;
		while (res < len && nums[res] == nums[idx]) ++res; 
		return res;
	}


	// sulution 1: 暴力, 三层循环 i, j, k，不过需要注意的是这里要排除重复组合问题。
	// 要排除重复组合， 可以通过控制i, j, k三个值对于重复值都只处理一遍来解决
	//
	// 如对于i， 要控制i只遍历出现一遍的数据， 那么可以先把数据排序， 然后遍历， 并且跳过上一次重复访问的数据来达到目的。
	//
	// 于是对于i,j,k，分别进行跳过重复数据的遍历， 可以写出如下三层循环
	//

	/*
	vector<vector<int>> threeSum(vector<int>& nums) {
		vector<vector<int>> res;
		sort(nums.begin(), nums.end());
		int len = nums.size();

		for (int i = 0; i < len - 2; i = GetNextNonRepeatIdx(nums, i, len - 2)) 
			for (int j = i + 1; j < len - 1; j = GetNextNonRepeatIdx(nums, j, len - 1)) 
				for (int k = j + 1; k < len; k = GetNextNonRepeatIdx(nums, k, len)) 
					if (nums[i] + nums[j] + nums[k] == 0) {
						res.push_back({nums[i], nums[j], nums[k]});		
					}

		return res;	
	}
	*/

	/*
	// solution 2 : 使用hashmap来优化一层循环查找, 不过还需要注意重复问题
	// 而且加入了一些优化点
	vector<vector<int>> threeSum(vector<int>& nums) {
		vector<vector<int>> res;
		sort(nums.begin(), nums.end());
		int len = nums.size();
		unordered_map<int, int> map;
	
		// 优化点一： 因为数组有序， 故 nums[i] <= nums[j] <= nums[k], 所以对于最外层循环i，并不需要继续计算大于0后的情况。
		for (int i = 0; i < len - 2 && nums[i] <= 0; i = GetNextNonRepeatIdx(nums, i, len - 2)) {
			// 将后续的数据加入map， 并统计每一个数据出现的个数
			map.clear();
			for (int j = i + 1; j < len; ++j) {
				map[nums[j]] += 1;	
			}
				
			// 开始第二层循环， 并且动态维护map数据, map数据维护策略如下:
			// @ 遍历到j时， 要把map[nums[j]] 个数减1;
			// @ 跳过j的所有重复数据时， 要把map[nums[j]] 整个数据清掉
			for (int j = i + 1; j < len - 1; j = GetNextNonRepeatIdx(nums, j, len - 1)) {
				// map[nums[j]] 个数减1	
				map[nums[j]] -= 1;	

				auto iter = map.find(0 - (nums[i] + nums[j]));
				if (iter != map.end() && iter->second > 0) {
					res.push_back({nums[i], nums[j], iter->first});
				}

				// 下一遍会跳过所有重复元素， 故这里要清掉nums[j]的索引
				map.erase(nums[j]);
			}
		}

		return res;	
	}
	*/


	// solution 3 : 双指针； 使用下标k 固定一个值， 作为固定的c, 用双指针i,j寻找存在a,b的和 a + b = -c 
	//		提前把数组排序， 跳过重复的同时， 可以通过双指针的左右夹逼快速找出 合适的a, b值
	vector<vector<int>> threeSum(vector<int>& nums) {
		vector<vector<int>> res;
		sort(nums.begin(), nums.end());
		int len = nums.size(), i, j, ans;
	
		// 优化点一： 因为数组有序， 故 nums[k] <= nums[i] <= nums[j], 所以对于最外层循环i，并不需要继续计算大于0后的情况。
		for (int k = 0; k < len - 2 && nums[k] <= 0; k = GetNextNonRepeatIdx(nums, k, len - 2)) {
			i = k+1;
		       	j = len-1;	

			while (i < j) {
				ans = nums[k] + nums[i] + nums[j];	
				if (ans > 0) {
					// 和太大， 减少j指针来控制和
					--j;	
					while (i < j && nums[j] == nums[j+1]) --j;
				} else if (ans < 0) {
					// 和太小， 增大i指针来控制和
					++i;	
					while (i < j && nums[i] == nums[i-1]) ++i;
				} else {
					// bingo
					res.push_back({nums[k], nums[i], nums[j]});

					// 两个指针同时收缩
					--j;	
					while (i < j && nums[j] == nums[j+1]) --j;
					++i;	
					while (i < j && nums[i] == nums[i-1]) ++i;	
				}
			}				
		}
		return res;	
	}


};

int main(int argc, char *argv[]) {
	Solution obj;	
	vector<int>vec({});
	obj.threeSum(vec);
	return 0;
}
