/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Tue 19 Jan 2021 09:30:02 AM CST
 @ File Name	: 0552_checkRecord.cpp
 @ Description	: 552. 学生出勤记录 II 
 ************************************************************************/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
#include <deque>
#include <unordered_map>
#include <unordered_set>
#include <cmath>

using namespace std;

/*
	solution 1: 回溯; 时间 O(3^N), 空间O(N)

	solution 2: dp; 根据solution1 的解法可知存在 idx， acnt 和 lcnt三种状态, 我们使用f(n, a, l) 表示当前下标n，A 个数为a， L 的连续个数为l 的可奖励个数;   
			这是一个三维dp， a 数值范围为[0,1], l 的数值范围为[0,2], 我们可以实例化a 和 l，组合成六种情况:
				状态	| a	| l 
				0	| 0	| 0	
				1	| 0	| 1
				2	| 0	| 2
				3	| 1	| 0
				4	| 1	| 1
				5	| 1	| 2

			现在我们使用dp[n][k] 表示可奖励次数, 存在如下状态转移方程:
				dp[n][0] = dp[n-1][0] + dp[n-1][1] + dp[n-1][2]
				dp[n][1] = dp[n-1][0]
				dp[n][2] = dp[n-1][1]
				dp[n][3] = dp[n-1][0] + dp[n-1][1] + dp[n-1][2] + dp[n-1][3] + dp[n-1][4] + dp[n-1][5]
				dp[n][4] = dp[n-1][3]
				dp[n][5] = dp[n-1][4]
			
			空间优化： 因为n的状态只与 n-1有关， 所以可以省略n这么一维;

			时间 O(N), 空间O(1)		

	solution 3: dp; 设dp[i] 表示i个出席记录【只考虑L和P, 不考虑A】中， 可奖励的情况数;
			1) 当 end whit P : [0...i-1]P 是合法的		
			2) 当 end whit PL : [0...i-2]PL 是合法的		
			3) 当 end whit PLL : [0...i-3]PLL 是合法的		
			
			而当 end whit LLL : [0...i-3]LLL 并不合法	
			
			所以存在如下状态转移方程:
				dp[i] = dp[i-1] + dp[i-2] + dp[i-3]

			base case: 
				dp[1] = 2;	
				dp[2] = 4;
				dp[3] = 7;
	
			当考虑上A时, 我们使用g[i][a] 表示考虑上A的可奖励个数, a 表示A的个数, a的取值为0或1:
				1) 如果A个数为O: 那么 g[i][0] = dp[i] 
				2) 如果A个数为1, 因为A可以出现在任何位置[1~i], 且会重置L的状态:  for k in range(1, i+1): cnt += dp[k-1] * dp[i-k]   

			算上A 时， 总的奖励个数为 g[n][0] + g[n][1];

			时间复杂度 O(N), 空间复杂度O(N)
   */

/*
// solution 1: 回溯
class Solution {
public:
	int ans = 0, mod = 1000000007;
	void BackTracking(int n, int idx, int acnt, int lcnt) {
		if (idx == n) {
			ans = (ans + 1) % mod;
			return ;
		}	

		// p	
		BackTracking(n, idx+1, acnt, 0);
		// a
		if (!acnt) BackTracking(n, idx+1, acnt+1, 0);	
		// l
		if (lcnt < 2) BackTracking(n, idx+1, acnt, lcnt+1);
	}

    int checkRecord(int n) {
	BackTracking(n, 0, 0, 0);	
	return ans;
    }
};

// solution 2: dp
class Solution {
public:
    int checkRecord(int n) {
        long long dp0 = 1, dp1 = 0, dp2 = 0, dp3 = 0, dp4 = 0, dp5 = 0;
        int mod = 1000000007;
        for (int i = 1; i <= n; ++i) {
                long long tmp0 = dp0, tmp3 = dp3;
                dp0 = (dp0 + dp1 + dp2) % mod;
                dp3 = (dp0 + dp3 + dp4 + dp5) % mod;                  // 优化一下dp3 的计算
                dp5 = dp4;
                dp4 = tmp3;
                dp2 = dp1;
                dp1 = tmp0;
        }
        return (dp0 + dp1 + dp2 + dp3 + dp4 + dp5) % mod;
    }
};

// solution 2: 上一个解法的qucik power 优化版
class Solution {
public:
    using Matrix = vector<vector<long>>;
    int checkRecord(int n) {
        Matrix m = {
            {1, 1, 0, 1, 0, 0},
            {1, 0, 1, 1, 0, 0},
            {1, 0, 0, 1, 0, 0},
            {0, 0, 0, 1, 1, 0},
            {0, 0, 0, 1, 0, 1},
            {0, 0, 0, 1, 0, 0},
        };
        // 初始化单位矩阵
        Matrix res = {
            {1, 0, 0, 0, 0, 0},
            {0, 1, 0, 0, 0, 0},
            {0, 0, 1, 0, 0, 0},
            {0, 0, 0, 1, 0, 0},
            {0, 0, 0, 0, 1, 0},
            {0, 0, 0, 0, 1, 1},
        };

        // qucik power 
        while (n) {
            if (n & 1) res = MatrixMul(res, m);
            m = MatrixMul(m, m);  
            n >>= 1; 
        }
        return accumulate(res[0].begin(), res[0].end(), long(0)) % 1000000007;
    }

    // 矩阵行列式 (这里其实写死了6*6)
    Matrix MatrixMul(Matrix &ma, Matrix &mb) {
        Matrix res(6, vector<long>(6, 0));
        for(int i = 0; i < 6; ++i) {
            for (int j = 0; j < 6; ++j) {
                for (int k = 0; k < 6; ++k) {
                    res[i][j] += ma[i][k] * mb[k][j];
                }
                res[i][j] %= 1000000007;
            }
        }
        return res; 
    }
};

*/

// solution 3: dp
class Solution {
public:
    int checkRecord(int n) {
        int mod = 1000000007;
	vector<long long> dp(n+1, 0);
	dp[0] = 1, dp[1] = 2;
	if (n >= 2) dp[2] = 4;
	for (int i = 3; i <= n; ++i) dp[i] = (dp[i-1] + dp[i-2] + dp[i-3]) % mod; 
	long long ans = dp[n]; 	
	for (int k = 1; k <= n; ++k) ans = (ans + dp[k-1] * dp[n-k]) % mod; 
	return ans;
    }
};


int main(int argc, char *argv[]) {

	return 0;
}
