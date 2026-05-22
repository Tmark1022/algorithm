/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Fri 22 May 2026 02:50:11 PM CST
 @ File Name	: 0541_reverseStr.cpp
 @ Description	: 541. 反转字符串 II
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

// solution 1: 自己实现reverse (双指针)
class Solution {
public:
    string reverseStr(string s, int k) {
        for (int i = 0, len = s.size(); i < len; i += k*2) {
            help(s, i, min(len - 1, i + k - 1));
        }
        return s;
    }

    void help(string &s, int l, int r) {
        while (l < r) {
            swap(s[l++], s[r--]);
        }
    } 
};



/*
// solution 2: 库函数
class Solution {
public:
    string reverseStr(string s, int k) {
        for (int i = 0, len = s.size(); i < len; i += 2*k) {
            reverse(s.begin() + i, s.begin() + min(i+k, len));
        }
        return s;
    }
};
*/



int main(int argc, char *argv[]) {

	return 0;
}
