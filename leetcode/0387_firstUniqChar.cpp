/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Wed 20 May 2026 04:41:09 PM CST
 @ File Name	: 0387_firstUniqChar.cpp
 @ Description	: 387. 字符串中的第一个唯一字符
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

class Solution {
public:
    int firstUniqChar(string s) {
        unordered_map<char, int> mm;
        for (auto &ch : s) ++mm[ch];
        for (int i = 0; i < s.size(); ++i) {
            if (mm[s[i]] == 1) return i;
        }
        return -1;
    }
};

int main(int argc, char *argv[]) {

	return 0;
}
