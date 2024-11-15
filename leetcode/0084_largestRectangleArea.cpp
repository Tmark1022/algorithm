/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Wed 11 Nov 2020 09:48:52 AM CST
 @ File Name	: 0084_largestRectangleArea.cpp
 @ Description	: 84. 柱状图中最大的矩形
 ************************************************************************/
#include <iostream>
#include <vector>
#include <cmath>
#include <stack>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::stack;

/*
 * area = width * height;
 *
 * 故暴力可以分别 枚举width 和 height
 */


class Solution {
public:
	/*
	// solution 1 : 枚举宽度
    int largestRectangleArea(vector<int>& heights) {
	int len = heights.size();	
	int area = 0;
	for (int i = 0; i < len; ++i) {
		int height = heights[i];
		for (int j = i; j < len; ++j) {		
			int width = j - i + 1;
			height = std::min(height, heights[j]);
			area = std::max(height * width, area);
		}	
	}	

	return area;
    }
    */

	/*
	// solution 2 : 枚举高度
    int largestRectangleArea(vector<int>& heights) {
	int len = heights.size();	
	int area = 0;

	for (int i = 0; i < len; ++i) {
		// 两边拓展计算宽度
		int left = i - 1;	// left 指向左侧第一个小于下标i高度的下标, 最低到达 -1
		while (left >= 0 && heights[i] <= heights[left])  --left;      
		int right = i + 1;	// right 指向右侧第一个小于下标i高度的下标, 最高到达 len	
		while (right < len && heights[i] <= heights[right])  ++right;      	
		int width = right - left - 1;	
		area = std::max(heights[i] * width, area);
	}	

	return area;
    }
    */
	

	/*
	// solution 3 : 枚举高度, 利用单调栈快速找到左边界(最近一个比当前值小的值)
    int largestRectangleArea(vector<int>& heights) {
	int len = heights.size();	
	int area = 0;
	stack<int> stk;

	for (int i = 0; i < len; ++i) {
		while (!stk.empty() && heights[stk.top()] >= heights[i]) {
			int height = heights[stk.top()];		
			stk.pop();
			int width = stk.empty() ? i : i - stk.top() - 1;   
			area = std::max(height * width, area);	
		}
		
		stk.push(i);
	}	

	// 处理栈中剩余的， 右边界统一都是len
	while (!stk.empty()) {
		int height = heights[stk.top()];		
		stk.pop();
		int width = stk.empty() ? len : len - stk.top() - 1;   
		area = std::max(height * width, area);	
	}

	return area;
    }
    */

	/*
	// solution 3 (代码优化版， 尾后增加哨兵(sentinel), 节省掉最后的while循环): 枚举高度, 利用单调栈快速找到左边界(最近一个比当前值小的值)
    int largestRectangleArea(vector<int>& heights) {
	// 尾后增加哨兵, 因为是题目要求非负整数， 故增加哨兵-1
	heights.push_back(-1);
	int len = heights.size();	
	int area = 0;
	stack<int> stk;

	for (int i = 0; i < len; ++i) {
		while (!stk.empty() && heights[stk.top()] >= heights[i]) {
			int height = heights[stk.top()];		
			stk.pop();
			int width = stk.empty() ? i : i - stk.top() - 1;   
			area = std::max(height * width, area);	
		}
		
		stk.push(i);
	}	
	return area;
    }
    */
	
	// solution 4 : 构造数组left 和 right
	// left 数组 : 对于下标i, left[i] 代表i的左侧中最近一个比heights[i]小的值的下标
	// right 数组 : 对于下标i, right[i] 代表i的右侧中最近一个比heights[i]小的值的下标
	//
	// 那么结果就是  area = std::max(area, heights[i] * (right[i] - left[i] - 1) 
    int largestRectangleArea(vector<int>& heights) {
	int len = heights.size();	
	if (len <= 0) return 0;
	vector<int> left(len, 0), right(len, 0);

	// 构造left数组
	left[0] = -1;
	for (int i = 1; i < len; ++i) {
		// 求出最近一个比height[i]小的值的下标
		int left_idx = i - 1; 
		while (left_idx >= 0 && heights[left_idx] >= heights[i]) {
			// 快速查找到前一个比当前值小的关键
			left_idx = left[left_idx];
		}
		left[i] = left_idx;
	}

	// 构造right数组
	right[len - 1] = len;
	for (int i = len - 2; i >= 0; --i) {
		// 求出最近一个比height[i]小的值的下标
		int right_idx = i + 1; 
		while (right_idx < len && heights[right_idx] >= heights[i]) {
			// 快速查找到前一个比当前值小的关键
			right_idx = right[right_idx];
		}
		right[i] = right_idx;
	}

	int area = 0;
	for (int i = 0; i < len; ++i) {
		area = std::max(area, heights[i] * (right[i] - left[i] - 1));
	}	
	return area;
    }


    /*
	// solution 5: divide & conquer, 以高度最低的元素 划分 左子问题 和 右子问题
    int largestRectangleArea(vector<int>& heights) {
        return _largestRectangleArea(heights, 0, heights.size() - 1);
    }

    int _largestRectangleArea(vector<int>& heights, int low, int high) {
        if (low > high) {
            return 0;
        }

        int pivot = low;  
        for (int i = low + 1; i <= high; ++i) {
            if (heights[i] < heights[pivot]) pivot = i;
        } 

        return max(
            max(_largestRectangleArea(heights, low, pivot - 1), _largestRectangleArea(heights, pivot + 1, high)),
            (high - low + 1) * heights[pivot]
        );
    }
    */
     
};


int main(int argc, char *argv[]) {

	return 0;
}
