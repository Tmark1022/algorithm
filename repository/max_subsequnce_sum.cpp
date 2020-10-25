/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Wed 21 Oct 2020 02:24:25 PM CST
 @ File Name	: max_subsequnce_sum.cpp
 @ Description	: 最大子序列的和 

 【问题描述】
	有整型数组arr, 数组元素有正有负，求子序列的最大和。

 【例子】
	有数组 -2, 1, 5, -10, 4, 3, -7, 6

	最大子序列和为 7

	有数组 -1, 100, -5, -5, -5, -5, 100, 2

	最大子序列和为182

	参考leetcode 53. 最大子序和 解答


 ************************************************************************/

#include <iostream>

using std::cin;
using std::cout;
using std::endl;


/***************************************************
* 解法一 : 穷举 
***************************************************/

/***************************************************
* 解法二 : 穷举 (优化求和过程)
***************************************************/

/***************************************************
* 解法三 : 分治 
*
* 把大数组分成两个小的数组， 最大子序列和对应的最大子序列的所在有三种情况：
*	1）完全包含于左边的数组中
*	2）完全包含于右边的数组中
*	3）划分小数组时刚好分割了
*
* 那么在一个大数组中求取子序列的最大和 就 变成求这三种情况的最大子序列和的最大值
* 求1）和 2）的最大子序列和可以调用原本的递归函数。
* 3）情况中，最大子序列和  = max(左边小数组最大和， 0) + max(右边小数组最大和， 0)
***************************************************/


/***************************************************
* 解法四 : 动态规划 
*
* 递推公式， 对于子序列尾元素下标为i的子序列和sum[i]， 有sum[i] = max(sum[i -1] + arr[i], arr[i])
* sum[i] means the maximum subarray ending with arr[i];
*
* 而在这个例子中，也完全可以不用sum数组
***************************************************/

class Solution{

};

int main(int argc, char *argv[]) {
	//Solution obj = new Solution;	
	return 0;
}


