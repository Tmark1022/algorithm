/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Thu 14 Jan 2021 07:32:59 PM CST
 @ File Name	: 0363_maxSumSubmatrix.cpp
 @ Description	: 363. 矩形区域不超过 K 的最大数值和
 ************************************************************************/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
#include <deque>
#include <unordered_map>
#include <unordered_set>
#include <set>

using namespace std;

/*
 *
 *
	这道题涉及很多知识点， 利用这些知识点可以逐步优化代码;	
	涉及到的知识点有:
		1) dp 算法设计方法
		2) 最大子序和
		3) 前缀和
		4) 二分方法（搜索树的查找）

	solution 1: brute force; 枚举起点(row1, col1)和终点(row2, col2), 然后暴力求范围和， 时间复杂度为O(MN * MN * MN)
	solution 2: dp; 枚举起点(row1, col1)和终点(row2, col2), 使用dp方法来求范围和， 时间复杂度为O(MN * MN)
			设 dp[row1][col1][row2][col2] 为 (row1, col1), (row2, col2) 的区域和
			存在如下状态转移方程:	
				dp[row1][col1][row2][col2] = \
					dp[row1][col1][row2-1][col2] + dp[row1][col1][row2][col2-1] - dp[row1][col1][row2-1][col2-1] + matrix[row2][col2]	

			又因为在状态转移方程中新起点与之前的旧起点 dp 值都没有任何关系, 所以我们可以在空间上优化这两维空间
			时间复杂度O(MN * MN), 空间复杂度O(MN)

	solution 2.1: 先O(MN)时间复杂度求二维矩阵前缀和，然后枚举起点(row1, col1)和终点(row2, col2), 然后利用前缀和O(1)求范围矩阵的和，最终时间复杂度为O(MN * MN)	
	
	solution 3: 固定左右边界的求和方式 (一); 枚举起始列 与 终止列， 快速求取row_sum数组; 暴力利用row_sum数组来进行区域求和.
			时间复杂度O(NN * MM), 空间复杂度O(M)

	solution 4: 固定左右边界的求和方式 (二); 枚举起始列 与 终止列， 快速求取row_sum数组; 利用最大子序和进行剪枝， 不行再暴力利用row_sum数组来进行区域求和
			时间复杂度O(NN * MM)【不过有许多测试用例都被剪枝了， 被剪枝的部分的时间复杂度是 O(NN * M)】, 空间复杂度O(M)

	solution 5: 固定左右边界的求和方式 (三); 枚举起始列 与 终止列， 快速求取row_sum数组; 计算row_sum数组的前缀和【参考leetcode 303/304 前缀和妙用】, 
			结合二分法【这里利用的其实是BST的二分查找特性， 找到最接近的结果; 这里使用set（红黑树实现）存储前缀和， lower_bound调用二分查询】快速找到最靠近结果k的区域和
			时间复杂度O(NN * MlogM), 空间复杂度O(M)

	solution 6 【最佳】: 固定左右边界的求和方式 (四); 参考solution 4的优化思路， 在solution 5的基础上进行最大子序和剪枝优化
   */


