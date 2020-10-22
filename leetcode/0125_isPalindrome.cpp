/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Thu 22 Oct 2020 08:17:31 PM CST
 @ File Name	: 0125_isPalindrome.cpp
 @ Description	:  125. 验证回文串
 ************************************************************************/
#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;



class Solution {
public:

	/*
	// solution 1: filter -> reverse -> compare
	bool isPalindrome(string s) {		

		// filter 
		string tmp; 
		for (auto ch : s) {
			if (isalnum(ch)) {
				tmp += tolower(ch);
			}
		}	

		// reverse	
		string tmp2 = tmp;
		std::reverse(tmp.begin(), tmp.end());

		// compare
		return tmp == tmp2;
	}
	*/


	// solution 2: 双指针 
	bool isPalindrome(string s) {		
		//不能使用decltype(s.size()) , string::size_type 是一个无符号整型， 当s是空字符串时， s.size() - 1 不是-1
		int beg = 0, end = s.size() - 1;		

		while (beg < end) {
			while (beg < end && !isalnum(s[beg]))
				++beg;

			while (beg < end && !isalnum(s[end]))
				--end;

			if (beg < end) {
				if (tolower(s[beg]) != tolower(s[end])) 	
					return false;
			}

			++beg;
			--end;
		}
		return true;
	}


};




int main(int argc, char *argv[]) {
	Solution obj;
	cout << obj.isPalindrome("A man, a plan, a canal: Panama");
	cout << endl;
	cout << obj.isPalindrome("");
	cout << endl;
	return 0;
}
