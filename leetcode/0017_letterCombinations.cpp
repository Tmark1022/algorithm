/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Fri 20 Nov 2020 11:30:26 AM CST
 @ File Name	: 0017_letterCombinations.cpp
 @ Description	: 17. 电话号码的字母组合
 ************************************************************************/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <deque>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::deque;

/*
// solution 1: 回溯
class Solution {
public:
	void BackTracking(int idx, string& digits, const vector<string>& map, string &tmp, vector<string>& ans) {
		if (idx == digits.size()) {
			ans.push_back(tmp);
			return ;
		}

		const string &letter = map[digits[idx] - '0'];
		for(auto &e : letter) {
			tmp.push_back(e);	
			BackTracking(idx+1, digits, map, tmp, ans);
			tmp.pop_back();;	
		}
	}

    vector<string> letterCombinations(string digits) {
	if (!digits.size()) return {};
	const vector<string> map = {"0", "1", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
	string tmp;	
	vector<string> ans;
	BackTracking(0, digits, map, tmp,ans);	
	return ans;
    }
};
*/

/*
// solution 2: f(n) = for_each(f(n-1)) append(digits[n]); 递归实现
class Solution {
public:
	vector<string> recur(int n, string& digits, const vector<string>& map) {
		if (n < 0) {
			return {""};
		}

		vector<string> last = recur(n-1, digits, map);  	
		vector<string> ans;
		for (auto &str : last)
			for (auto &e : map[digits[n] - '0']) 
				ans.push_back(str+e);

		return ans;
	}

    vector<string> letterCombinations(string digits) {
	if (!digits.size()) return {};
	const vector<string> map = {"0", "1", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
	return recur(digits.size() - 1, digits, map); 
    }
};
*/

/*
// solution 2: f(n) = for_each(f(n-1)) append(digits[n]); 递归实现
class Solution {
public:
	vector<string> recur(int n, string& digits, const vector<string>& map) {
		if (n < 0) {
			return {""};
		}

		vector<string> last = recur(n-1, digits, map);  	
		vector<string> ans;
		for (auto &str : last)
			for (auto &e : map[digits[n] - '0']) 
				ans.push_back(str+e);

		return ans;
	}

    vector<string> letterCombinations(string digits) {
	if (!digits.size()) return {};
	const vector<string> map = {"0", "1", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
	return recur(digits.size() - 1, digits, map); 
    }
};
*/

// solution 2: f(n) = for_each(f(n-1)) append(digits[n]); 迭代实现， 其实可以简单地使用一个队列来模拟这个过程
class Solution {
public:
    vector<string> letterCombinations(string digits) {
	if (!digits.size()) return {};
	const vector<string> map = {"0", "1", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
	deque<string> que = {""};	
	while (que.front().size() != digits.size()) {
		string tmp = que.front();
		que.pop_front();	
		for (auto &e : map[digits[tmp.size()] - '0']) 
			que.push_back(tmp+e);
	}	
	return vector<string>(que.begin(), que.end());
    }
};

int main(int argc, char *argv[]) {

	return 0;
}