/*
// solution 2:dp
class Solution {
public:
    int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
        if (!matrix.size() || !matrix[0].size()) return 0;
        int m = matrix.size(), n = matrix[0].size(), ans = INT_MIN;
        for (int r1 = 1; r1 <= m; ++r1) {                                       // 矩阵下标从 开始
                for (int c1 = 1; c1 <= n; ++c1) {
                        vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
                        for (int r2 = r1; r2 <= m; ++r2) {
                                for (int c2 = c1; c2 <= n; ++c2) {
                                        dp[r2][c2] = dp[r2-1][c2] + dp[r2][c2-1] - dp[r2-1][c2-1] + matrix[r2-1][c2-1];
                                        if (dp[r2][c2] <= k && dp[r2][c2] > ans) ans = dp[r2][c2];
                                }
                        }
                }
        }
        return ans;
    }
};

// solution 3:
class Solution {
public:
    int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
        if (!matrix.size() || !matrix[0].size()) return 0;
        int m = matrix.size(), n = matrix[0].size(), ans = INT_MIN;

	for (int c1 = 0; c1 < n; ++c1) {
		vector<int> row_sum(m, 0);
		for (int c2 = c1; c2 < n; ++c2) {		
			// 计算row_sum
			for (int r = 0; r < m; ++r) row_sum[r] += matrix[r][c2];
			ans = max(ans, maxSumSubmatrixHelper(row_sum, k));
		}
        }
        return ans;
    }

    int maxSumSubmatrixHelper(vector<int> &row_sum, int k) {
	// 利用row_sum 暴力求解区域和 
	int ans = INT_MIN, m = row_sum.size();
	for (int r1 = 0; r1 < m; ++r1) {
		for (int r2 = r1, sum = 0; r2 < m; ++r2) {
			sum += row_sum[r2];
			if (sum <= k && sum > ans) ans = sum;
		}
	}			
	return ans;
    }
};

// solution 4:
class Solution {
public:
    int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
        if (!matrix.size() || !matrix[0].size()) return 0;
        int m = matrix.size(), n = matrix[0].size(), ans = INT_MIN;

	for (int c1 = 0; c1 < n; ++c1) {
		vector<int> row_sum(m, 0);
		for (int c2 = c1; c2 < n; ++c2) {		
			// 计算row_sum 并 计算最大子序和
			for (int r = 0, dp = 0; r < m; ++r) {
				row_sum[r] += matrix[r][c2];
			}
			ans = max(ans, maxSumSubmatrixHelper(row_sum, k));
		}
        }
        return ans;
    }
    int maxSumSubmatrixHelper(vector<int> &row_sum, int k) {
	// 计算最大子序和
	int max_sub_sum = INT_MIN, m = row_sum.size();	
	for (int r = 0, dp = 0; r < m; ++r) {
		if (dp < 0) dp = row_sum[r];
		else dp += row_sum[r];
		max_sub_sum = max(max_sub_sum, dp);
	}

	// 最大子序和剪枝 
	if (max_sub_sum <= k) return max_sub_sum; 

	// 利用row_sum 暴力求解区域和 
	int ans = INT_MIN;
	for (int r1 = 0; r1 < m; ++r1) {
		for (int r2 = r1, sum = 0; r2 < m; ++r2) {
			sum += row_sum[r2];
			if (sum <= k && sum > ans) ans = sum;
		}
	}			
	return ans;
    }
};
*/

// solution 5:
class Solution {
public:
    int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
        if (!matrix.size() || !matrix[0].size()) return 0;
        int m = matrix.size(), n = matrix[0].size(), ans = INT_MIN;

	for (int c1 = 0; c1 < n; ++c1) {
		vector<int> row_sum(m, 0);
		for (int c2 = c1; c2 < n; ++c2) {		
			// 计算row_sum
			for (int r = 0; r < m; ++r) row_sum[r] += matrix[r][c2];
			ans = max(ans, maxSumSubmatrixHelper(row_sum, k));
		}
        }
        return ans;
    }

    int maxSumSubmatrixHelper(vector<int> &row_sum, int k) {
	int max_sub_sum = INT_MIN, m = row_sum.size();	
	// 计算row_sum 并 计算最大子序和
	for (int r = 0, dp = 0; r < m; ++r) {
		if (dp < 0) dp = row_sum[r];
		else dp += row_sum[r];
		max_sub_sum = max(max_sub_sum, dp);
	}

	// 最大子序和剪枝 
	if (max_sub_sum <= k) return max_sub_sum; 

	int ans = INT_MIN;
	set<int> prefix = {0};		
	for (int r = 0, sum = 0; r < m; ++r) {
		sum += row_sum[r];
		auto it = prefix.lower_bound(sum - k);
		if (it != prefix.end()) ans = max(ans, sum - *it); 
		prefix.insert(sum);
	}
	return ans;
    }
};


int main(int argc, char *argv[]) {

	return 0;
}
