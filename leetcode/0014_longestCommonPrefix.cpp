/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Thu 21 May 2026 01:48:55 PM CST
 @ File Name	: 0014_longestCommonPrefix.cpp
 @ Description	: 14. 最长公共前缀 
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
	solution 1: 遍历扫描; O(mn), m 为字符串长度
	solution 2: divide & conquer; O(mn)
*/

/*
// solution 1: 遍历扫描
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) { 
        for (int i = 0; i < strs[0].size(); ++i) {
            for (int j = 1; j < strs.size(); ++j) {
                if (i >= strs[j].size() || strs[j][i] != strs[0][i]) return strs[0].substr(0, i);
            }
        }
        return strs.front();
    }
};
*/

// solution 2: divide & conquer
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        return help(strs, 0, strs.size() - 1);
    }

    string help(vector<string> &strs, int l, int r) {
        if (l == r) return strs[l];

        auto mid = l + (r - l) / 2;
        auto sl = help(strs, l, mid); 
        auto sr = help(strs, mid + 1, r); 

        int i = 0; 
        while (i < sl.size() && i < sr.size() && sl[i] == sr[i]) ++i;
        return sl.substr(0, i);
    }
};

int main(int argc, char *argv[]) {

	return 0;
}
