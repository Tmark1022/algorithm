/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Thu 14 Jan 2021 10:26:57 AM CST
 @ File Name	: 0303_sumRange.cpp
 @ Description	: 303. 区域和检索 - 数组不可变 
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
	solution 1: brute force; 不做预处理， 每一次范围查询都遍历累加起来； 构造对象O(1), 查询O(N), 空间O(1)
	solution 2: 使用缓存; 预先计算每一个范围的区域和，使用哈希表存储起来，每次查询查哈希表; 构造对象O(N^2), 查询O(1), 空间O(N^2)
	solution 3: 使用缓存，一维前缀和【不知是否算是dp】; 构造对象O(N), 查询O(1), 空间O(N)
			g(i) 表示 sum{sums[0 ... i -1]};
			区域和 f(i, j) = g(j+1) - g(i); 
   */


// solution 3: 一维前缀和 
class NumArray {
public:
	vector<int> g;
    NumArray(vector<int>& nums) {
	g.resize(nums.size() + 1, 0);
	for (int i = 1; i <= nums.size(); ++i) g[i] = g[i-1] + nums[i-1];
    }
    
    int sumRange(int i, int j) {
	return g[j+1] - g[i];
    }
};

int main(int argc, char *argv[]) {

	return 0;
}
