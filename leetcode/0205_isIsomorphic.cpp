/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Thu 11 Jun 2026 07:57:16 PM CST
 @ File Name	: 0205_isIsomorphic.cpp
 @ Description	: 205. 同构字符串
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

// solution 1: hashtable; time complexity O(N), space complexity O(N)
class Solution {
public:
    bool isIsomorphic(string s, string t) {
        unordered_map<char, char> mm, mmr;
        for (int i = 0; i < s.size(); ++i) {
            if (mm.count(s[i])) {
                if (mm[s[i]] != t[i]) return false;
            } else {
                if (mmr.count(t[i])) return false;      // 目标已经被之前的字符映射过了
                mm[s[i]] = t[i], mmr[t[i]] = s[i]; 
            }
        } 
        return true;
    }
};


int main(int argc, char *argv[]) {

	return 0;
}
