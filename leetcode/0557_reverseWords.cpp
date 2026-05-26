/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Tue 26 May 2026 03:44:30 PM CST
 @ File Name	: 0557_reverseWords.cpp
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

// solution 1: 遍历字符串， 找到单词的边界， 然后reverse 单词
class Solution {
public:
    string reverseWords(string s) {
        for (int i = 0, j; i < s.size(); ++i) {
            if (s[i] == ' ') continue;
            j = i + 1;
            while (j < s.size() && s[j] != ' ') ++j;
            reverse(s.begin() + i, s.begin() + j);
            i = j;
        }
        return s;
    }
};



int main(int argc, char *argv[]) {

	return 0;
}
