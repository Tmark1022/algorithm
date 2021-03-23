/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Tue 23 Mar 2021 11:44:51 AM CST
 @ File Name	: 0438_findAnagrams.cpp
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

/*
	solution 1: 使用leetcode 242的 isAnagram 函数来校验异位词, 遍历选取每一个字符起点; 其中n为字符串s的size, k 为字符串p的size 
			isAnagram 实现:
				1) 数组排序, sort函数库O(klogk) / 计数排序 O(k) 
				2) 哈希表, O(k); 可以使用长度26数组替代 

			总时间复杂度 : O(nk), 空间复杂度 O(1)


	solution 2: 双指针滑动窗口, 解法思路同 leetcode 76; 使用滑动窗口解决子串cover问题。 
			使用哈希表remain 统计要组成字符串p, 每种字符还剩下多少个;  
			维护整型distance 来快速判断remain 中是否全部字符需要的数目都为0了	
			然后使用双指针组成滑动窗口 校验每一个起点
			优化 ： 因为都是小写字母, 所以可以使用长度为26的整型数组来替代哈希表

			时间复杂度 O(k + n), 空间复杂度O(1) 

   */


/*
// solution 1:
class Solution{
public:
	void CountingSort(string &a) {
		vector<int> cnt(26, 0); 
		for (auto &e : a) ++cnt[e - 'a'];	
		int idx = 0;
		for (int i = 0; i < cnt.size(); ++i) {
			for (int j = 1; j <= cnt[i]; ++j) a[idx++] = 'a' + i;	
		} 
	}

	bool IsAnagram_sort(string a, string b) {
		CountingSort(a);
		CountingSort(b);
		return a == b;
	}

	bool IsAnagram(string a, string b) {
		if (a.size() != b.size()) return false;
		vector<int> cnt(26, 0);
		for(auto &e : a) ++cnt[e-'a'];
		for(auto &e : b) {
			if (--cnt[e-'a'] < 0) return false;
		}
		return true;
	}

    vector<int> findAnagrams(string s, string p) {
	vector<int> ans;				
	for (int i = 0, sl = s.size(), pl = p.size(), end = sl-pl; i <= end; ++i) {
		if (IsAnagram(s.substr(i, pl), p)) ans.push_back(i);
	}
	return ans;
    }
};
*/


// solution 2:
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
	vector<int> remains(26, 0), ans;
	for (auto &ch : p) ++remains[ch - 'a'];	
	
	int distance = p.size();	
	for (int bidx = 0, eidx = 0; eidx < s.size(); ++eidx) {
		// 右指针
		if (--remains[s[eidx] - 'a'] >= 0) --distance;
		// 滑动窗口大小， 左指针
		if (eidx - bidx + 1 > p.size()) {
			if (++remains[s[bidx] - 'a'] > 0) ++distance; 	
			++bidx;
		}
		// 记录结果		
		if (!distance) ans.push_back(bidx);
	}
	return ans;
    }
};


int main(int argc, char *argv[]) {

	return 0;
}
