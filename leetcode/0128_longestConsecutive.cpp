/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Wed 04 Feb 2026 06:08:49 PM CST
 @ File Name	: 0128_longestConsecutive.cpp
 @ Description	: 128.最长连续序列 
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
	solution 1: 排序再一遍循环得出最大的连续序列，因为输入数据并不适合使用计数基数排序，所以最终的时间复杂度为O(nlogn), 空间复杂度为排序递归深度O(logn)
			不符合题意需要的O(N)时间复杂度。

	solution 2: hashtable， 遍历nums的元素elem, 判断是否为序列头部， 是的就判断elem+1, elem+2, ... elem+x 是否在nums内， 以此来计算出最长连续序列。
		    因为这里剪枝了非序列头部elem，故通常时间复杂度为O(N)

		Note:
			需要注意， 如果nums中有多个相同的最长序列头部，会导致多次重复判断elem+1, elem+2 ... elem+x，以导致在特殊的输入数据时使得时间复杂度最差为O(N^2)
		    可以增加一个visit数据， 来记录该头部是否已经计算过， 来规避该问题。

			或者更优的方式是直接遍历hashtable【已经去重】
*/

/*
// solution 1:排序
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
            if (!nums.size()) return 0;
            std::sort(nums.begin(), nums.end());
            auto e = std::unique(nums.begin(), nums.end());

            int res = 1;
            for (int i = 1, len = 1; i < distance(nums.begin(), e); ++i) {
                    if (nums[i] != nums[i-1] + 1) {
                            len = 1;
                    } else {
                        res = max(res, ++len);
                    }
            }
            return res;
    }
};

// solution 2: hashtable
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
            unordered_set<int> s(nums.begin(), nums.end()), visit;
            int res = 0, cnt;
            for (auto e : nums) {
                    if (s.count(e-1) || visit.count(e)) continue;
                    visit.insert(e);
                    cnt = 1;
                    while (s.count(++e)) ++cnt;
                    res = max(res, cnt);
            }
            return res;
    }
};
*/

// solution 2: hashtable
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
            unordered_set<int> s(nums.begin(), nums.end());
            int res = 0, cnt;
            for (auto e : s) {
                    if (s.count(e-1)) continue;
                    cnt = 1;
                    while (s.count(++e)) ++cnt;
                    res = max(res, cnt);
            }
            return res;
    }
};






int main(int argc, char *argv[]) {

	return 0;
}
