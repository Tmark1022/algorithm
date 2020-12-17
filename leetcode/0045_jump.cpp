/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Thu 17 Dec 2020 08:38:35 PM CST
 @ File Name	: 0045_jump.cpp
 @ Description	: 45. 跳跃游戏 II 
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

   solution 1: 【超时】bfs, 从leetcode 55中可以知道， 该问题可以转换为图寻找最短路径问题， 这里只需要求最短路径长度， 所以可以使用BFS;
		时间复杂度为 O(n+e), e最多为N^2, 故最终时间复杂度为 O(N^2)

   solution 2: 【超时】使用辅助数组dist， 遍历nums， 设置其cur的所有下一跳next的最小次数为 dist[next] = min(dist[next], dist[cur] + 1) 
		时间复杂度为O(N^2)
	
   solution 3: 相较于solution2， 因为需要使用O(N)的事件复杂度来维护dist数组， 那是否可以优化掉这部分?
		观察一下什么时候step才会加1, 只有当当前遍历到的nums值到达上一次step的最大延伸位置时， 才会+1
		时间复杂度O(N)

*/


/*
// solution 1: BFS
class Solution {
public:
    int jump(vector<int>& nums) {
	vector<bool> visit(nums.size(), false);		// 题意nums.size()总是大于0		
	deque<int> que; 
	que.push_back(0);
	visit[0] = true;
	
	int step = 0;
	while(que.size()) {
		for (int cnt = que.size(); cnt; --cnt) {
			int cur = que.front();
			que.pop_front();
			if (cur == nums.size() - 1) return step;	
			for (int i = 1; i <= nums[cur]; ++i) {
				int next = cur + i;
				if (next < nums.size() && !visit[next]) {
					que.push_back(next);
					visit[next] = true;
				}
			}
		}
		++step;
	}
	return -1;	
    }
};

// solution 2:
class Solution {
public:
    int jump(vector<int>& nums) {
	vector<int> dist(nums.size(), INT_MAX);		// 题意nums.size()总是大于0, 并且总是可达的		
	dist[0] = 0;
	for (int i = 0; i < nums.size(); ++i) {
		for (int j = 1; j <= nums[i]; ++j) {
			int next = i + j; 	
			if (next < nums.size()) dist[next] = min(dist[next], dist[i] + 1);
		}
	}	
	return dist[nums.size() - 1];
    }
};
*/

// solution 3:
class Solution {
public:
    int jump(vector<int>& nums) {
	int step = 0;	
	int max_pos = 0;	// 下一个step可以到达的最远下标	
	int tail = 0;		// 当前step最后一个下标
	for (int i = 0; i < nums.size(); ++i) {
		if (i > tail) {
			// 已经超过上一个step的最远距离， 更新为下一个step
			++step;	
			tail = max_pos;			// 因为题意总是可达终点， 所以这里max_pos 总是大于tail的
		}	
		max_pos = max(max_pos, i+nums[i]);		
	}	
	return step;
    }
};


int main(int argc, char *argv[]) {

	return 0;
}
