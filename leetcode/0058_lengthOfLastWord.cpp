/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Tue 19 May 2026 11:03:55 AM CST
 @ File Name	: 0058_lengthOfLastWord.cpp
 @ Description	: 58. 最后一个单词的长度 
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
    int lengthOfLastWord(string s) {
        int res = 0, flag = 0;
        for (auto it = s.rbegin(); it != s.rend(); ++it) {
            if (*it != ' ') {
                ++res;
                flag = 1;
            } else if (flag) break;
        }
        return res;
    }
};

int main(int argc, char *argv[]) {

	return 0;
}
