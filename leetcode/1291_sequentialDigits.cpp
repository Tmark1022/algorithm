/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Mon 13 Jul 2026 07:51:48 PM CST
 @ File Name	: 1291_sequentialDigits.cpp
 @ Description	: 1291. 顺次数 
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

// solution 1: 枚举开头数字， 然后按位数生成顺次数。 迭代实现。
class Solution {
public:
    vector<int> sequentialDigits(int low, int high) {
        vector<vector<int>> res(10);
        for (int s = 1; s < 9; ++s) {
            int val = s; 
            for (int len = 2; s+len-1 <= 9; ++len) {
                val = val*10+s+len-1;
                if (val > high) break;
                if (val < low) continue;
                res[len].push_back(val); 
            }  
        }   

        vector<int> ans;
        for (auto &arr : res) {
            if (arr.empty()) continue;
            ans.insert(ans.end(), arr.begin(), arr.end());
        }
        return ans;
    }
};


// solution 1: 枚举开头数字， 然后按位数生成顺次数。 递归实现
class Solution {
public:
    vector<int> sequentialDigits(int low, int high) {
        vector<vector<int>> res(10);
        for (int digit = 0; digit < 9; ++digit)
            backtracking(low, high, 0, digit, 0, res);

        vector<int> ans;
        for (int i = 2; i < res.size(); ++i) {
            if(res[i].empty()) continue;
            ans.insert(ans.end(), res[i].begin(), res[i].end());
        }
        return ans;
    }


    void backtracking(int low, int high, int cnt, int lastDigit, int tmp, vector<vector<int>> &res) {
        if (tmp > high) return ;
        if (low <= tmp) res[cnt].push_back(tmp);
        if (lastDigit == 9) return ;
        backtracking(low, high, cnt+1, lastDigit+1, tmp*10+lastDigit+1, res);
    }

};






int main(int argc, char *argv[]) {

	return 0;
}
