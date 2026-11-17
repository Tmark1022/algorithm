/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Tue 17 Nov 2026 04:40:54 PM CST
 @ File Name	: 0135_candy.cpp
 @ Description	: 135. 分发糖果 
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
// solution 1: brute force; greedy + backtracking
//      NOTE: 相邻的数相等的话， 可大可小
// 时间复杂度 指数级

class Solution {
public:
    int candy(vector<int>& ratings) {
        return backtracking(ratings, 0, 0, 0);
    }

    int backtracking(vector<int> &ratings, int idx, int lastCnt, int totalCnt) {
        if (idx == ratings.size()) return totalCnt;

        int sCnt, eCnt, res;
        if (idx == 0 || ratings[idx] > ratings[idx-1]) sCnt = lastCnt + 1, eCnt = INT_MAX;
        else if (ratings[idx] == ratings[idx - 1]) sCnt = 1, eCnt = INT_MAX;
        else sCnt = 1, eCnt = lastCnt - 1;

        for (int i = sCnt; i <= eCnt; ++i) {
            res = backtracking(ratings, idx + 1, i, totalCnt + i);
            if (res) return res;
        }
        return 0;
    }
};

// solution 2: 模拟分配， 遇到向下不能分配时， 前面的连续递减梯度向上抬一级
//              O(N^2)
class Solution {
public:
    int candy(vector<int>& ratings) {
        int len = ratings.size();
        vector<int> arr(len, 1);
        for (int i = 1; i < len; ++i) {
            if (ratings[i] > ratings[i-1]) arr[i] = arr[i-1] + 1;
            else if (ratings[i] < ratings[i-1]) {
                if (arr[i-1] == 1) {
                    // 前面梯队往向上抬一级
                    for (int j = i-1; j >= 0 && ratings[j] > ratings[j+1] && arr[j] == arr[j+1]; --j) ++arr[j];
                }
            }
        }
        return accumulate(arr.begin(), arr.end(), 0);
    }
};
*/

// solution 3: 左右扫描一遍数组
class Solution {
public:
    int candy(vector<int>& ratings) {
        int len = ratings.size();
        vector<int> larr(len, 1), rarr(len, 1);
        for (int i = 1; i < len; ++i) {
            if (ratings[i] > ratings[i-1]) larr[i] = larr[i-1] + 1;
            if (ratings[len-1-i] > ratings[len-i]) rarr[len-1-i] = rarr[len-i] + 1;
        }
        int res = 0;
        for (int i = 0; i < len; ++i) {
            res += max(larr[i], rarr[i]);
        }
        return res;
    }
};

int main(int argc, char *argv[]) {

	return 0;
}
