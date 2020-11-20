/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Fri 20 Nov 2020 07:45:35 PM CST
 @ File Name	: 0051_solveNQueens.cpp
 @ Description	: 51. N 皇后 
 ************************************************************************/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;



/*
// solution 1: 回溯， 试探所有可能的组合，提前进行剪枝 
//		x-y 的范围是 [-(n-1), n-1]; x+y 的范围是 [0, 2n-2]
class Solution {
public:	
	void BackTracking(int n, vector<bool>& col, vector<bool>& xy_diff, vector<bool>& xy_sum, vector<int>& tmp, vector<vector<int>>& ans) {
		int row = tmp.size();
		if (row == n) {
			ans.push_back(tmp);
			return ;
		}

		for (int i = 0; i < n; ++i) {
			if (col[i] || xy_diff[row-i + n-1] || xy_sum[row+i]) continue;

			col[i] = true;
			xy_diff[row-i+n-1] = true;
			xy_sum[row+i] = true;
			tmp.push_back(i);

			BackTracking(n, col, xy_diff, xy_sum, tmp, ans);

			col[i] = false;
			xy_diff[row-i+n-1] = false;
			xy_sum[row+i] = false;
			tmp.pop_back();
		}
	}

    vector<vector<string>> solveNQueens(int n) {
	if (n <= 0) return {{}};		
	vector<bool> col(n, false), xy_diff(2*n-1, false), xy_sum(2*n-1, false);	// xy_diff, xy_sum 可用unordered_set替代
	vector<int> tmp;
	vector<vector<int>> ans;
	BackTracking(n, col, xy_diff, xy_sum, tmp, ans);

	vector<vector<string>> res;
	for (auto &vec : ans) {
		vector<string> matrix;  
		for (auto &e : vec) { 
			matrix.emplace_back(n, '.');
			matrix.back()[e] = 'Q';
		}
		res.push_back(matrix);
	}

	return res;
    }
};
*/

/*
// solution 2: 与solution1 思路一致， 不过因为三个辅助vector的值都是true or false， 
//		限制：因为内置数据类型中bit位数有限 那么如果n的取值不大, 如在C++中 n<= 64， 可以使用二进制位1/0来替代 
class Solution {
public:	
	void BackTracking(int n, long long col, long long xy_diff, long long xy_sum, vector<int>& tmp, vector<vector<int>>& ans) {
		int row = tmp.size();
		if (row == n) {
			ans.push_back(tmp);
			return ;
		}

		long long valid_position = ((1 << n) - 1) & ~(col | xy_diff | xy_sum); // 所有可行的位
		while (valid_position) {
			// 求最右一位1	
			long long pos_val = valid_position & (-valid_position); 	
			// __builtin_ctz(x)：x末尾0的个数。x=0时结果未定义。
			// 不知如何实现， 如果使用循环， 那么其实时间复杂度就是O(N)， 还不如一开始直接for (i = 0; i<n; ++i);
			int pos = __builtin_ctz(pos_val);			
				
			tmp.push_back(pos);
			BackTracking(n, col|pos_val, (xy_diff|pos_val) >> 1, (xy_sum|pos_val) << 1, tmp, ans);
			tmp.pop_back();

			valid_position &= valid_position - 1;
		}
	}

    vector<vector<string>> solveNQueens(int n) {
	if (n <= 0) return {{}};		
	long long col = 0x0, xy_diff = 0x0, xy_sum = 0x0;
	vector<int> tmp;
	vector<vector<int>> ans;
	BackTracking(n, col, xy_diff, xy_sum, tmp, ans);

	vector<vector<string>> res;
	for (auto &vec : ans) {
		vector<string> matrix;  
		for (auto &e : vec) { 
			matrix.emplace_back(n, '.');
			matrix.back()[e] = 'Q';
		}
		res.push_back(matrix);
	}
	return res;
    }
};
*/

// TODO : solution 3: 在solutin 2的基础上， 使用栈来模拟递归 





int main(int argc, char *argv[]) {

	return 0;
}
