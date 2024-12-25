/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Thu 17 Dec 2020 08:13:40 PM CST
 @ File Name	: 0055_canJump.cpp
 @ Description	: 55. 跳跃游戏 
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


// solution 1: DFS; 这个其实可以转换为一个图寻找路径, 顶点就是所有的nums值, 边就是每一个顶点能够延伸到的范围值;
//		所以这个问题可以使用DFS 或者 BFS(因为知道起点和终点， 所以也能使用双向BFS)来解决; 时间复杂度为o(N+e), e极端情况下是N^2, 所以时间复杂度为O(N^2) 

// solution 2: BFS;

// solution 3: 贪婪， 维护right or maxIdx值表示能从起点开始能到达的右边最远距离， right >= nums.size() - 1 即证明终点可达	


/*
// solution 1: DFS
class Solution {
public:
    // solution 1: dfs
    bool canJump(vector<int>& nums) {
        vector<bool> visit(nums.size(), false);  
        return dfs(0, nums, visit);
    }

    bool dfs(int idx, const vector<int> &nums, vector<bool> &visit) {
        int size = nums.size();
        if (idx == size - 1) {
            return true;
        } 
        visit[idx] = true;
        bool ret = false; 
        for (int next = min(size - 1, idx + nums[idx]); next > idx && !ret; --next) {
            if (visit[next]) continue;
            ret = dfs(next, nums, visit);
        } 
        return ret;
    } 
};
*/


/*
// solution 2: bfs
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int term = nums.size() - 1;
        if (0 == term) return true;
        vector<bool> visit(nums.size(), false);  
        visit[0] = true;
        deque<int> que = {0};
        while (que.size()) {
            auto cur = que.front(); 
            que.pop_front();
            // 从大到小遍历adjacent，尽可能减少比那里规模
            for (int next = min(term, cur + nums[cur]); next > cur; --next) {
                if (visit[next]) continue;
                if (next == term) return true;
                visit[next] = true;
                que.emplace_back(next); 
            }
        }
        return false;
    }
};
*/


/*
// solution 3
class Solution {
public:
    bool canJump(vector<int>& nums) {
	int right = 0;	
	for (int i = 0; i < nums.size(); ++i) {
		if (i > right) return false;
		right = max(right, i + nums[i]);
	}
	return true;
    }
};
*/

// solution 3
class Solution {
public:
    bool canJump(vector<int>& nums) {
        for (int idx = 0, maxIdx = 0; maxIdx < nums.size() - 1; ++idx) {
            if (idx > maxIdx) return false;
            maxIdx = max(maxIdx, idx + nums[idx]);
        }
        return true;
    }
};



int main(int argc, char *argv[]) {

	return 0;
}
