/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Thu 28 May 2026 03:45:36 PM CST
 @ File Name	: 0680_validPalindrome.cpp
 @ Description	: 680. 验证回文串 II
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
// solution 1: 删除任意一个字符(替换成'#'表示删除)， 检测是否为合法的; O(N^2)
class Solution {
public:
    bool validPalindrome(string s) {
        // 不删除字符时
        if (isPalindrome(s)) return true;

        // 删除一个字符
        for (auto &ch : s) {
            auto tmp = ch;
            ch = '#';
            if (isPalindrome(s)) return true;
            ch = tmp;
        }
        return false;
    }

    bool isPalindrome(const string &s) {
        for (int l = 0, r = s.size() - 1; l < r; ++l, --r) {
            while (l < r && !isalpha(s[l])) ++l;
            while (l < r && !isalpha(s[r])) --r;
            if (s[l] != s[r]) return false;
        }
        return true;
    }
};
*/

// solution 2:  双指针; O(N)
// 从solution 1的解法可知， 当外围的字符都不同时， 删除内部的任意一个字符都不可能是palindrome， 故如果只能删除一个字符时， 只能从外往内遍历， 尝试删除首次遇到不同的字符对的任意一个， 都不行的话， 再往里边也不必尝试了。

class Solution {
public:
    bool validPalindrome(string s) {
        return isPalindrome(s, 0, s.size() - 1, true);
    }

    bool isPalindrome(const string &s, int l, int r, bool deleteFlag) {
        while (l < r) {
            if (s[l] == s[r]) ++l, --r;
            else {
                if (deleteFlag) return isPalindrome(s, l+1, r, false) || isPalindrome(s, l, r-1, false); 
                else return false;
            }
        }
        return true;
    }
};


int main(int argc, char *argv[]) {

	return 0;
}
