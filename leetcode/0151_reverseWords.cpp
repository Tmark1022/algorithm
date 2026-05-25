/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Mon 25 May 2026 12:01:50 PM CST
 @ File Name	: 0151_reverseWords.cpp
 @ Description	: 
 ************************************************************************/
#include <iostream>
#include <numeric>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
#include <deque>
#include <unordered_map>
#include <unordered_set>

using namespace std;

/*
// solution 1: split + reverse + join
class Solution {
public:
    string reverseWords(string s) {
        // split
        string word;
        vector<string> words;
        for (auto &ch : s) {
            if (ch != ' ')  word += ch;
            else if (word.size()) words.push_back(word), word.clear();
        }
        if (word.size()) words.push_back(word);

        // reverse
        for (int len = words.size(), i = 0, j = len - 1; i < j; ++i, --j) swap(words[i], words[j]);

        // join
        auto fun = [](const string &init, const string &val){return init + " " + val;};
        return accumulate(words.begin() + 1, words.end(), words.front(), fun);
    }
};
*/

/*
// solution 2: 反过来扫描
class Solution {
public:
    string reverseWords(string s) {
        string res;
        int idx = s.size() - 1, count = 0;
        for (; idx >= 0; --idx) {
            if (s[idx] != ' ') ++count;
            else if (count) {
                if (res.size()) res += ' ';
                res.append(s, idx + 1, count);
                count = 0;
            }
        }

        if (count) {
            if (res.size()) res += ' ';
            res.append(s, idx + 1, count);
        }
        return res;
    }
};
*/

// solution 3：原地修改， O（1）时间复杂度
class Solution {
public:
    string reverseWords(string s) {
        reverse(s.begin(), s.end());
        int idx = 0;
        for (int b = 0, e = 0; b < s.size(); ++b) {
            if (s[b] == ' ') continue;
            if (idx != 0) s[idx++] = ' ';
            for (e = b; e < s.size() && s[e] != ' '; ++e) s[idx++] = s[e];
            reverse(s.begin() + (idx - (e - b)), s.begin() + idx);
            b = e;
        }
        s.erase(s.begin() + idx, s.end());
        return s;
    }
};


int main(int argc, char *argv[]) {

	return 0;
}
