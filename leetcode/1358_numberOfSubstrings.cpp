/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Tue 30 Jun 2026 11:42:31 AM CST
 @ File Name	: 1358_numberOfSubstrings.cpp
 @ Description	: 1358. 包含所有三种字符的子字符串数目 
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
// solution 1: brute force, O(N^2)
class Solution {
public:
    int numberOfSubstrings(string s) {
        int res = 0;
        vector<int> cnt(3);
        for (int i = 0; i <= s.size() - 3; ++i) {
            cnt = {0, 0, 0};
            for (int j = i; j < s.size(); ++j) {
                ++cnt[s[j]-'a'];
                if (cnt[0] && cnt[1] && cnt[2]) ++res;
            }
        }
        return res;
    }
};
*/

/*
// solution 2: 前缀和 + 二分; O(nlogn)
//              brute force的基础上， 内层循环使用二分法进行加速【需要前缀和数组进行辅助】
class Solution {
public:
    int numberOfSubstrings(string s) {
        int res = 0, len = s.size(), pos;
        vector<vector<int>> prefix(3, vector<int>(len+1, 0));

	// construct prefix array
        for (int i = 0; i < len; ++i) {
            prefix[0][i+1] = prefix[0][i];
            prefix[1][i+1] = prefix[1][i];
            prefix[2][i+1] = prefix[2][i];
            ++prefix[s[i]-'a'][i+1];
        }

	// 枚举起点， 通过二分找到临界点
        for (int i = 0; i <= len-3; ++i) {
            pos = binarySearch(prefix, i, i, len-1);
            if (pos < 0) break;
            res += len - pos;
        }
        return res;
    }

    int binarySearch(vector<vector<int>> &prefix, int t, int l, int r) {
        if (!check(prefix, t, r)) return -1;        // 整个范围都找不到合适的子串， 后续不用跑了
        while (l < r) {
            int mid = l + (r-l) / 2;
            if (check(prefix, t, mid)) r = mid;
            else l = mid + 1;
        }
        return l;
    }

    bool check(vector<vector<int>> &prefix, int l, int r) {
        return (prefix[0][r+1] - prefix[0][l]) && (prefix[1][r+1] - prefix[1][l]) && (prefix[2][r+1] - prefix[2][l]);
    }
};
*/

// solution 3: 双指针/滑动窗口, O(N)
class Solution {
public:
    int numberOfSubstrings(string s) {
        int res = 0, len = s.size();
        vector<int> cnt(3);
        for (int i = 0, j = 0; j < len; ++j) {
            ++cnt[s[j]-'a'];
            while(cnt[0] && cnt[1] && cnt[2]) {
                res += len - j;
                --cnt[s[i++]-'a'];
            }
        }
        return res;
    }
};



int main(int argc, char *argv[]) {

	return 0;
}
