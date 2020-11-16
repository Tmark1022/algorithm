/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Sat 14 Nov 2020 07:28:18 PM CST
 @ File Name	: 0077_combine.cpp
 @ Description	: 77. 组合 
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


// solution 1:回溯 
// solution 2:递归二进制枚举 + 剪枝
// solution 3:C(n,k) = C(n-1,k-1) + C(n-1,k), 通俗解释就是是否取当前的n, 来缩小问题规模, f(n, k) = [f(n0,k-1)->push_back(n)] + f(n-1, k);  
// solution 4:字典序法实现组合, 参考官方解法



// solution 1: 递归模拟多层循环, 每一层递归就一层循环	
class Solution {
public:
	void Help(int level, int start, int n, int k, vector<int> &tmp, vector<vector<int>> &ans) {
		if (level == k) {
			ans.push_back(tmp);
			return ;
		}
		for (int i = start; i <= n - k + 1 + level; ++i) {
			tmp[level] = i; 
			Help(level + 1, i+1, n, k, tmp, ans);
		}
	}	

    vector<vector<int>> combine(int n, int k) {
	// invalid
	if (k <= 0 || n < k) {
		return {};
	}	
	vector<int> tmp(k); 
	vector<vector<int>> ans;		
	Help(0, 1, n, k, tmp, ans);
	return ans;
    }
};

int main(int argc, char *argv[]) {
	int n = 4, k = 2;
	Solution obj;

	vector<vector<int>> ans = obj.combine(n, k);
	for (auto &a : ans) {
		cout << "[";
		for (auto &b :a) {
			cout << b << ",";
		}
		cout << "]" << endl;
	}

	return 0;
}
