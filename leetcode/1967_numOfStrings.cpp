/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Mon 29 Jun 2026 10:24:28 AM CST
 @ File Name	: 1967_numOfStrings.cpp
 @ Description	: 1967. 作为子字符串出现在单词中的字符串数目 
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
// solution 1: brute force; 时间复杂度O(kmn), k 是patterns的数量， m是pattern的长度， n 是word 的长度
class Solution {
public:
    int numOfStrings(vector<string>& patterns, string word) {
        int res = 0;
        for (auto &pattern : patterns) {
            for (int i = 0, j, m = pattern.size(); i+m <= word.size(); ++i) {
                for (j = 0; j < m; ++j) {
                    if (word[i+j] != pattern[j]) break;
                }
                if (j >= m) {
                    ++res;
                    break;
                }
            }
        }
        return res;
    }
};
*/

/*
// solution 1.1: brute force; 使用库函数; 时间复杂度O(kmn), k 是patterns的数量， m是pattern的长度， n 是word 的长度
class Solution {
public:
    int numOfStrings(vector<string>& patterns, string word) {
        int res = 0;
        for (auto &pattern : patterns) {
            if (word.find(pattern) != string::npos) ++res;
        }
        return res;
    }
};
*/

// solution 2: 使用rabin-karp 算法加快字符串匹配; O(kmn)

// solution 3: 使用KMP 算法加快字符串匹配; O(kl), l = m+n 


int main(int argc, char *argv[]) {

	return 0;
}
