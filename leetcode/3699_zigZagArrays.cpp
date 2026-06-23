/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Tue 23 Jun 2026 08:39:39 PM CST
 @ File Name	: 3699_zigZagArrays.cpp
 @ Description	: 3699. 锯齿形数组的总数 I 
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
// solution 1: 朴素brute force, 枚举所有可能的序列， 然后判断序列是否为zigzag array
class Solution {
public:
    int zigZagArrays(int n, int l, int r) {
        vector<int> arr;
        int res = 0;
        backtracking(arr, n, l, r, res);
        return res;
    }

    void backtracking(vector<int> &arr, int n, int l, int r, int &res) {
        if (arr.size() == n) {
            if (isZigZag(arr)) {
                res = (res + 1) % 1000000007;
            }
            return ;
        }

        for (int i = l; i <= r; ++i) {
            arr.push_back(i);
            backtracking(arr, n, l, r, res);
            arr.pop_back();
        }
    }

    bool isZigZag(vector<int> &arr) {
        if (arr[0] == arr[1]) return false;
        int prev = arr[0], cur = arr[1];
        for (int i = 2; i < arr.size(); ++i) {
            if (arr[i] == cur) return false;
            if (prev < cur) {
                if (cur < arr[i]) return false;
            } else {
                if (cur > arr[i]) return false;
            }
            prev = cur;
            cur = arr[i];
        }
        return true;
    }
};

// solution 1.1: brute force, 提前剪支
class Solution {
public:
    int zigZagArrays(int n, int l, int r) {
        int res = 0;
        backtracking(n, 0, 0, l, r, res);
        return res;
    }

    void backtracking(int n, int prev, int cur, int l, int r, int &res) {
        if (!n) {
            res = (res + 1) % 1000000007;
            return ;
        }

        bool directFlag = prev && cur;
        if (directFlag) {
            int b, e;
            if (prev < cur)  b = l, e = cur;
            else b = cur+1, e = r+1;
            for (int i = b; i < e; ++i) backtracking(n-1, cur, i, l, r, res);
        } else {
            // 不测方向
            for (int i = l; i <= r; ++i) {
                if (i == cur) continue;
                backtracking(n-1, cur, i, l, r, res);
            }
        }
    }
};

// solution 1.2: brute force, 提前剪支; 相比solution 1.1, 换一些状态变量， 方便后续的dp解法
class Solution {
public:
    int zigZagArrays(int n, int l, int r) {
        int res = 0;
        backtracking(n, 0, 0, l, r, res);
        return res;
    }

    void backtracking(int n, int direct, int cur, int l, int r, int &res) {
        if (!n) {
            res = (res + 1) % 1000000007;
            return ;
        }

        if (direct) {
            // 有方向
            int b, e;
            if (direct == 1) b = l, e = cur;
            else b = cur+1, e = r+1;
            for (int i = b; i < e; ++i) backtracking(n-1, -direct, i, l, r, res);
        } else {
            // 无方向， 选择不与cur相等的即可
            for (int i = l; i <= r; ++i) {
                if (i == cur) continue;
                if (cur) {
                    backtracking(n-1, i > cur ? 1 : -1, i, l, r, res);
                } else {
                    backtracking(n-1, 0, i, l, r, res);
                }
            }
        }
    }
};
*/

// solution 2: dp
/*
    设 m = r - l + 1， 后续使用0 ~ m-1 的数值表示即可， 无需使用 l~r 内的数值
    可知， 当n = 1 时， 结果就是m。
            当 n = 2 时， 结果就是m * (m-1)
            当 n >= 3 时， 可用如下dp计算


    状态定义：
        设 f(k, d, i) 为当前已经选择了k个数，且第k个数选择数值i, 与上一个选择的数的方向关系是d（bool， false 为i 小于上一个数； true 为 i 大于上一个选择的数）

    状态转移方程:
            f(k, false, i) = f(k-1, true, i+1) + f(k-1, true, i+2) + ... + f(k-1, true, m-1)
            f(k, true, i)  = f(k-1, false, 0) + f(k-1, false, 1) + ... + f(k-1, false, i-1)

        又因
            f(k, false, i+1) = f(k-1, true, i+2) + f(k-1, true, i+3) + ... + f(k-1, true, m-1)
            f(k, true, i-1) = f(k-1, false, 0) + f(k-1, false, 1) + ... + f(k-1, false, i-2)

        故 最终状态转移方程可以优化为
            f(k, false, i) = f(k-1, true, i+1) + f(k, false, i+1)
            f(k, true, i)  = f(k, true, i-1) + f(k-1, false, i-1)

        k 的 状态只与 k-1 有关系， 故我们可以使用滚动二维数组来优化空间复杂度

    最终结果 即当选取完所有的元素时， 最终的二维数组的和。

    复杂度分析:
        space complexity : O(m)
        time complexty : O(m*n)
*/
class Solution {
public:
    int zigZagArrays(int n, int l, int r) {
        int m = r - l + 1, prev = 0, cur = 1, dt, b, e, mod = 1000000007;
        /*
        // n >= 3, 故这两个条件分析注释掉了
        if (n == 1) return m;
        if (n == 2) return m*(m-1);
        */

        vector<vector<vector<int>>> dp(2, vector<vector<int>>(2, vector<int>(m)));

        // 初始化一下当k == 2时， 二维数组的值
        for (int d = 0; d < 2; ++d) {
            for (int i = 0; i < m; ++i) {
                dp[prev][d][i] = d ? i : m-1-i;
            }
        }

        for (int k = 3; k <= n; ++k) {
            // d == false
            dp[cur][0][m-1] = 0;
            for (int i = m-2; i >= 0; --i) {
                dp[cur][0][i] = (dp[prev][1][i+1] + dp[cur][0][i+1]) % mod;
            }
            // d == true
            dp[cur][1][0] = 0;
            for (int i = 1; i < m; ++i) {
                dp[cur][1][i] = (dp[cur][1][i-1] + dp[prev][0][i-1]) % mod;
            }
            swap(prev, cur);
        }

        int res = 0;
        for (auto &vec : dp[prev]) {
            for (auto &val : vec) {
                res = (res + val) % mod;
            }
        }
        return res;
    }
};


int main(int argc, char *argv[]) {

	return 0;
}
