/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Tue 19 Jan 2021 03:17:20 PM CST
 @ File Name	: 0551_checkRecord.cpp
 @ Description	: 551. 学生出勤记录 I 
 ************************************************************************/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
#include <deque>
#include <unordered_map>
#include <unordered_set>
#include <regex>

using namespace std;

/*
// soluiton 1: 使用标准库
class Solution {
public:
    bool checkRecord(string s) {
	return std::count(s.begin(), s.end(), 'A') <= 1 && s.find("LLL") == string::npos;   	
    }
};

// soluiton 2: 一遍循环 
class Solution {
public:
    bool checkRecord(string s) {
	int acnt = 0, lcnt = 0;
	for (int i = 0; i < s.size() && acnt <= 1 && lcnt <= 2; ++i) {
		if (s[i] == 'L') ++lcnt; 
		else {
			lcnt = 0;
			if (s[i] == 'A') ++acnt;
		}
	}
	return acnt <= 1 && lcnt <= 2;
    }
};
*/

// soluton 3: 正则表达式
class Solution {
public:
    bool checkRecord(string s) {
	return !std::regex_match(s, std::regex(".*(A.*A|LLL).*"));
    }
};


int main(int argc, char *argv[]) {

	return 0;
}
