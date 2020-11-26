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
    int trap(vector<int>& height) {	
	int area = 0;	
	int len = height.size();
	if (len <= 2) return area;
		
	for (int i = 1; i < len - 1; ++i) {	
		// 左边界
		int left = i-1;				
		while (left >= 0 && height[left] <= height[i]) --left;
		if (left < 0) continue;	

		// 右边界
		int right = i+1;
		while (right < len && height[right] < height[i]) ++right; 
		if (right >= len || height[right] == height[i]) continue;
	
		// 计算area 
		int w = right - left - 1; 		
		int h = std::min(height[left], height[right]) - height[i];
		area += w*h;
	}

	return area;	
    }
};
*/

/*
// solution 2: 单调栈(递减)
class Solution {
public:
    int trap(vector<int>& height) {	
	int area = 0;	
	int len = height.size();
	if (len <= 2) return area;
	stack<int> stk;	

	for (int right = 0; right < len; ++right) {	
		// stk中两个相邻的相同高度， 因为先出栈的那个h会计算为0， 所以area加0, 后续的才会计算真实接雨水量， 不会造成重复	
		while (!stk.empty() && height[right] > height[stk.top()]) {		
			int idx = stk.top();
			stk.pop();			
			if (stk.empty()) break;
			int left = stk.top();
			
			int w = right - left - 1; 		
			int h = std::min(height[left], height[right]) - height[idx];
			area += w*h;
		}	
		stk.push(right);
	}

	return area;	
    }
};
*/

/*
// solution 3: 暴力v2
class Solution {
public:
    int trap(vector<int>& height) {	
	int area = 0;	
	int len = height.size();
	if (len <= 2) return area;
		
	for (int i = 1; i < len - 1; ++i) {	
		// left max
		int left_max = height[i];				
		for (int j = i-1; j >= 0; --j) left_max = std::max(left_max, height[j]);
		// right max
		int right_max = height[i];				
		for (int j = i+1; j < len; ++j) right_max = std::max(right_max, height[j]);

		area += std::min(left_max, right_max) - height[i];
	}
	return area;	
    }
};
*/

/*
// solution 4: dp
class Solution {
public:
    int trap(vector<int>& height) {	
	int area = 0;	
	int len = height.size();
	if (len <= 2) return area;	
	vector<int> left_max(len), right_max(len);	
	
	// left_max
	left_max[0] = height[0];	
	for (int i = 1; i < len; ++i) left_max[i] = std::max(left_max[i-1], height[i]);
	// right_max 
	right_max[len-1] = height[len-1];	
	for (int i = len-2; i >= 0; --i) right_max[i] = std::max(right_max[i+1], height[i]);
	// calc area
	for (int i = 1; i < len-1; ++i) area += std::min(left_max[i], right_max[i]) - height[i];	
	return area;	
    }
};
*/

/*
// solution 5: 双指针
class Solution {
public:
    int trap(vector<int>& height) {
        int area = 0;
        int len = height.size();
        if (len <= 2) return area;
        int left_max = 0, right_max = 0, left = 0, right = len-1;

        while (left < right) {
                if (height[left] < height[right]) {
                        left_max = std::max(left_max, height[left]);
                        area += left_max - height[left++];
                } else {
                        right_max = std::max(right_max, height[right]);
                        area += right_max - height[right--];
                }
        }
        return area;
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
