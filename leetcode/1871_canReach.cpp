/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Wed 15 Jan 2025 07:36:10 PM CST
 @ File Name	: 1871_canReach.cpp
 @ Description	: 1871. 跳跃游戏 VII
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
// solution 1: dfs【超时】, time complexity : O((maxJump - minJump) * N),  space complexity : O(N)
//		因为每次寻找adjacent vertex 都需要遍历 maxJump - minJump + 1 的长度。
class Solution {
public:
    bool canReach(string s, int minJump, int maxJump) {
	    vector<bool> visit(s.size(), false);
	    return dfs(0, s, minJump, maxJump, visit);
    }

    bool dfs(int idx, const string &s, int minJump, int maxJump, vector<bool> &visit) {
	    int t = s.size() - 1;
	    if (idx == t) {
		    return true;
	    }

	    visit[idx] = true;
	    for (int j = idx + minJump; j <= min(t, idx + maxJump); ++j) {
		if ('1' == s[j] || visit[j]) continue;

		if (dfs(j, s, minJump, maxJump, visit)) return true;
	    }
	    return false;
    }
};
*/

/*
// solution 2: bfs【超时】, time complexity : O((maxJump - minJump) * N),  space complexity : O(N)
//		因为每次寻找adjacent vertex 都需要遍历 maxJump - minJump + 1 的长度。
class Solution {
public:
    bool canReach(string s, int minJump, int maxJump) {
	    vector<bool> visit(s.size(), false);
	    visit[0] = true;
	    deque<int> que = {0};

	    while (que.size()) {
		auto cur = que.front();
		que.pop_front();

		for (int j = cur + minJump, t = s.size() - 1; j <= min(t, cur + maxJump); ++j) {
	    	    if ('1' == s[j] || visit[j]) continue;

		    if (j == t) return true;
		    visit[j] = true;
		    que.emplace_back(j);
	    	}
	    }
	    return false;
    }
}; 
*/

/*
// 从solution 1 和 solution 2超时可知， 因为每次寻找adjacent vertex 都需要遍历 maxJump - minJump + 1 的长度。故超时
// 并且我们发现，题目只求是否可达， 当首次遍历 idx + minJump ~ idx + maxJump 范围区间时， 该区间的结果已是最终的数据， 
// 后续再访问到该区间的任何一片小区间时， 都是无用的， 我们可以优化掉这块无用访问。
//
// solution 3: 类BFS, 参考拓扑排序方式优化版的单元点最短路劲问题的解法思路， 维护boundary, 表示boundary之后（包含boundary)是还未求解的【而boundary之前的idx是否可达都是已经求解了】， 从而避免重复计算
//		time complexity : O(2N), space complexity : O(N)
//
class Solution {
public:
    bool canReach(string s, int minJump, int maxJump) {
	    vector<bool> bingo(s.size(), false);
	    bingo[0] = true;
	    int boundary = 1, t = s.size() - 1;
	    for (int i = 0; i <= t && boundary <= t; ++i) {
		    // i 并不是一个可跳跃点 或者 i 并不可达
		    if ('1' == s[i] || !bingo[i]) continue;

		    // 设置该区间可达
		    for (int j = max(boundary, i + minJump); j <= min(t, i + maxJump); ++j) {
			    if ('1' == s[j]) continue;
			    bingo[j] = true;
		    }

		    // 更新boundary 
		    boundary = min(t, i + maxJump) + 1;
	    }
	    return bingo[t];
    }
}; 
*/

/*
// solution 3.1: solution 3 的代码优化版 
//		time complexity : O(2N), space complexity : O(N)
//
class Solution {
public:
    bool canReach(string s, int minJump, int maxJump) {
	    s[0] = '2';		// s 原地修改， '2' 表示可达
	    int boundary = 1, t = s.size() - 1;
	    for (int i = 0; i <= t && boundary <= t; ++i) {
		    // i 并不是一个可跳跃点 或者 i 并不可达
		    if ('2' != s[i]) continue;

		    // 设置该区间可达
		    for (boundary = max(boundary, i + minJump); boundary <= min(t, i + maxJump); ++boundary) {
			    if ('0' == s[boundary]) s[boundary] = '2'; 
		    }
	    }
	    return '2' == s[t];
    }
}; 
*/

// solution 4: dp, 设f(i) 表示下标为i的位置是否可达。f(i) 位置可达需要满足如下两个条件。
//		1) s(i) == '0'
//		2) 区间[i - maxJump, i - minJump] 存在可达的下标。
//
//		故 存在如下递推关系式
//		f(i) = 0; when s[i] == '1' 
//		f(i) = OR{f(i-maxJump), f(i-maxJump + 1), ...., f(i-minJump)};
// 
//		OR{f(i-maxJump), f(i-maxJump + 1), ...., f(i-minJump)} 的结果可以在遍历过程中动态维护该区间的可达下标数量来快速求解
// 
//		
//		time complexity : O(N), space complexity : O(N)
//
class Solution {
public:
    bool canReach(string s, int minJump, int maxJump) {
	    vector<bool> dp(s.size(), false);
	    dp[0] = true;
	    int cnt = 0;
	    for (int i = 1; i < s.size(); ++i) {
		    if (i - minJump >= 0 && dp[i - minJump]) ++cnt;
		    if (s[i] == '0' && cnt) dp[i] = true;
		    if (i - maxJump >= 0 && dp[i - maxJump]) --cnt;
	    }
	    return dp[s.size() - 1];
    }
}; 






int main(int argc, char *argv[]) {	

	return 0;
}

