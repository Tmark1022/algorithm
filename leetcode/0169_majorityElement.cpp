/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Thu 03 Dec 2020 10:24:06 AM CST
 @ File Name	: 0169_majorityElement.cpp
 @ Description	: 169. 多数元素 
 ************************************************************************/
#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

using namespace std;

/*
题意 ： 
	给定一个大小为 n 的数组，找到其中的多数元素。多数元素是指在数组中出现次数大于 ⌊ n/2 ⌋ 的元素。
	你可以假设数组是非空的，并且给定的数组总是存在多数元素。
	
	注： 需要注意是找数组的多数元素(次数大于ceil(N/2)), 如果没有次数大于ceil(N/2)，那么下面很多算法都不能用 	

解法 ： 
	solution 1：暴力， 枚举每一个数组中的元素出现次数， 找到一个元素出现次数大于ceil(N/2)即终止， 最多要枚举N/2次就能枚举到答案元素。
			时间复杂度为 O(N^2), 空间复杂度为O(1)
		
	solution 2: hash table， 使用hash table来统计元素出现次数。
			时间复杂度为 O(N), 空间复杂度为O(N)

	solution 3: 排序， 答案即下标[N/2]的元素
			时间复杂度为 O(NlogN), 空间复杂度为O(1)
	
	solution 4: 分治， 可能中间过程中存在小数组的解并不正确，但是并不影响最终问题的解； 时间复杂度为O(nlogn), 时间复杂度为O(logn)【递归实现中使用的栈， 为树高度】
			虽然时间复杂度为O(nlogn)， 但是因为有超过一半元素是相同的，所以很多合并时走conquer(1)步骤即可完成遍历	

		divide : 每次将大数组划分为两个小数组，对于长度为1的数组， 其多数元素就是该元素。 
		conquer: 我们使用一种并不严谨的方法来合并小数组求大数组的多数元素， 过程如下
			1) 如果两个小数组的多数元素值相同， 那么该值就是大数组的多数元素;
			2) 如果两个小数组的多数元素值不同， 如两个数组的多数元素值为a和b, 那么我们在大数组中统计a和b的出现个数， a和b的多数者作为大数组的多数元素;
			   这一步其实是不严谨的，如小数组1中有6个a和4个c，小数组1的多数元素为a, 小数组2中有7个b和4个c，小数组2的多数元素为b， 但是合并后，
			   大数组的多数元素应该是c， 但是该算法得到的却是b。 但是这并不影响最终问题的解, 因为不断往上合并时， 总能遇到一个小数组的解为最终的多数元素【最起码第一次划分的小数组中， 其中一个数组的多数元素必定是最终的多数元素， 所以最后问题的解还是正确的】。
	
	solution 5: boyer moore 投票算法【最佳】, 算法过程如下(需要两个数组， 一个是候选元素， 一个是候选元素票数【默认为0】)：
			1) 候选元素等于当前遍历元素； 候选元素票数 + 1 
			2) 候选元素不等于当前遍历元素; 如果候选票数为0，更换候选元素为当前遍历元素; 如果候选元素票数大于0， 候选元素票数-1
			3) 遍历完成后， 候选元素就是最终的多数元素
		    时间复杂度O(N), 空间复杂度O(1)
	
	solution 6: 位运算, 对于int的每一个bit， 遍历数组统计位是1出现的次数， 出现次数大于N/2即代表最终多数元素在该位中也为1。

	solution 7: partion 求最大的(第)K个数,  这里K = N/2即可; 
			该算法的效率在本问题中非常依赖输入数据 :
			1)对于多数元素个数 约等于 N/2的时候算法效率最快，时间复杂度为O(N)
			2)对于多数元素个数 约等于 N的时候算法效率最慢, 相当于每次parition 只能把问题规模缩小1, 时间复杂度为O(N^2)

			空间复杂度为O（1）【如果递归实现时， 空间复杂度为递归深度， 因为最大深度可能为N， 故复杂度为O（N）】
*/

