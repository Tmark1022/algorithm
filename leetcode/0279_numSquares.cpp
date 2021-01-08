/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Fri 08 Jan 2021 09:55:19 AM CST
 @ File Name	: 0279_numSquares.cpp
 @ Description	: 279. 完全平方数
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
	这个题目其实就是 leetcode 322 硬币兑换， 不同在于这个题目的coins需要自己构建， 构建的coins的时间复杂度为 n^(1/2)
		
	solution 1: dfs 回溯搜索， 组合的方式

	solution 2: dp, bottom-up 【还可以写成记忆化递归方式】

	solution 3: BFS

	solution 4: 双向 BFS 
   */

/*
// solution 1: dfs 回溯搜索 [快得一比]
class Solution {
public:
	int ans = INT_MAX; 
	void BackTracking(vector<int>& squares, int idx, int n, int step) {
		if (!n)	{
			ans = min(ans, step);
			return ;
		}

		// pruning
		if (idx < 0) return ;
		int k = n / squares[idx];	
		if (step + k >= ans) return ;
		
		// drill down
		for (; k >= 0; --k) BackTracking(squares, idx - 1, n - k * squares[idx], step + k);
	}

    int numSquares(int n) {
	vector<int> squares;	
	for(int i = 1; i*i <= n; ++i) squares.push_back(i*i);
	BackTracking(squares, squares.size() - 1, n, 0);		// square 大到小
	return ans;
    }
};

// solution 2: dp【有点慢】, 设 dp[i] 代表组成数值i需要的最小square;
//		存在如下状态转移方程:  
//			dp[i] = min{dp[i- squares[0], ], dp[i-squares[1]], .....} + 1
//
//		时间复杂度为 O(n * n^(1/2))
//			
class Solution {
public:
    int numSquares(int n) {
	vector<int> squares, dp(n+1, INT_MAX);	
	for(int i = 1; i*i <= n; ++i) squares.push_back(i*i);

	dp[0] = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j < squares.size() && squares[j] <= i; ++j) {
			dp[i] = min(dp[i], dp[i - squares[j]] + 1);		
		}
	}
	return dp[n];
    }
};

// solution 3: BFS, 转化为图论问题， 0~n 每一个值都是一个顶点， 每一个顶点都有squares.size()条边 
//		时间复杂度为O(n+e), 即为O(n + n*n^(1/2)), 空间复杂度 O(n)	
class Solution {
public:
    int numSquares(int n) {
	vector<int> squares;	
	for(int i = 1; i*i <= n; ++i) squares.push_back(i*i);

	deque<int> que = {0}; 
	vector<bool> visit(n, false);
	visit[0] = true;
	int step = 0;
	while (que.size()) {			// 每次一层
		++step;
		for (int cnt = que.size(); cnt; --cnt) {
			int cur = que.front();	
			que.pop_front();	
			for (auto &e : squares) {
				int next = cur + e;	
				if (next == n) return step;
				if (next < n && !visit[next]) {
					visit[next] = true;	
					que.push_back(next);
				}
			}		
		}
	}
	return -1;
    }
};
*/

// solution 4: 双向 BFS, 转化为图论问题， 0~n 每一个值都是一个顶点， 每一个顶点都有squares.size()条边 , 因为知道起点与终点， 所以可以使用双向BFS优化搜索
//		时间复杂度为O(n+e), 即为O(n + n*n^(1/2)), 空间复杂度 O(n)	
class Solution {
public:
    int numSquares(int n) {
	vector<int> squares;	
	for(int i = 1; i*i <= n; ++i) squares.push_back(i*i);

	unordered_set<int> set1 = {0}, set2 = {n}, *head = &set1, *tail = &set2;
	vector<bool> visit(n+1, false);
	visit[0] = true, visit[n] = true;
	int step = 0;
	bool d = true;
	while (head->size() && tail->size()) {			// 每次一层
		++step;	
		if (head->size() > tail->size()) swap(head, tail), d = !d; 

		unordered_set<int> new_set;	
		for (auto &cur : *head){
			for (auto &e : squares) {
				int next = d ? cur + e : cur - e;	
				if (tail->count(next)) return step;	
				if (0 <= next && next <= n && !visit[next]) {
					visit[next] = true;	
					new_set.insert(next);
				}
			}		
		}
		*head = new_set;
	}
	return -1;
    }
};





int main(int argc, char *argv[]) {

	return 0;
}
