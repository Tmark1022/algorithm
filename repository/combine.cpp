/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Mon 16 Nov 2020 08:03:51 PM CST
 @ File Name	: combine.cpp
 @ Description	: 
 ************************************************************************/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;


/***************************************************
* 所有子集 
***************************************************/
// 二进制枚举 -- 迭代
vector<vector<int>> BinaryEnumerate(int n)
{
	if (n <= 0) {
		return {};
	}

	vector<vector<int>> ans;
	// 0000.. --> 1111..
	for (int i = 0; i < (1<<n); ++i) {	

		// 判断二进制中那一位为1		
		vector<int> tmp;
		for (int j = 0; j < n; ++j) {
			if (i & (1 << j)) tmp.emplace_back(j + 1);	
		}	

		ans.push_back(tmp);		
	}	
	
	return ans;
}	

// 二进制枚举 -- 递归
void dfs(int cur, int n, vector<int> &tmp, vector<vector<int>> &ans)
{
	if (cur == n+1) {
		ans.push_back(tmp);	
		return ;
	}

	// 不选当前cur
	dfs(cur+1, n, tmp, ans);

	// 选择当前cur
	tmp.push_back(cur);
	dfs(cur+1, n, tmp, ans);
	tmp.pop_back();
}

vector<vector<int>> BinaryEnumerateRecur(int n)
{
	if (n <= 0) {
		return {};
	}
	vector<int> tmp;	
	vector<vector<int>> ans;
	dfs(1, n, tmp, ans);
	return ans;
}	

/***************************************************
* other 
***************************************************/
void PrintVec(const vector<int> &vec)
{
	cout << "[";
	for (auto& e : vec) {
		cout << e<< ",";
	}
	cout << "]" << endl;
}

int main(int argc, char *argv[]) {
	vector<int> nums1, nums2;	
	int n;	
	cout << "n = ";
	cin >> n;	
	auto ret1 = BinaryEnumerateRecur(n);
	cout << "size = "<< ret1.size() << ",[" << endl;
	for (auto & a : ret1) {
		PrintVec(a);
	}
	cout << "]" << endl;


	return 0;
}