/*
// solution 1: 暴力
class Solution {
public:
    int majorityElement(vector<int>& nums) {
	for (auto &i : nums) {
		int count = 0;
		for (auto &j : nums) if (i == j) ++count; 
		if (count > nums.size() / 2) return i;
	}
	return -1;
    }
};

// solution 2: hash table
class Solution {
public:
    int majorityElement(vector<int>& nums) {
	unordered_map<int, int> map;
	int max_elem = -1, max_cnt = 0;	
	for (auto &i : nums) {
		++map[i];			
		if (map[i] > max_cnt) {
			max_elem = i;
			max_cnt = map[i];
		}
	}
	return max_elem;
    }
};

// solution 3: 排序
class Solution {
public:
    int majorityElement(vector<int>& nums) {
	    sort(nums.begin(), nums.end());
	    return nums[nums.size() / 2];
    }
};

// solution 4: 分治
class Solution {
public:
    int elemCnt(vector<int> &nums, int low, int high, int e) {
	int ans = 0;
	for (int i = low; i <= high; ++i)
		if (nums[i] == e) ++ans;
	return ans;
    }

    int majorityElement(vector<int>& nums, int low, int high) {
	// terminator
	if (low == high) return nums[low];		
	
	// split problem
	int mid = low + (high - low) / 2;
	
	// handle sub problem
	int l_res = majorityElement(nums, low, mid);	
	int r_res = majorityElement(nums, mid+1, high);	

	// merge result		
	if (l_res == r_res) {
		return l_res;	
	} else {
		return elemCnt(nums, low, high, l_res) >= elemCnt(nums, low, high, r_res) ? l_res : r_res;	
	}
    }

    int majorityElement(vector<int>& nums) {
	return majorityElement(nums, 0, nums.size() - 1);
    }
};
	
// solution 5: boyer moore 投票算法
class Solution {
public:
    // int majorityElement(vector<int>& nums) {
    //     int candidate = nums[0], vote = 0;
    //     for (int i = 1; i < nums.size(); ++i) {
    //     	if (candidate == nums[i]) ++vote; 	
    //     	else if (!vote) candidate = nums[i];
    //     	else --vote;  
    //     }
    //     return candidate;
    // }

    int majorityElement(vector<int>& nums) {
	    int candidate, vote = 0;
	    for (const auto &e : nums) {
		    if (!vote) {
			    candidate = e;
			    vote = 1;
		    } else {
			    candidate == e ? ++vote : --vote;
		    }
	    }
	    return candidate;
    }
};
*/

/*
// solution 6: 位运算
class Solution {
public:
    int majorityElement(vector<int>& nums) {
	int half = nums.size() / 2, ans = 0;
	for (int i = 1; i; i <<= 1) {
		int count = 0;
		for (auto &e : nums) e&i && ++count;
		if (count > half) ans |= i;		
	}
	return ans;
    }
};
*/


// solution 7: partition
class Solution {
public:
	int partition(vector<int>& nums, int low, int high) {
		if (low == high) return low;			

		// random 	
		int ran = std::rand() % (high - low);
		swap(nums[low], nums[low+ran]);

		int pivot = low;	
		for (int i = low+1; i <= high; ++i) {
			if (nums[i] < nums[low] && ++pivot != i) swap(nums[pivot], nums[i]);  
		}	
		swap(nums[pivot], nums[low]);
		return pivot;
	}

    int majorityElement(vector<int>& nums, int low, int high) {
	int pivot = partition(nums, low, high);				
	int half = nums.size()/2;
	if (pivot == half) return nums[pivot]; 	
	else if (half < pivot) return majorityElement(nums, low, pivot - 1);
	else return majorityElement(nums, pivot+1, high); 
    }

    int majorityElement(vector<int>& nums) {
	return majorityElement(nums, 0, nums.size() - 1);
    }
};




int main(int argc, char *argv[]) {

	return 0;
}
