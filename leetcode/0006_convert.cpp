/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Tue 24 Nov 2026 03:10:37 PM CST
 @ File Name	: 0006_convert.cpp
 @ Description	: 6. Z 字形变换 
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
// solution 1: 模拟
class Solution {
public:
    string convert(string s, int numRows) {
        if (numRows == 1) return s;
        string tmp(numRows, ' ');
        bool direct = false;
        int idx = 0;
        vector<string> arr;
        for (auto &ch : s) {
            if (direct) {
                arr.back()[idx++] = ch;
                if (idx == numRows) direct = false, idx = numRows-2;
            } else {
                arr.push_back(tmp);
                arr.back()[idx--] = ch;
                if (idx < 0) direct = true, idx = 1;
            }
        }

        string res;
        for (int j = 0; j < numRows; ++j) {
            for (string &str : arr) {
                if (str[j] == ' ') continue;
                res += str[j];
            }
        }
        return res;
    }
};
*/

/*
// soluiton 1.1: 模拟
class Solution {
public:
    string convert(string s, int numRows) {
        if (numRows == 1) return s;
        vector<string> res(numRows);
        int idx = 0;
        bool direct = true;
        for (auto &ch : s) {
            if (direct) {
                res[idx++].push_back(ch);
                if (idx == numRows) direct = false, idx = numRows - 2;
            } else {
                res[idx--].push_back(ch);
                if (idx < 0) direct = true, idx = 1;
            }
        }
        return accumulate(res.begin(), res.end(), string(""));
    }
};
*/

// solution 2: 总结规律
class Solution {
public:
    string convert(string s, int numRows) {
        if (numRows == 1) return s;

        int len = s.size(), diff = 2*numRows-2;
        string res(len,'\0');
        for (int i = 0, k = 0; i < min(len, numRows); ++i) {
            int interDiff = (diff - i * 2) % diff;
            for (int j = i; j < len; j+=diff) {
                res[k++] = s[j];
                if (interDiff && j + interDiff < len) res[k++] = s[j+interDiff];
            }
        }

        return res;
    }
};


int main(int argc, char *argv[]) {

	return 0;
}
