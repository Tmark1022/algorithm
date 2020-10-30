/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Wed 28 Oct 2020 11:20:17 AM CST
 @ File Name	: 0003_lengthOfLongestSubstring.cpp
 @ Description	: 3. 无重复字符的最长子串
 ************************************************************************/
#include <iostream>
#include <string>
#include <unordered_map>
#include <cstring>

using namespace std;

class Solution {
public:
	/*
	// solution 1 : 暴力, 两层循环枚举所有子串， 最后一层循环判断子串是否有重复字符
	int lengthOfLongestSubstring(string s) {
		int len = s.size();
		unordered_map<char, bool> map;
		int max_len = 0;	
		for (int i = 0; i < len; ++i) {
			for (int j = i; j < len; ++j) {	

				// i -> j 指定子串 是否重复
				bool is_repeat = false;
				map.clear();	
				for (int k = i; k <= j; ++k) {
					if (map.find(s[k]) != map.end()) {
						is_repeat = true;
						break;
					}				
					map[s[k]] = true;
				}

				// 判断最长
				if (!is_repeat) {
					max_len = max(max_len, j - i + 1);
				}
			}
		}

		return max_len;
	}
	*/

	/*
	// solution 2 : 暴力优化, 如果以i为起点， j为尾的子串重复， 那么i 到 j+1, j+2, j+... 都是重复的， 可以优化掉这些逻辑
	int lengthOfLongestSubstring(string s) {
		int len = s.size();
		unordered_map<char, bool> map;
		int max_len = 0;
		for (int i = 0; i < len; ++i) {
			map.clear();
			for (int j = i; j < len; ++j) {	
				if (map.find(s[j]) != map.end()) {
					// 直接break 掉， 后续的也不需要判断了
					break;
				}
				map[s[j]] = true;
				max_len = max(max_len, j - i + 1);
			}
		}

		return max_len;
	}
	*/

	// solution 3 : 滑动窗口, 出现重复字符时， 左指针移动到第一个重复字符的后一个位置  
	//
	// 这里还有一个优化点就是 用 bool[128] 替代 哈希表， 虽然哈希表查找O（1）, 但是还是要处理hash计算 和 collison
	int lengthOfLongestSubstring(string s) {
		int len = s.size(), max_len = 0, cur_len = 0;
		bool map[128];
		bzero(map, sizeof(map));
			
		// left 坐指针, right 右指针
		for (int left = 0, right = 0; right < len; ++right) {	
			if (map[s[right]]) {
				// left 移动到第一个重复字符的后一个位置， 并且清除map标记
				// 循环直到上一个left移动到上一个相同字符后一位
				while (map[s[right]]) {		
					map[s[left++]] = false;
				}			

				max_len = max(max_len, cur_len);
				cur_len = right - left + 1;
			} else {
				++cur_len;
			}	

			map[s[right]] = true;
		}

		return max(max_len, cur_len);
	}

};





int main(int argc, char *argv[]) {

	return 0;
}
