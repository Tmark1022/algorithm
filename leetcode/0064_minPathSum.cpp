/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Mon 21 Dec 2020 11:08:52 AM CST
 @ File Name	: 0064_minPathSum.cpp
 @ Description	: 64. 最小路径和 
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
	solution 1: 转化为图问题, dfs 回溯搜索, 指数级时间复杂度 O(2^N), 最大递归深度N+M-2，空间复杂度为O(N+M)

	solution 2: 转化为图问题（有向加权图），单源点加权最短路径问题，使用dijkstra算法, 顶点数为M*N，每个顶点最多有两条边, 边数e < 2*N*M
		1) 常规dijkstra算法, 每次需要在N*M的数组里边取最小值顶点为作为下一个计算顶点， 选取最小值顶点需要O(NM), 所以总时间复杂度为O(NM * NM),空间复杂度 O(NM)
		2) 因为图是无环图， 所以可以参考拓扑排序的方式， 每次选取入度为0的顶点作为下一个计算顶点， 选取顶点的时间复杂度为O(1), 所以最终时间复杂度为O(N*M + e)
		   e < 2*N*M, 所以最终时间复杂度为O(NM), 空间复杂度为O(NM)

	soluton 3: 动态规划, 状态转移方程为 f(i, j) = min(f(i-1, j), f(i, j-1)) + grid[i][j]; 最终时间复杂度为O(NM), 空间复杂度为O(NM)【可以优化为O(N)】
   */


class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
	return 0;
    }
};

int main(int argc, char *argv[]) {

	return 0;
}
