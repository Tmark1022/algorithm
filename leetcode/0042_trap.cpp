/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Thu 26 Nov 2020 11:54:03 AM CST
 @ File Name	: 0042_trap.cpp
 @ Description	: 42. 接雨水 
 ************************************************************************/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stack>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::stack;

/*

求面积思路:
	1、对于每一根柱子, 找其左右边界(比该柱子高),  当前柱子产生的area = (右边界 - 左边界 - 1) * [min(左边界高, 右边界高) - 当前柱子高]; 该方法需要考虑排除相同的左右边界内相同高度的柱子面积重复问题。
	2、对于每一根柱子, 找其左边最高的柱子left_max和左边最高的柱子right_max， 那么该柱子（宽度为1）能储存到的积水面积area = min(left_max, right_max) - 当前柱子高 


解决方法:
solutin 1: 暴力 v1【面积思路1】，枚举每一根柱子， 找出其左右边界(比当前柱子高的柱子), 需要做如下三个特殊处理
		1) 没有找到左边界, 跳过该柱子
     		2) 没有找到右边界, 跳过该柱子
     		3) 在寻找右边界的过程中,  在右边遇到柱子高度相等的柱子, 跳过该柱子 【单单计算后续相等高度柱子的接到雨水即可， 不然会重复计算】

solution 2: 单调栈(单调递减栈)【面积思路1】

solution 3: 暴力 v2【面积思路2】 

solution 4: dp, 空间换时间【面积思路2】， 预先求出left_max数组和right_max数组

solution 5: 双指针左右夹逼【面积思路2】， solution 4的优化版; 
		每次移动柱高小的那一边，那么不移动的指针指向的柱子总是当时遇到的所有柱子里边最高的; 
		那么对于当前要移动的柱子， 其边界的小值一定是其指针之前移动经过的所有柱子的最大值。

		例如 当前比较left 和 right, 如果left 小于right， 那么right就是当前移动经过的所有柱子里边的最大值, 能够接收雨水量的左右边界的较小值(那根柱子)绝对不可能是right, 绝对在当前left柱子的左边存在比right柱子高度小的柱子， 其成为当前left柱子能够接收雨水量的边界; 

		// 具体实现中其实left_max 和 right_max 能仅仅使用一个level来替代，这里的level其实就是指代第二大的值， level所指代的那个柱子一定处于当前最大的柱子的对面, 为了可读性， 这里的实现中还是使用left_man 和 right_max


   */


/*
// solution 1: 暴力
class Solution {
public:
    // solution 1: 面积思路一, 暴力法; 找左右边界时， 需要排除同样高度的情况（同样高度只计算一遍）
    int trap(vector<int>& height) {
        int res = 0, left, right;
        for (int i = 1; i < height.size() - 1; ++i) {
	    // 左边界
            for (left = i - 1; left >= 0 && height[left] <= height[i]; --left);
            if (left < 0) continue;

	    // 右边界
            // 这里使用height[right] < height[i], 而不是<=, 用于排除相同高度； 即前边的计算结果都为0， 只有最后一个相同高度的有效
            for (right = i + 1; right < height.size() && height[right] < height[i]; ++right); 
            if (right >= height.size()) continue;

            res += (right - left - 1) * (min(height[left], height[right]) - height[i]); 
        }
        return res;
    }
};
*/

/*
// solution 2: 单调栈(递减)
class Solution {
public:
    int trap(vector<int>& height) {
        int res = 0, idx, w, h;
        stack<int> stk;

        for (int i = 0; i < height.size(); ++i) {
            while (stk.size() && height[stk.top()] <= height[i]) {
                idx = stk.top();
                stk.pop();
                if (stk.empty()) continue;

                w = i - stk.top() - 1;
                h = min(height[stk.top()], height[i]) - height[idx];
                res += w * h;
            }
            stk.push(i);
        }
        return res;
    }
};
*/

/*
// solution 3: 暴力v2
class Solution {
public:
    // solution 3: 面积思路二； 暴力找左右最大高度(且比当前高度要高)
    int trap(vector<int>& height) {
        int res = 0, leftMax, rightMax;
        for (int i = 1; i < height.size() - 1; ++i) {
            leftMax = rightMax = height[i];
            for (int j = i - 1; j >= 0; --j) leftMax = max(leftMax, height[j]); 
            for (int j = i + 1; j < height.size(); ++j) rightMax = max(rightMax, height[j]); 
            res += min(leftMax, rightMax) - height[i];
        }
        return res;
    }
};
*/

/*
// solution 4: dp
class Solution {
public:
    // solution 4: 面积思路二; dp
    int trap(vector<int>& height) {
        int size = height.size(), res = 0;
        vector<int> left(size), right(size);

        left[0] = height[0];
        for (int i = 1; i < size; ++i) left[i] = max(left[i - 1], height[i]);
        right[size - 1] = height[size - 1];
        for (int i = size - 2; i >= 0; --i) right[i] = max(right[i + 1], height[i]);

        for (int i = 1; i < size - 1; ++i) res += min(left[i], right[i]) - height[i];
        return res;
   }
};
*/

/*
// solution 5: 双指针
class Solution {
public:
    // solution 5: 面积思路二； 双指针
    int trap(vector<int>& height) {
        int res = 0, leftMax = 0, rightMax = 0, left = 0, right = height.size() - 1;
        while (left < right) {
            if (height[left] <= height[right]) {
                leftMax = max(leftMax, height[left]);
                res += leftMax - height[left++]; 
            } else {
                rightMax = max(rightMax, height[right]);
                res += rightMax - height[right--];
            }
        } 
        return res;
    }
};
*/

// solution 5: 双指针, 简洁版
class Solution {
public:
    int trap(vector<int>& height) {
        int len = height.size();
        int area = 0, level = 0, left = 0, right = len-1;
        while (left < right) { 
                int lower = height[height[left] < height[right] ? left++ : right--];
                level = std::max(level, lower);
                area += level - lower;
        }
        return area;
    }
};


int main(int argc, char *argv[]) {

	return 0;
}
