/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Wed 18 Nov 2026 03:50:29 PM CST
 @ File Name	: 0013_romanToInt.cpp
 @ Description	: 13. 罗马数字转整数 
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
    int romanToInt(string s) {
        unordered_map<string, int> mm = {{"I",1}, {"V",5}, {"IV",4}, {"IX",9},
                                        {"X",10}, {"L",50}, {"XL",40}, {"XC",90},
                                        {"C",100}, {"D",500}, {"CD",400}, {"CM",900},
                                        {"M",1000}};
        int res = 0, len = s.size();
        string tmp;
        for (int i = 0; i < s.size(); ++i) {
            tmp.clear();
            tmp.append(1, s[i]);
            if (i < len - 1) {
                if (s[i] == 'I' && (s[i+1] == 'V' || s[i+1] == 'X')) tmp.append(1, s[++i]);
                else if (s[i] == 'X' && (s[i+1] == 'L' || s[i+1] == 'C')) tmp.append(1, s[++i]);
                else if (s[i] == 'C' && (s[i+1] == 'D' || s[i+1] == 'M')) tmp.append(1, s[++i]);
            }
            res += mm[tmp];
        }
        return res;
    }
};
*/

// solution 1: 模拟
class Solution {
public:
    int romanToInt(string s) {
        unordered_map<char, int> mm = {{'I',1}, {'V',5}, {'X',10}, {'L',50}, {'C',100}, {'D',500},{'M',1000}};
        int res = 0, len = s.size(), val;
        for (int i = 0; i < s.size(); ++i) {
            val = mm[s[i]];
            if (i < len - 1 && val < mm[s[i+1]]) res -= val;
            else res += val;
        }
        return res;
    }
};


int main(int argc, char *argv[]) {

	return 0;
}
