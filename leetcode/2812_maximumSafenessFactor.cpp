/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Wed 01 Jul 2026 12:05:34 PM CST
 @ File Name	: 2812_maximumSafenessFactor.cpp
 @ Description	: 2812. 找出最安全路径
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
// solution 1: brute force， dfs 枚举所有可能的路径， 然后计算途径的点的安全系数， 得出最大安全系数
class Solution {
public:
    vector<vector<int>> xyDiff = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int maximumSafenessFactor(vector<vector<int>>& grid) {
        vector<pair<int, int>> thief;
        for (int i = 0; i < grid.size(); ++i) {
            for (int j = 0; j < grid[i].size(); ++j) {
                if (!grid[i][j]) continue;
                thief.emplace_back(i, j); 
            }
        }

        int res = 0;
        dfs(grid, 0, 0, thief, INT_MAX, res); 
        return res;
    }

    void dfs(vector<vector<int>> &grid, int x, int y, vector<pair<int, int>> &thief, int tmp, int &res) {
        int n = grid.size();

        // 坐标非法或者已经访问过了  
        if (x < 0 || x >= n || y < 0 || y >= n || grid[x][y] < 0) return ;

        tmp = min(tmp, safeFactor(thief, x, y));
        // 提前， pruning 
        if (tmp <= res) return ;

        if (x == n-1 && y == n-1) {
            res = tmp; 
            return ;
        }

        auto tv = grid[x][y];  
        grid[x][y] = -1;            // visit
        for (auto &diff : xyDiff) {
            dfs(grid, x + diff[0], y + diff[1], thief, tmp, res);
        }
        grid[x][y] = tv;
    }
    
    int safeFactor(vector<pair<int, int>> &thief, int x, int y) {
        int res = INT_MAX; 
        for (auto &p : thief) {
            res = min(res, abs(p.first - x) + abs(p.second - y));
        }
        return res;
    }
};
*/

// solution 2: 多源BFS + 二分， time complexity O(nnlogn), space complexity O(N^2)
class Solution {
public:
    vector<vector<int>> xyDiff = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int maximumSafenessFactor(vector<vector<int>>& grid) {
        // 多源BFS 求每个点到最近小偷的距离
        int n = grid.size();
        vector<vector<int>> dst(n, vector<int>(n, -1));
        deque<pair<int, int>> que;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (!grid[i][j]) continue;
                dst[i][j] = 0;
                que.emplace_back(i, j);
            }
        }

        while (que.size()) {
            auto &p = que.front();
            for (auto &diff : xyDiff) {
                auto x = p.first + diff[0], y = p.second + diff[1];
                if (x < 0 || x >= n || y < 0 || y >= n || dst[x][y] >= 0) continue;
                dst[x][y] = dst[p.first][p.second] + 1;
                que.emplace_back(x, y);
            }
            que.pop_front();
        }

        // 二分收敛于最终的最大安全系数
        int l = 0, r = min(dst[0][0], dst[n-1][n-1]), mid;
        while (l < r) {
            mid = l + (r - l + 1) / 2;
            if (check(dst, mid)) l = mid;
            else r = mid - 1;
        }
        return l;
    }

    // BFS 检测是否存在起点到终点的路径（经过的每个点的安全系数都要 >= limit）
    bool check(vector<vector<int>> dst, int limit) {
        int n = dst.size();
        deque<pair<int, int>> que = {{0, 0}};
        dst[0][0] = -1;
        while (que.size()) {
            auto p = que.front();

            for (auto &diff : xyDiff) {
                auto x = p.first + diff[0], y = p.second + diff[1];
                if (x < 0 || x >= n || y < 0 || y >= n || dst[x][y] < limit) continue;
                if (x == n-1 && y == n-1) return true;
                dst[x][y] = -1;
                que.emplace_back(x, y);
            }
            que.pop_front();
        }
        return false;
    }
};


int main(int argc, char *argv[]) {

	return 0;
}
