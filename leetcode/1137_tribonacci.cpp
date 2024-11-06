/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Wed 06 Nov 2024 08:14:15 PM CST
 @ File Name	: 1137_tribonacci.cpp
 @ Description	: 1137.第N个泰波那契数 
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
// solution 1: DP 迭代方式实现, 使用滚动数组， 时间复杂度O(N), 空间复杂度O(1)
class Solution {
public:
    int tribonacci(int n) {
	    if (0 == n) return 0;
	    if (2 >= n) return 1;
	    int s, tmp0 = 0, tmp1 = 1, tmp2 = 1;
	    for (int i = 3; i <= n; ++i) {
		s = tmp0 + tmp1 + tmp2;
		tmp0 = tmp1;
		tmp1 = tmp2;
		tmp2 = s;
	    }
	    return s;
    }
};

// solution 2: DP 递归方式实现, 时间复杂度O(N), 空间复杂度O(N)
class Solution {
public:
    int tribonacci(int n) {
	    if (0 == n) return 0;
	    if (2 >= n) return 1;
	    vector<int> cache(n+1, -1);
	    cache[0] = 0, cache[1] = 1, cache[2] = 1;
	    return doit(n, cache);
    }

    int doit(int n, vector<int> &cache) {
	    if (cache[n] >= 0) return cache[n];
	    return cache[n] = doit(n-1, cache) + doit(n-2, cache) + doit(n-3, cache);
    }

};

*/


// solution 3: 矩阵快速幂, 时间复杂度O(logn), 空间复杂度O(1)
class Solution {
public:
    int tribonacci(int n) {
	    if (0 == n) return 0;
	    if (2 >= n) return 1;
	    vector<vector<long>> ret = QuickPow(n - 2); 
	    return ret[0][0] + ret[1][0]; 
    }

    vector<vector<long>> QuickPow(int k) {
		vector<vector<long>> ret = {{1,0,0}, {0,1,0}, {0,0,1}}; 
		vector<vector<long>> mat = {{1,1,0}, {1,0,1}, {1,0,0}};

		while (k) {
			if (k & 1) ret = mul(ret, mat);
			mat = mul(mat, mat);
			k >>= 1;
		}
		return ret;
    }

    vector<vector<long>> mul(const vector<vector<long>> &a, const vector<vector<long>> &b) {
		vector<vector<long>> ret(3, vector<long>(3));
		for(int i = 0; i < 3; ++i) {
			for(int j = 0; j < 3; ++j) {
				ret[i][j] = a[i][0] * b[0][j] + a[i][1] * b[1][j] + a[i][2] * b[2][j];
			}
		}
		return ret;
    }
};



int main(int argc, char *argv[]) {
	
	Solution obj;
	cout << obj.tribonacci(34) << endl;

	return 0;
}
