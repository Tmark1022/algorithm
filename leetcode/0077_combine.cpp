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
// solution 3:dp, C(n,k) = C(n-1,k-1) + C(n-1,k), 通俗解释就是是否取当前的n, 来缩小问题规模, f(n, k) = [f(n0,k-1)->push_back(n)] + f(n-1, k);  
// solution 4:字典序法实现组合, 参考官方解法



/*
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
*/


/*
// solution 1: 回溯 
class Solution {
public:
	void dfs(int start, int n, int k, vector<int> &tmp, vector<vector<int>> &ans) {
		// terminator
		if (0 == k) {
			ans.push_back(tmp);
			return ;
		}		
		
		for (int i = start; i <= n - k + 1; ++i) {
			tmp.emplace_back(i);						
			dfs(i+1, n, k-1, tmp, ans);
			tmp.pop_back();
		}
	}

    vector<vector<int>> combine(int n, int k) {
	// invalid
	if (k <= 0 || n < k) {
		return {};
	}	
	vector<int> tmp; 
	vector<vector<int>> ans;		
	dfs(1, n, k, tmp, ans);
	return ans;
    }
};
*/


/*
// solution 2: 二进制枚举 + 剪枝
class Solution {
public:
	void dfs(int cur, int k, vector<int> &tmp, vector<vector<int>> &ans) {

		if (cur + tmp.size() < k) {
			return ;
		}
		if (tmp.size() == k) {
			ans.push_back(tmp);	
			return ;
		}
		
		// non pick	
		dfs(cur-1, k, tmp, ans);	

		// pick
		tmp.emplace_back(cur);			
		dfs(cur-1, k, tmp, ans);	
		tmp.pop_back();
	}

    vector<vector<int>> combine(int n, int k) {
	// invalid
	if (k <= 0 || n < k) {
		return {};
	}	
	vector<int> tmp; 
	vector<vector<int>> ans;		
	dfs(n, k, tmp, ans);
	return ans;
    }
};
*/


/*
// solution 3: C(n, k) = C(n-1, k-1) + c(n-1, k), 没有使用缓存， 重复计算数值
class Solution {
public:	
	vector<vector<int>> Generate(int n, int k) {
		// terminator			
		if (0 == k || n == k) {
			vector<int> tmp;
			for (int i = 1; i <= k; ++i) tmp.emplace_back(i);
			return {tmp};
		}
	

		vector<vector<int>> ans = Generate(n-1, k-1);	
		for (auto& elem : ans) elem.push_back(n); 
		vector<vector<int>> tmp = Generate(n-1, k);    
		ans.insert(ans.end(), tmp.begin(), tmp.end());
		return ans;
	}

    vector<vector<int>> combine(int n, int k) {
	// invalid
	if (k <= 0 || n < k) {
		return {};
	}	
	return Generate(n, k);
    }
};
*/


/*
// solution 3: dp, C(n, k) = C(n-1, k-1) + c(n-1, k), 使用缓存
class Solution {
public:	
	using AnsType = vector<vector<int>>;
	vector<vector<int>> Generate(int n, int k, vector<vector<AnsType>> & cache) {
		// terminator			
		if (!cache[n][k].empty()) {
			return cache[n][k];
		}
	
		AnsType &ans = cache[n][k];
		ans = Generate(n-1, k-1, cache);	
		for (auto& elem : ans) elem.push_back(n); 
		AnsType tmp = Generate(n-1, k, cache);    
		ans.insert(ans.end(), tmp.begin(), tmp.end());
		return ans;
	}

    vector<vector<int>> combine(int n, int k) {
	// invalid
	if (k <= 0 || n < k) {
		return {};
	}	

	// 构造初始的dp表
	vector<vector<AnsType>> cache(n+1,vector<AnsType>(n+1));	
	for (int i = 0; i <= n; ++i) {
		cache[i][0].push_back({});
		if (i > 0) {
			cache[i][i] = cache[i-1][i-1];
			for (auto &e : cache[i][i]) e.push_back(i);
		}
	}	
	return Generate(n, k, cache);
    }
};
*/



// solution 4: 字典序
class Solution {
public:

    vector<vector<int>> combine(int n, int k) {
	// invalid
	if (k <= 0 || n < k) {
		return {};
	}	

	vector<vector<int>> ans;		
	vector<int> tmp; 
	for (int i = 1; i <= k; ++i) tmp.emplace_back(i);
	tmp.push_back(n+1);		// sentinel	
	
	int j = 0;	
	while(j < k) {
		ans.emplace_back(tmp.begin(), tmp.end() - 1);

		// 找出最后一个连续的1
		for (j = 0; j < k && tmp[j] + 1 == tmp[j+1]; ++j) tmp[j] = j+1;
		++tmp[j];
	}

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
