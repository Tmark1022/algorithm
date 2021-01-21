/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Thu 14 Jan 2021 11:15:48 AM CST
 @ File Name	: 0304_sumRegion.cpp
 @ Description	: 304. 二维区域和检索 - 矩阵不可变 
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
 *	设 M 是行数， N是列数
	solution 1: brute force; 每次查询直接求(row1, col1), (row2, col2) 的和; 创建对象O(1), 查询O(MN), 空间O(1)
	solution 2: 缓存; 遍历计算所有可能的(row1, col1), (row2, col2) 组合的区域和， 使用四维数组 dp[row1][col1][row2][col2] 保存起来
			确定起点(row1, col1)和终点 (row2, col2) 需要时间复杂度O(MN * MN), 计算(row1, col1), (row2, col2)的区域和方法有:
				1) 朴素的计算方法 : 遍历计算区域和 O(MN), 那么单纯构造四维缓存数组的时间复杂度为O(MN * MN * MN)
				2) 动态规划方法: dp[row1][col1][row2][col2] = \
					dp[row1][col1][row2][col2-1] + dp[row1][col1][row2-1][col2] - dp[row1][col1][row2-1][col2-1] + matrix[row2][col2]
					那么单纯构造四维缓存数组的时间复杂度为O(MN * MN)
			故 创建对象最佳O(MN*MN), 查询O(1), 空间(MN*MN)
	
	solution 3: 行缓存, 参考 leetcode 303, 创建M 个 大小为N的一维前缀和数组; 创建对象O(MN), 查询O(M), 空间O(MN)

	solution 4: 缓存, 利用二维前缀和数组， 计算前缀和使用dp方法; 参考上面 (row1, col1), (row2, col2)的区域和为 dp[row1][col1][row2][col2] = \
					dp[row1][col1][row2][col2-1] + dp[row1][col1][row2-1][col2] - dp[row1][col1][row2-1][col2-1] + matrix[row2][col2]

				我们现在固定起点就是(0, 0), dp[i][j] 表示 (0,0), (i,j) 的区域和, 存在如下状态转移方程:
					dp[i][j] = dp[i-1][j] + dp[i][j-1] - dp[i-1][j-1] + matrix[i][j]


				当我们得出dp数组后， 那么计算(row1, col1), (row2, col2)的区域和等价于如下方程:
					res = dp[row2][col2] - dp[row1-1][col2] - dp[row2][col1-1] + dp[row1-1][col1-1];
		
			故 创建对象【构造dp数组】O(MN), 查询O(1), 空间(MN)
   */


/*
// solution 3: 行缓存
class NumMatrix {
public:
	vector<vector<int>> dp;
    NumMatrix(vector<vector<int>>& matrix) {
	if (!matrix.size() || !matrix[0].size()) return ;
	int m = matrix.size(), n = matrix[0].size();
	dp = vector<vector<int>>(m, vector<int>(n+1, 0));	
	for (int i = 0; i < m; ++i) {
		for (int j = 1; j <= n; ++j) {
			dp[i][j] = dp[i][j-1] + matrix[i][j-1];
		}
	} 
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {	
	int ans = 0; 	
	for (int i = row1; i <= row2; ++i) {
		ans += dp[i][col2+1] - dp[i][col1]; 
	}	
	return ans;
    }
};
*/

// solution 3: 缓存, 利用二维前缀和数组
class NumMatrix {
public:
	vector<vector<int>> dp;
    NumMatrix(vector<vector<int>>& matrix) {
	if (!matrix.size() || !matrix[0].size()) return ;
	int m = matrix.size(), n = matrix[0].size();
	dp = vector<vector<int>>(m+1, vector<int>(n+1, 0));	
	for (int i = 1; i <= m; ++i) {
		for (int j = 1; j <= n; ++j) {
			dp[i][j] = dp[i-1][j] + dp[i][j-1] - dp[i-1][j-1] + matrix[i-1][j-1];
		}
	} 
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {	
	    return dp[row2+1][col2+1] - dp[row2+1][col1] - dp[row1][col2+1] + dp[row1][col1]; 
    }
};




int main(int argc, char *argv[]) {

	return 0;
}
