/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Tue 29 Dec 2020 09:05:30 AM CST
 @ File Name	: 0120_minimumTotal.cpp
 @ Description	: 120. 三角形最小路径和 
 ************************************************************************/
#include <ctime>
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
#include <deque>
#include <unordered_map>
#include <unordered_set>

using namespace std;

/*
	N 为三角形数组中的元素个数	

	solution 1: dfs回溯搜索, O(2^N), 空间复杂度为O(l), l为递归深度， l也是三角形的高（总行数） 
	solution 2: 因为存在负值边， 故不能直接使用dijkstra （加权图最短路径问题）算法, 可以直接使用存在负值边的最短路径算法。
			但是又因为图无环， 可以使用拓扑排序的方式获得下一个节点， 时间复杂度为 O(N), 空间复杂度为O(N) 
	solution 3: dp, 设 l 为行数， i为数组下标值; f(l, i) 代表从起点到第l行下标i的位置的最小路径和;
			状态转移方程为 f(l,i) = min(f(l-1, i-1), f(l-1, i)) + triangle[l][i]; 当 l < 0 || i < 0, f(l, i) = INT_MAX 类似triange使用二维数组作为dp table
			时间复杂度 O(N), 空间复杂度O(N)

			空间优化策略:
				(1) 使用两个一维数组, 因为状态转移方程只与上一行的数据有关，所以可以单纯使用两个一维数组作为辅助空间即可, 时间复杂度O(N), 空间复杂度O(l)
				(2) 使用一个一维数组作为记录状态， 每次遍历每一层数组时, 从右往左遍历， 那么就可以使用一维滚动数组即可； 
				(3) 如果形参triangle允许修改， 可以直接使用triangle 作为dp数组。那么空间复杂度就是O(1)
			

			转换思考方向， 如果f(l,i) 代表从第l行，第i个元素到最底一层的最小路径和， 那么有状态转移方程： f(l, i) = min{f(l+1, i) + f(l+1, i+1)} + triangle[l][i], 同理可以使用一维数组作为dp表	

   */


/*
// solution 1: dfs回溯搜索 【超时】
class Solution {
public:
	int ans = INT_MAX;
	void dfs(vector<vector<int>>& triangle, int l, int i, int step) {
		// terminator
		if (triangle.size()-1 == l) {
			// 最后一层
			ans = min(ans, step);
			return ;
		}		
		dfs(triangle, l+1, i, step + triangle[l+1][i]);
		dfs(triangle, l+1, i+1, step + triangle[l+1][i+1]);
	}

    int minimumTotal(vector<vector<int>>& triangle) {
	if (!triangle.size()) return 0;	
	dfs(triangle, 0, 0, triangle[0][0]);
	return ans;
    }
};
*/

/*
// solution 2: 负值边单源点最短路径
class Solution {
public:
    // solution 2: 具有负值边的单源点最短
    int minimumTotal(vector<vector<int>>& triangle) {
        int row = triangle.size(); 
        vector<vector<pair<int, bool>>> dist;
        for (int i = 1; i <= row; ++i) {
            dist.emplace_back(i, pair<int, bool>(INT_MAX, false));
        }
        dist[0][0] = make_pair(triangle[0][0], true);
        deque<pair<int, int>> que = {{0, 0}}; 

        while (que.size()) {
            auto node = que.front();
            que.pop_front();
            int x = node.first, y = node.second; 
            dist[x][y].second = false;      // 表示移出队列

            if (x >= row - 1) continue;

            if (dist[x][y].first + triangle[x+1][y] < dist[x + 1][y].first) {
                dist[x + 1][y].first = dist[x][y].first + triangle[x+1][y];
                if (!(dist[x + 1][y].second)) {
                    dist[x + 1][y].second = true;       // 表示入队
                    que.emplace_back(x+1, y);
                }
            }

            if (dist[x][y].first + triangle[x+1][y+1] < dist[x + 1][y+1].first) {
                dist[x + 1][y+1].first = dist[x][y].first + triangle[x+1][y+1];
                if (!(dist[x + 1][y+1].second)) {
                    dist[x + 1][y+1].second = true;     // 表示入队
                    que.emplace_back(x+1, y+1);
                }
            }
        }

        // 最后一排的最小值就是答案
        int res = INT_MAX;
        for (auto &p : dist[row - 1]) {
            res = min(res, p.first); 
        }
        return res;
    }
};
*/

