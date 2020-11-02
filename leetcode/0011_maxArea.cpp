/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Mon 02 Nov 2020 08:31:40 PM CST
 @ File Name	: 0011_maxArea.cpp
 @ Description	: 11. 盛最多水的容器 
 ************************************************************************/
#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>

using std::cin;
using std::cout;
using std::endl;
using std::vector;


class Solution {
public:
	/*	
	// solution 1: 暴力, 遍历所有可能的left bar 和 right bar
	int maxArea(vector<int>& height) {
		int len = height.size();
		int max = 0;
		for (int i = 0; i < len - 1; ++i) {
			for (int j = i + 1; j < len; ++j) {
				max = std::max(max, (j - i) * std::min(height[i], height[j]));			
			}
		}
		return max;
    	}
	*/


	// solution 2: 双指针， 左右夹逼, 缩减搜索空间， 减少问题规模
	// 每次取最左i和最右j指针， 有height[i] < height[j], 那么有area = (j - i) * min(height[i], height[j]); 
	// 计算完这个area后， 我们就需要考虑如何缩减问题规模了； 现在有左右指针， 如果固定小的一边， 如在这里就是固定i， 将值大的右指针j往中间移动， 那么对于之后任意构成的容器， 因为高度最大就是i的高度, 但是因为宽度的缩减， 所以构成的容器永远小于第一次计算的area， 所以对于固定i的情况[固定小边]可以完全排除【因为后续不可能有固定i边还能找到比最先计算的area要大的容器了】, 将问题规模减1
	//
	// 于是， 问题规模就从 i -> j中最大的容器 缩小为 i + i -> j 中计算最大的容易， 以此类推， 将问题一直缩小， 最后就得到最后解决办法
	// 思路参考：https://leetcode-cn.com/problems/container-with-most-water/solution/on-shuang-zhi-zhen-jie-fa-li-jie-zheng-que-xing-tu/ 
	int maxArea(vector<int>& height) {
		int left = 0, right = height.size() - 1, max = 0, h;		
		while (left < right) {
			max = std::max(max, (right - left) * std::min(height[left], height[right]));	
			if (height[left] < height[right]) ++left;
			else --right;
		}
		return max;
    	}

};

int main(int argc, char *argv[]) {

	return 0;
}
