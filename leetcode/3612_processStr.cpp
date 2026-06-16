/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Tue 16 Jun 2026 10:41:26 AM CST
 @ File Name	: 3612_processStr.cpp
 @ Description	:  3612. 用特殊操作处理字符串 I
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


// solution 1: 按着题意模拟即可
class Solution {
public:
    string processStr(string s) {
        string res;
        for (auto ch : s) {
            if (ch == '*') op2(res);
            else if (ch == '#') op3(res);
            else if (ch == '%') op4(res);
            else op1(res, ch);
        }
        return res;
    }

    void op1(string &str, char ch) {
        str += ch;
    }

    void op2(string &str) {
        if (str.size()) str.pop_back();
    }

    void op3(string &str) {
        int len = str.size();
        for (int i = 0; i < len; ++i) {
            str += str[i];
        }
    }

    void op4(string &str) {
        if (str.empty()) return ;
        for (int l = 0, r = str.size() - 1; l < r; ++l, --r) swap(str[l], str[r]);
    }
};



int main(int argc, char *argv[]) {

	return 0;
}