/*
// solution 2: dijkstra(拓扑排序方式)
class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {	
	if (!triangle.size()) return 0;	
	
	// 构造degree数组 和 dist数组
	vector<vector<int>> degree(triangle.size());
	degree[0].push_back(0);
	vector<vector<int>> dist(triangle.size());
	dist[0] = vector<int>(1, triangle[0][0]);
	for (int l = 1; l < triangle.size(); ++l) {
		for (int i = 0; i <= l; ++i) {
			if (0 == i || i == l) degree[l].push_back(1);		
			else degree[l].push_back(2);
		}	
		dist[l] = vector<int>(l+1, INT_MAX);
	}	
	deque<pair<int, int>> que = {{0,0}};

	// dijkstra
	while (que.size()) {
		pair<int, int> cur = que.front();
		que.pop_front();
		
		// 更新邻接顶点
		int l = cur.first, i = cur.second;
		if (l+1 < triangle.size()) {
			dist[l+1][i] = min(dist[l+1][i], dist[l][i] + triangle[l+1][i]);
			if (!--degree[l+1][i]) que.push_back(make_pair(l+1, i));

			dist[l+1][i+1] = min(dist[l+1][i+1], dist[l][i] + triangle[l+1][i+1]);
			if (!--degree[l+1][i+1]) que.push_back(make_pair(l+1, i+1));
		}
	}		
	
	// 最后一行最小值
	int ans = INT_MAX;
	for (auto &e : dist[triangle.size() -1]) ans = min(ans, e);
	return ans;
    }
};
*/

/*
// solution 3: dp; 状态转移方程为 f(l,i) = min(f(l-1, i-1), f(l-1, i)) + triangle[l][i]; 当 l < 0 || i < 0, f(l, i) = INT_MAX
class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
	if (!triangle.size()) return 0;	
	
	vector<vector<int>> dp(triangle.size());
	dp[0].push_back(triangle[0][0]);
	for (int l = 1; l < triangle.size(); ++l) {
		for (int i = 0; i <= l; ++i) {
			if (0 == i) dp[l].push_back(dp[l-1][i] + triangle[l][i]);	
			else if (l == i) dp[l].push_back(dp[l-1][i-1] + triangle[l][i]);
			else dp[l].push_back(min(dp[l-1][i-1], dp[l-1][i]) + triangle[l][i]);
		}
	}	

	// 最后一行最小值
	int ans = INT_MAX;
	for (auto &e : dp[triangle.size() -1]) ans = min(ans, e);
	return ans;
    }
};

// solution 4: dp, 空间优化版; 状态转移方程为 f(l,i) = min(f(l-1, i-1), f(l-1, i)) + triangle[l][i]; 当 l < 0 || i < 0, f(l, i) = INT_MAX
class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
	if (!triangle.size()) return 0;	
	
	vector<vector<int>> dp(2, vector<int>(triangle.size()));
	dp[0][0] = triangle[0][0]; 
	int pre = 0, cur = 1;	
	for (int l = 1; l < triangle.size(); ++l) {
		for (int i = 0; i <= l; ++i) {
			if (0 == i) dp[cur][i] = dp[pre][i] + triangle[l][i];	
			else if (l == i) dp[cur][i] = dp[pre][i-1] + triangle[l][i];
			else dp[cur][i] = min(dp[pre][i-1], dp[pre][i]) + triangle[l][i];
		}
		swap(pre, cur);
	}	

	// 最后一行最小值
	return *min_element(dp[pre].begin(), dp[pre].end());
    }
};

// solution 5: dp, 空间优化版; 一个一维数组 
class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
	if (!triangle.size()) return 0;		
	vector<int> dp(triangle.size());
	dp[0] = triangle[0][0];	
	for (int l = 1; l < triangle.size(); ++l) {
		for (int i = l; i >= 0; --i) {
			if (l == i) dp[i] = dp[i-1] + triangle[l][i];
			else if (0 == i) dp[i] = dp[i] + triangle[l][i];	
			else dp[i] = min(dp[i-1], dp[i]) + triangle[l][i];
		}
	}	
	// 最后一行最小值
	return *min_element(dp.begin(), dp.end());
    }
};


// solution 6: dp, 状态转移方程 f(l, i) = min{f(l+1, i) + f(l+1, i+1)} + triangle[l][i], 使用一维数组作为dp表	
class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
	int len = triangle.size();
	if (!len) return 0;		
	vector<int> dp = triangle[len - 1];
	for (int l = len - 2; l >= 0; --l) {
		for (int i = 0; i <= l; ++i) {
			dp[i] = min(dp[i], dp[i+1]) + triangle[l][i];
		}
	}	
	return dp[0];
    }
};
*/

// solution 7: dp, 状态转移方程 f(l, i) = min{f(l+1, i) + f(l+1, i+1)} + triangle[l][i], 使用原来的triangle一维数组作为dp表
class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int len = triangle.size();
        if (!len) return 0;
        for (int l = len - 2; l >= 0; --l) {
                for (int i = 0; i <= l; ++i) {
                        triangle[l][i] = min(triangle[l+1][i], triangle[l+1][i+1]) + triangle[l][i];
                }
        }
        return triangle[0][0];
    }
};



int main(int argc, char *argv[]) {

	return 0;
}
