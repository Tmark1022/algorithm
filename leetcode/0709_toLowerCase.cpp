/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Tue 19 May 2026 10:51:19 AM CST
 @ File Name	: 0709_toLowerCase.cpp
 @ Description	: 709. 转换成小写字母
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
    string toLowerCase(string s) {
        for (auto &c : s) {
           c = tolower(c); 
        }
        return s;
    }
};

int main(int argc, char *argv[]) {

	return 0;
}
