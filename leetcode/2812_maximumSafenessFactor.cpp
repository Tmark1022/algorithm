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
// solution 1: 多源BFS 求得每个点到最近小偷的安全系数后， 再backtracking 试探所有路径， 求得最大的安全系数;
//              time complexity O(4^(n*n))
class Solution {
public:
    vector<vector<int>> xyDiff = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int maximumSafenessFactor(vector<vector<int>>& grid) {
        // 找出所有小偷的位置
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

        // 多源BFS求每个点到最近小偷的安全系数
        while (que.size()) { 
            auto &p = que.front(); 
            for (auto &diff : xyDiff) {
                int x = p.first + diff[0], y = p.second + diff[1];
                if (x < 0 || x >= n || y < 0 || y >= n || dst[x][y] >= 0) continue;
                dst[x][y] = dst[p.first][p.second] + 1;
                que.emplace_back(x, y);
            }
            que.pop_front();
        }

        // brute force, backtracking 
        int res = 0;
        backtracking(dst, 0, 0, INT_MAX, res);
        return res;
    }

    void backtracking(vector<vector<int>> &dst, int x, int y, int tmp, int &res) {
        int n = dst.size();
        if (x < 0 || x >= n || y < 0 || y >= n || dst[x][y] < 0) return ;

        tmp = min(tmp, dst[x][y]); 
        if (tmp <= res) return ;

        if (x == n-1 && y == n-1) {
            res = tmp;
            return ;
        }

        int t = dst[x][y];  
        dst[x][y] = -1;
        for (auto &diff : xyDiff) {
            backtracking(dst, x+diff[0], y+diff[1], tmp, res);
        }
        dst[x][y] = t;
    }
};
*/

/*
// solution 2: 多源BFS 求得每个点到最近小偷的安全系数后; 再二分法收敛于最终的最大安全系数
//              time complexity O(log(n) * n^2)
class Solution {
public:
    vector<vector<int>> xyDiff = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int maximumSafenessFactor(vector<vector<int>>& grid) {
        // 找出所有小偷的位置
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

        // 多源BFS求每个点到最近小偷的安全系数
        while (que.size()) {
            auto &p = que.front();
            for (auto &diff : xyDiff) {
                int x = p.first + diff[0], y = p.second + diff[1];
                if (x < 0 || x >= n || y < 0 || y >= n || dst[x][y] >= 0) continue;
                dst[x][y] = dst[p.first][p.second] + 1;
                que.emplace_back(x, y);
            }
            que.pop_front();
        }

        // 二分法收敛于最终最大安全系数
        int l = 0, r = min(dst[0][0], dst[n-1][n-1]);
        while (l < r) {
            int mid = l + (r-l+1) / 2;
            if (check(dst, mid)) l = mid;
            else r = mid - 1;
        }
        return l;
    }

    // 可以使用bfs 或者 dfs 检测当只能选取>= limit 的坐标时， 是否存在可行的路径
    bool check(vector<vector<int>> dst, int limit) {
        return dfs(dst, limit, 0, 0);
    }

    bool dfs(vector<vector<int>> &dst, int limit, int x, int y) {
        int n = dst.size();
        if (x < 0 || x >= n || y < 0 || y >= n || dst[x][y] < limit) return false;
        if (x == n-1 && y == n-1) return true;

        dst[x][y] = -1;
        for (auto &diff : xyDiff) {
            if (dfs(dst, limit, x+diff[0], y+diff[1])) return true;
        }
        return false;
    }
};
*/

