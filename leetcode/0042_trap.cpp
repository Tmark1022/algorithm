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

solutin 1: 暴力，枚举每一根柱子， 找出其左右边界(比当前柱子高的柱子), 需要做如下三个特殊处理
		1) 没有找到左边界, 跳过该柱子
     		2) 没有找到右边界, 跳过该柱子
     		3) 在寻找右边界的过程中,  在右边遇到柱子高度相等的柱子, 跳过该柱子 【单单计算后续相等高度柱子的接到雨水即可， 不然会重复计算】

solution 2: 单调栈(单调递减栈)
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





int main(int argc, char *argv[]) {

	return 0;
}
