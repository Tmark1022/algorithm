/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Fri 22 May 2026 02:35:52 PM CST
 @ File Name	: 0344_reverseString.cpp
 @ Description	: 344. 反转字符串 
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

// solution 1: 双指针， O(N)
class Solution {
public:
    void reverseString(vector<char>& s) {
        for (int l = 0, r = s.size() - 1; l < r; ++l, --r) {
            swap(s[l], s[r]);
        }
    }
};

/*
// solution 2: 库函数
class Solution {
public:
    void reverseString(vector<char>& s) {
        reverse(s.begin(), s.end());
    }
};
*/



int main(int argc, char *argv[]) {

	return 0;
}