/*
// solution 3: 多源BFS 求得每个点到最近小偷的安全系数后; 再贪心算法
//          算法细节：
//              贪心参考kruskal算法， 安全系数从大到小选取坐标点， 当选取的点能够连通起点与终点时， 证明存在起点到终点的路径， 
//              那么最后一次选取的坐标点即最大安全系数。
//              判断连通性可以使用并查集， 选取点的时候， 将四方向的已选取点union起来， 当起点和终点在同一个并查集时， 即存在连通性
//
//          时间复杂度： O(n*n*log(n^2)) ==> O(n*n*2logn) ==> O(n*n*logn)
class DisjointSet {
public:
    DisjointSet(int n):n(n), parent(n*n, -1) {}
    int doFind(int idx) {
        if (parent[idx] < 0) return idx;
        auto p = doFind(parent[idx]); 
        return parent[idx] = p;
    }

    void doUnion(int idx1, int idx2) {
        auto p1 = doFind(idx1), p2 = doFind(idx2);
        if (p1 == p2) return ;

        if (parent[p1] > parent[p2]) swap(p1, p2);
        parent[p1] += parent[p2];
        parent[p2] = p1;
    }

    bool isConnect() {
        int bidx = 0, eidx = n*n-1;
        return doFind(bidx) == doFind(eidx);
    }
private:
    vector<int> parent; 
    int n;
};

class Solution {
public:
    vector<vector<int>> xyDiff = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int maximumSafenessFactor(vector<vector<int>>& grid) {
        // 找出所有小偷的位置
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

        // 多源BFS求每个点到最近小偷的安全系数
        vector<pair<int, int>> arr;           // 已按安全系数排序的坐标点
        while (que.size()) { 
            auto &p = que.front(); 
            arr.emplace_back(p.first, p.second);
            for (auto &diff : xyDiff) {
                int x = p.first + diff[0], y = p.second + diff[1];
                if (x < 0 || x >= n || y < 0 || y >= n || dst[x][y] >= 0) continue;
                dst[x][y] = dst[p.first][p.second] + 1;
                que.emplace_back(x, y);
            }
            que.pop_front();
        }

        // 贪心
        DisjointSet ss(n); 
        for (auto it = arr.rbegin(); it != arr.rend(); ++it) {
            for (auto &diff : xyDiff) {
                int x = it->first + diff[0], y = it->second + diff[1];
                if (x < 0 || x >= n || y < 0 || y >= n || dst[x][y] >= 0) continue;
                ss.doUnion(x*n+y, it->first*n+it->second); 
            } 
            if (ss.isConnect()) return dst[it->first][it->second];
            dst[it->first][it->second] = -1;        // pick
        }
        return 0;
    }
};
*/


// solution 4: 多源BFS 求得每个点到最近小偷的安全系数后; 再贪心算法
//          算法细节：
//              贪心参考prim算法， 从起点出发， 每次拓展新的路径点时， 选择目前已知的最大安全系数的点。
//              那么当选择到终点时， 所有选择的点的最小值即最终的安全系数值。
//              每次选择已知的最大安全系数的点， 可以使用优先队列
//
//          时间复杂度： O(n*n*log(n^2)) ==> O(n*n*2logn) ==> O(n*n*logn)
class Node{
public:
    Node(int x, int y, int val):x(x), y(y), val(val) {}
    bool operator<(const Node &obj) const {
        return this->val < obj.val;
    }
    int x, y, val;
};

class Solution {
public:
    vector<vector<int>> xyDiff = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int maximumSafenessFactor(vector<vector<int>>& grid) {
        // 找出所有小偷的位置
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

        // 多源BFS求每个点到最近小偷的安全系数
        while (que.size()) {
            auto &p = que.front();
            for (auto &diff : xyDiff) {
                int x = p.first + diff[0], y = p.second + diff[1];
                if (x < 0 || x >= n || y < 0 || y >= n || dst[x][y] >= 0) continue;
                dst[x][y] = dst[p.first][p.second] + 1;
                que.emplace_back(x, y);
            }
            que.pop_front();
        }

        // 贪心
        int res = INT_MAX;
        priority_queue<Node, vector<Node>, less<Node>> pque;
        pque.push(Node(0, 0, dst[0][0]));
        dst[0][0] = -1;     // visit
        while (pque.size()) {
            auto cur = pque.top();
            pque.pop();
            res = min(res, cur.val);
            if (cur.x == n-1 && cur.y == n-1) return res;

            for (auto &diff : xyDiff) {
                int x = cur.x + diff[0], y = cur.y + diff[1];
                if (x < 0 || x >= n || y < 0 || y >= n || dst[x][y] < 0) continue;
                pque.push(Node(x, y, dst[x][y]));
                dst[x][y] = -1;
            }
        }
        return 0;
    }
};

int main(int argc, char *argv[]) {

	return 0;
}
