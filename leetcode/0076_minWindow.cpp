/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Tue 26 Jan 2021 10:13:21 AM CST
 @ File Name	: 0076_minWindow.cpp
 @ Description	: 76. 最小覆盖子串  
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
	solution 1: brute force; 枚举s中的子串起点和终点， 然后判断子串是否覆盖t字符串; 
			判断是否覆盖使用 两个unordered_map, 判断子串的字符个数是否覆盖t字符串;	
			时间复杂度O(N^2 * S), S 为字符种类数; 空间复杂度O(S);
	solution 2: 双指针滑动窗口; 优雅地暴力， 缩小搜索子区间。     
			1) 使用两个unordered_map 来判断子串覆盖, 时间复杂度O(S); 总时间复杂度为O(NS)
			2) 维护变量amount, 表示包含t字符串的字符个数; 判断条件 amout == t.size() 表示子串覆盖， 时间复杂度O(1); O(N)

	solution 3: soluton 2 中对s字符串进行预处理， 把没有一些没有关系的字符先剔除出去
   */


/*
// solution 1: brute force
class Solution {
public:
	bool IsCover(unordered_map<char, int>& smap, unordered_map<char, int> &tmap) {
		for (const auto & e : tmap) {
			if (smap[e.first] < e.second) return false;	
		}
		return true;
	}

    string minWindow(string s, string t) {
	unordered_map<char, int> tmap;	
	for (auto &e : t) ++tmap[e];

	// 这里可以做一些简单的剪枝, 如最小子串 >= t.size(); 查找过程中 >= min_len 的可以跳过不查
	int pos = -1, min_len = INT_MAX, slen = s.size(), tlen = t.size();
	for (int i = 0; i <= slen - tlen; ++i) {
		unordered_map<char, int> smap;
		for (int j = i; j < slen && j - i + 1 < min_len; ++j) {
			++smap[s[j]];
			if (IsCover(smap, tmap)) pos = i, min_len = j - i + 1; 	
		}
	}	

	if (pos < 0) return "";		
	else return s.substr(pos, min_len);
    }
};
*/

/*
// solution 2: 滑动窗口(1)
class Solution {
public:
	bool IsCover(unordered_map<char, int>& smap, unordered_map<char, int> &tmap) {
		for (const auto & e : tmap) {
			if (smap[e.first] < e.second) return false;	
		}
		return true;
	}
    string minWindow(string s, string t) {
	unordered_map<char, int> tmap, smap;	
	for (auto &e : t) ++tmap[e];
	// 这里可以做一些简单的剪枝, 如最小子串 >= t.size(); 查找过程中 >= min_len 的可以跳过不查
	int pos = -1, min_len = INT_MAX, slen = s.size(), tlen = t.size();
	for (int left = 0, right = 0; right < slen; ++right) {
		++smap[s[right]];
		while (IsCover(smap, tmap)) {
			if (right - left + 1 < min_len) pos = left, min_len = right - left + 1;		
			--smap[s[left]];
			++left;
		}	
	}
	if (pos < 0) return "";		
	else return s.substr(pos, min_len);
    }
};

// solution 2: 滑动窗口(1)
class Solution {
public:
	bool IsCover(unordered_map<char, int>& smap, unordered_map<char, int> &tmap) {
		for (const auto & e : tmap) {
			if (smap[e.first] < e.second) return false;	
		}
		return true;
	}
    string minWindow(string s, string t) {
	unordered_map<char, int> tmap, smap;	
	for (auto &e : t) ++tmap[e];

	int pos = -1, min_len = INT_MAX, slen = s.size(), tlen = t.size();
	for (int left = 0, right = 0; right < slen; ++right) {
		++smap[s[right]];
		while (IsCover(smap, tmap)) {
			if (right - left + 1 < min_len) pos = left, min_len = right - left + 1;		
			--smap[s[left]];
			++left;
		}	
	}
	if (pos < 0) return "";		
	else return s.substr(pos, min_len);
    }
};
*/

/*
// solution 2: 滑动窗口(2)
class Solution {
public:
    string minWindow(string s, string t) {
	unordered_map<char, int> tmap, smap;	
	for (auto &e : t) ++tmap[e];

	int pos = -1, min_len = INT_MAX, slen = s.size(), tlen = t.size(), amount = 0;
	for (int left = 0, right = 0; right < slen; ++right) {
		if (smap[s[right]]++ < tmap[s[right]]) ++amount;
		while (amount == tlen) {
			if (right - left + 1 < min_len) pos = left, min_len = right - left + 1;	
			if (smap[s[left]]-- <= tmap[s[left]]) --amount;
			++left;
		}	
	}
	if (pos < 0) return "";		
	else return s.substr(pos, min_len);
    }
};

// solution 2: 滑动窗口(2) : 更换amount表达意思， amount 表示 还剩余多少 字符串的字符没有被包含, 该解法中可以省略掉一个smap结构空间
class Solution {
public:
    string minWindow(string s, string t) {
        unordered_map<char, int> tmap;
        for (auto &e : t) ++tmap[e];

        int pos = -1, min_len = INT_MAX, slen = s.size(), amount = t.size();
        for (int left = 0, right = 0; right < slen; ++right) {
                if (tmap[s[right]]-- > 0) --amount;
                while (!amount) {
                        if (right - left + 1 < min_len) pos = left, min_len = right - left + 1;
                        if (tmap[s[left]]++ >= 0) ++amount;
                        ++left;
                }
        }
        if (pos < 0) return "";
        else return s.substr(pos, min_len);
    }
};
*/


// solution 2: 滑动窗口(2) : 更换amount表达意思， amount 表示 还剩余多少 字符串的字符没有被包含, 该解法中可以省略掉一个smap结构空间
//		使用vector<int> tmap(128) 来替代unordered_map
class Solution {
public:
    string minWindow(string s, string t) {
	vector<int> tmap(128, 0);
        for (auto &e : t) ++tmap[e];
        int pos = -1, min_len = INT_MAX, slen = s.size(), amount = t.size();
        for (int left = 0, right = 0; right < slen; ++right) {
                if (tmap[s[right]]-- > 0) --amount;
                while (!amount) {
                        if (right - left + 1 < min_len) pos = left, min_len = right - left + 1;
                        if (tmap[s[left]]++ >= 0) ++amount;
                        ++left;
                }
        }
	return pos < 0 ? "" : s.substr(pos, min_len);
    }
};






/*
// solution 3: solution 2 的对数据s预处理版本 
class Solution {
public:
    string minWindow(string s, string t) {
	int pos = -1, min_len = INT_MAX, amount = t.size();
	unordered_map<char, int> tmap;	
	for (auto &e : t) ++tmap[e];

	// 对s字符串做预处理
	vector<int> sidx;
	for (int i = 0; i < s.size(); ++i) {
		if (tmap.count(s[i])) sidx.push_back(i);
	}

	for (int left = 0, right = 0, li, ri; right < sidx.size(); ++right) {
		ri = sidx[right]; 
		if (tmap[s[ri]]-- > 0) --amount;
		while (!amount) {
			li = sidx[left];
			if (ri - li + 1 < min_len) pos = li, min_len = ri - li + 1;	
			if (tmap[s[li]]++ >= 0) ++amount;
			++left;
		}	
	}
	if (pos < 0) return "";		
	else return s.substr(pos, min_len);
    }
};
*/


int main(int argc, char *argv[]) {

	return 0;
}
