/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Thu 19 Nov 2026 11:38:31 AM CST
 @ File Name	: 0012_intToRoman.cpp
 @ Description	: 12. 整数转罗马数字 
 ************************************************************************/
#include <iostream>
#include <numeric>
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
    string intToRoman(int num) {
        // 位数索引数据
        unordered_map<int, vector<string>> mm = {{0, {"I", "V", "IV", "IX"}},
                                            {1, {"X", "L", "XL", "XC"}},
                                            {2, {"C", "D", "CD", "CM"}},
                                            {3, {"M"}}};

        vector<string> arr;
        while (num) {
            int val = num % 10;
            num /= 10;
            string tmp;
            auto &signArr = mm[arr.size()];
            while (val) {
                if (val == 4) tmp += signArr[2], val = 0;
                else if (val == 9) tmp += signArr[3], val = 0;
                else if (val >= 5) tmp += signArr[1], val -= 5;
                else tmp += signArr[0], val -= 1;
            }
            arr.push_back(tmp);
        }

        return accumulate(arr.rbegin(), arr.rend(), string(""));
    }
};
*/

// solution 1: 模拟
class Solution {
public:
    string intToRoman(int num) {
        vector<pair<int, string>> arr = {
            {1000, "M"},
            {900, "CM"},
            {500, "D"},
            {400, "CD"},
            {100, "C"},
            {90, "XC"},
            {50, "L"},
            {40, "XL"},
            {10, "X"},
            {9, "IX"},
            {5, "V"},
            {4, "IV"},
            {1, "I"},
        };

        string res;
        for (auto &p : arr) {
            while (num >= p.first) {
                res += p.second;
                num -= p.first;
            }
        }
        return res;
    }
};

int main(int argc, char *argv[]) {

	return 0;
}
