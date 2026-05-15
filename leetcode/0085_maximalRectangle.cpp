/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Fri 15 May 2026 12:10:53 PM CST
 @ File Name	: 0085_maximalRectangle.cpp
 @ Description	: 
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


//  tips: 转换为柱状图, 然后再解决问题。

/*
	solution 1: 枚举i, j 作为矩形的右下角， 然后枚举长度， 利用柱状图获得最大的高度， 从而计算当i, j为矩形右下角时最大的面积。
		时间复杂度 O（MNN）, 空间复杂度 O（N）

	solution 2: 转换为柱状图后， 采用leetcode 84的解法来解决
	        这里转换为柱状图后， 采用单调栈的解法;
		时间复杂度 O（MN）, 空间复杂度 O（N）
*/
/*
//  tips: 转换为柱状图, 然后再解决问题。
//  solution 1: 枚举i, j 作为矩形的右下角， 然后枚举长度， 利用柱状图获得最大的高度， 从而计算当i, j为矩形右下角时最大的面积。
//  时间复杂度 O（MNN）, 空间复杂度 O（N）
class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        int m = matrix.size(), n = matrix[0].size(), res = 0;
        vector<int> height(n, 0);
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (matrix[i][j] == '1') ++height[j];
                else height[j] = 0;
                for (int k = j, h = INT_MAX; k >= 0 && h; --k) {
                    h = min(h, height[k]);
                    res = max(res, (j-k+1)*h);
                }
            }
        }
        return res;
    }
};
*/


//  tips: 转换为柱状图, 然后再解决问题。
//  solution 2: 转换为柱状图后， 采用leetcode 84的解法来解决
//                  这里转换为柱状图后， 采用单调栈的解法
class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        for (auto &vec : matrix) vec.push_back('0'); // sentinel
        int m = matrix.size(), n = matrix[0].size(), res = 0, h, l;
        vector<int> height(n, 0);
        for (int i = 0; i < m; ++i) {
            stack<int> stk;
            for (int j = 0; j < n; ++j) {
                if (matrix[i][j] == '1') ++height[j];
                else height[j] = 0;

                while (stk.size() && height[stk.top()] >= height[j]) {
                    h = height[stk.top()];
                    stk.pop();
                    l = j - 1 - (stk.size() ? stk.top() : -1);
                    res = max(res, h * l);
                }
                stk.push(j);
            }
        }
        return res;
    }
};




int main(int argc, char *argv[]) {

	return 0;
}
