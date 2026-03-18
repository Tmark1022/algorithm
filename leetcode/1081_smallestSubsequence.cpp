/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Wed 18 Mar 2026 10:59:52 AM CST
 @ File Name	: 1081_smallestSubsequence.cpp
 @ Description	: 1081. 不同字符的最小子序列
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
	solution 1: brute force, 子集枚举所有子序列，筛选得出每个字符都出现一次且最小。time complexity O(2^n), space complexity O(n)
	solution 2: brute force, solution 1 优化版，直接减枝得出每个字符都出现一次的子序列集合， 再判断最小。 time complexity O(2^n), space complexity O(n)
	solution 3: 单调栈; time complexity O(n), space complexity O(n)
*/

/*
// soltuion 1: brute force
class Solution {
public:
    string smallestSubsequence(string s) {
	    unordered_set<char> ss(s.begin(), s.end());
	    string res = "zz", tmp; 
	    backtracking(s, 0, tmp, res, ss);
	    return res;
    }
	
    void backtracking(const string &s, int idx, string &tmp, string &res, const unordered_set<char> &ss) {
	    if (idx == s.size()) {
		if (CheckStr(tmp, ss)) res = min(res, tmp);
		return ;
	    }
		
	    // pick
	    tmp.push_back(s[idx]); 
	    backtracking(s, idx + 1, tmp, res, ss);
	    tmp.pop_back();

	    // not pick
	    backtracking(s, idx + 1, tmp, res, ss);
    }

    bool CheckStr(const string &tmp, const unordered_set<char> &ss) {
	    unordered_set<char> tss(tmp.begin(), tmp.end());
	    return tmp.size() == tss.size() && tss.size() == ss.size();
    }
};
*/

/*
// soltuion 2: brute force优化版
class Solution {
public:
    string smallestSubsequence(string s) {
	    unordered_map<char, int> sm;
	    for (int idx = 0; idx < s.size(); ++idx) sm[s[idx]] = idx; 
	    string res = "zz", tmp; 
	    backtracking(s, 0, tmp, res, sm);
	    return res;
    }
	
    void backtracking(const string &s, int idx, string &tmp, string &res, unordered_map<char, int> &sm) {
	    if (idx == s.size()) {
		res = min(res, tmp);
		return ;
	    }

	    char ch = s[idx];
	    if (sm[ch] < 0) {
		    // already picked, do nothing
		    backtracking(s, idx + 1, tmp, res, sm); 
	    } else if (idx == sm[ch]) {
		    // the last one, must pick
		    auto tmpIdx = sm[ch];
		    sm[ch] = -1;
		    tmp.push_back(ch);
		    backtracking(s, idx + 1, tmp, res, sm);
		    tmp.pop_back();
		    sm[ch] = tmpIdx;
	    } else {
		    // not pick
		    backtracking(s, idx + 1, tmp, res, sm); 

		    // pick
		    auto tmpIdx = sm[ch];
		    sm[ch] = -1;
		    tmp.push_back(ch);
		    backtracking(s, idx + 1, tmp, res, sm);
		    tmp.pop_back();
		    sm[ch] = tmpIdx;
	    }
    }
};
*/

// soltuion 3: 单调栈
class Solution {
public:
    string smallestSubsequence(string s) {
	    unordered_map<char, int> sm;
	    unordered_set<char> visit;
	    for (int idx = 0; idx < s.size(); ++idx) sm[s[idx]] = idx; 
	    deque<char> que;
	    for (int idx = 0; idx < s.size(); ++idx) {
		    auto ch = s[idx];
		    if (visit.count(ch)) continue;		// already in queue

		    while (que.size() && que.back() > ch && idx < sm[que.back()]) {
			visit.erase(que.back());
			que.pop_back();
		    }
		    visit.insert(ch);
		    que.push_back(ch);
	    }
	    return {que.begin(), que.end()};
    }	
};



int main(int argc, char *argv[]) {

	return 0;
}
