/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Wed 11 Nov 2020 06:56:26 PM CST
 @ File Name	: 0242_isAnagram.cpp
 @ Description	: 242. 有效的字母异位词 
 ************************************************************************/
#include <iostream>
#include <string>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::string;

class Solution {
public:
	/*
	//  solution 1: 先排序， 再比较
    bool isAnagram(string s, string t) {
	if (s.size() != t.size()) {
		return false;	
	}
	
	std::sort(s.begin(), s.end());	
	std::sort(t.begin(), t.end());	
	return s == t;
    }
    */

	/*
	//  solution 2: 使用hashtable计算字符出现频次, 因为这里只会有小写的字母， 故使用26长度的数组既可以替代, 最后验证频次所有都是0
    bool isAnagram(string s, string t) {
	if (s.size() != t.size()) {
		return false;	
	}
	
	int count[26] = {0};
	for (int i = 0; i < s.size(); ++i) {
		++count[s[i] - 'a'];
		--count[t[i] - 'a'];
	}	

	for (auto elem : count) {
		if (elem) return false;
	}

	return true;	
    }
    */

	//  solution 3: 另一种使用hashtable的方法 
    bool isAnagram(string s, string t) {
	if (s.size() != t.size()) {
		return false;	
	}
	
	int count[26] = {0};
	for (auto ch : s) {
		++count[ch - 'a'];
	}	
	
	for (auto ch : t) {
		if (--count[ch - 'a'] < 0) return false;
	}	

	// 因为上边已经判断了两个字符串长度相等， 后续不需继续判断了count全为0了， 因为如果存在不同个数的字母, --count[ch - 'a'] 必定会发生小于0的情况
	return true;	
    }
};

int main(int argc, char *argv[]) {

	return 0;
}
