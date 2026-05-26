/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Tue 26 May 2026 03:58:56 PM CST
 @ File Name	: 0917_reverseOnlyLetters.cpp
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
// solution 1: 双指针原地修改
class Solution {
public:
    string reverseOnlyLetters(string s) {
        for (int l = 0, r = s.size() - 1; l < r; ) {
            while (l < r && !isAlpha(s[l])) ++l;
            while (l < r && !isAlpha(s[r])) --r;
            swap(s[l++], s[r--]);
        }
        return s;
    }

    bool isAlpha(char ch) {
        return ('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z');
    }
};
*/

// solution 2: 使用一个辅助空间，先将所有字母字符提取出来， 然后再倒序覆盖到原来的字符串中
class Solution {
public:
    string reverseOnlyLetters(string s) {
        vector<char> letters;
        for (auto &ch : s) {
            if (!isAlpha(ch)) continue;
            letters.push_back(ch);
        }

        for (auto &ch : s) {
            if (!isAlpha(ch)) continue;
            ch = letters.back();
            letters.pop_back();
        }

        return s;
    }

    bool isAlpha(char ch) {
        return ('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z');
    }
};

int main(int argc, char *argv[]) {

	return 0;
}
