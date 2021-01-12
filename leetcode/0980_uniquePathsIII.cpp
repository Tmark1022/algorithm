/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Mon 11 Jan 2021 01:54:29 PM CST
 @ File Name	: 0980_uniquePathsIII.cpp
 @ Description	: 980. 不同路径 III 
 ************************************************************************/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
#include <deque>
#include <unordered_map>
#include <unordered_set>
#include <bitset>

using namespace std;


/*
	这道题目的关键是如何控制好是遍历完所有0/1/2顶点【且每一个顶点只能遍历一次】后才到达终点的

	solution 1: dfs回溯搜索【最佳】, 记录当前剩余0/1/2节点的数目; 递归终止条件是到达终点， 并且剩余的0/1/2顶点个数为0;
			为避免dfs重复访问节点， 访问过的节点暂时置为-1
	
	solution 2: dp【记忆化递归方式】, f(i, j, set) 表示使用了坐标集（点集）set, 从起点到达坐标<i, j> 的最大不同路径数  
			存在如下状态转移方程:
				f(i, j, set) = f(i-1, j, set-<i,j>) + f(i+1, j, set-<i,j>) + f(i, j-1, set-<i,j>) + f(i, j+1, set-<i,j>)

				其中 set - <i,j> 表示 点集set中排除<i,j>左边点

			base case:
				1) 非法坐标<i, j> 或 grid[i][j] == -1  ==> f(i, j, set) = 0	
				2) 对于<i,j>是起点， 当 set 只有其自身坐标时 ==> f(i, j, set) = 1; 其他情况下 f(i, j, set) = 0; 
				3) 对于set 不含有 <i,j> 自身时， f(i, j, set) ==> 0 【包含了 set.size() == 0, f(i, j, set) ==> 0】


			因为 m * n <= 20, 我们可以使用int作为bit map来表示点集问题
   */


/*
// solution 1: dfs回溯搜索, 4ms
class Solution {
public:
        vector<vector<int>> xy_diff = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        bool IsValidCoordinate(vector<vector<int>>& grid, int x, int y) {
                return x >= 0 && x < grid.size() && y >= 0 && y < grid[0].size();
        }

        int ans = 0;
        // @x, y: 当前访问坐标
        // n: 剩余0/1/2顶点个数
        void BackTracking(vector<vector<int>>& grid, int x, int y, int n) {
                if (!IsValidCoordinate(grid, x, y) || grid[x][y] == -1) return ;
                if (grid[x][y] == 2) {
                        if (0 == n) ++ans;
                        return ;
                }

                int flag = grid[x][y];
                grid[x][y] = -1;
                for (auto &diff : xy_diff) BackTracking(grid, x+diff[0], y+diff[1], n-1);
                grid[x][y] = flag;
        }

    int uniquePathsIII(vector<vector<int>>& grid) {
            int x = -1, y = -1, n = 0;
            for (int i = 0; i < grid.size(); ++i) {
                    for (int j = 0; j < grid[0].size(); ++j) {
                        if (-1 == grid[i][j]) continue;
                        ++n;
                        if (1 == grid[i][j]) x = i, y = j;
                    }
            }
            BackTracking(grid, x, y, n-1);
            return ans;
    }
};
*/


/*
// solution 2: dp, m*n == 20, 使用int 位图来表示点集, 但是创建dp数组是， 因为最后一维需要 1 << m*n 个元素， 需要使用大量的时间， 但是其实最后一维只使用很少的空间
//		400ms， 很慢
class Solution {
public:
        vector<vector<int>> xy_diff = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        bool IsValidCoordinate(vector<vector<int>>& grid, int x, int y) {
                return x >= 0 && x < grid.size() && y >= 0 && y < grid[0].size();
        }
        int CalIdx(vector<vector<int>> &grid, int x, int y) {
                int n = grid[0].size();
                return x * n + y;
        }
        int CalBitCode(int idx) {
                return 1 << idx;
        }
    int uniquePathsIII(vector<vector<int>>& grid) {
            int m = grid.size(), n = grid[0].size(), sx = -1, sy = -1, tx = -1, ty = -1, set = 0;
            for (int i = 0; i < m; ++i) {
                    for (int j = 0; j < n; ++j) {
                        if (-1 == grid[i][j]) continue;
                        set |= CalBitCode(CalIdx(grid, i, j));
                        if (1 == grid[i][j]) sx = i, sy = j;
                        else if (2 == grid[i][j]) tx = i, ty = j;
                    }
            }

            // 初始化dp数组【三维】
            vector<vector<vector<int>>> dp(m, vector<vector<int>>(n, vector<int>(1 << (m*n), -1)));
            dp[sx][sy] = vector<int>(1 << (m *n), 0);
            dp[sx][sy][CalBitCode(CalIdx(grid, sx, sy))] = 1;
            return Recurse(grid, tx, ty, set, dp);
    }

         int Recurse(vector<vector<int>> &grid, int x, int y, int set, vector<vector<vector<int>>> &dp) {
             if (!IsValidCoordinate(grid, x, y) || -1 == grid[x][y] || !(set & CalBitCode(CalIdx(grid, x, y)))) return 0;
             int offset = CalBitCode(CalIdx(grid, x, y));
             if (-1 != dp[x][y][set]) return dp[x][y][set];

             dp[x][y][set] = 0;
             for (auto &diff : xy_diff) dp[x][y][set] += Recurse(grid, x+diff[0], y+diff[1], set^offset, dp);
             return dp[x][y][set];
     }
};
*/

// solution 3: dp, 使用unordered_map来表示solution 2中dp的最后一维 ,  20ms
class Solution {
public:
    vector<vector<int>> xy_diff = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    bool IsValidCoordinate(vector<vector<int>>& grid, int x, int y) {
        return x >= 0 && x < grid.size() && y >= 0 && y < grid[0].size();
    }

    int CalBitCode(vector<vector<int>> &grid, int x, int y) {
        int n = grid[0].size();
        return 1 << (x *n + y);
    }

    int uniquePathsIII(vector<vector<int>>& grid) {
        int tx = -1, ty = -1, m = grid.size(), n = grid[0].size(), set = 0;
        for (int i = 0; i < m; ++i){
            for (int j = 0; j < n; ++j) {
                if (-1 == grid[i][j]) continue;
                set |= CalBitCode(grid, i, j);
                if (grid[i][j] == 2) tx = i, ty = j;
            }
        }
        vector<vector<unordered_map<int, int>>> dp(m, vector<unordered_map<int, int>>(n));
        return Recurse(grid, tx, ty, set, dp);
    }

    int Recurse(vector<vector<int>> &grid, int x, int y, int set, vector<vector<unordered_map<int, int>>> &dp) {
        if (!IsValidCoordinate(grid, x, y) || -1 == grid[x][y] || !(set & CalBitCode(grid, x, y))) return 0;
        int offset = CalBitCode(grid, x, y);
	// 起点
        if (grid[x][y] == 1) return set == offset ? 1 : 0;
	// 缓存
        if (dp[x][y].count(set)) return dp[x][y][set];
        int cnt = 0;
        for (auto &diff : xy_diff) cnt += Recurse(grid, x+diff[0], y+diff[1], set^offset, dp);
        dp[x][y][set] = cnt;
        return dp[x][y][set];
    }
};



int main(int argc, char *argv[]) {
	Solution obj;
	vector<vector<int>> grid = {{0,0,0,0,0,1,0,2,0,-1,0,-1,0,-1,0}};
	cout << obj.uniquePathsIII(grid) << endl;;
	return 0;
}
