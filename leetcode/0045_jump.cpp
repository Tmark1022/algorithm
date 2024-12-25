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

   solution 1: 【超时】dfs回溯, 枚举所有路劲， 找出最短路径。
		时间复杂度为指数级 


   solution 2: 每次一层bfs, 从leetcode 55中可以知道， 该问题可以转换为图寻找最短路径问题， 这里只需要求最短路径长度， 所以可以使用BFS;
		时间复杂度为 O(n+e), e最多为N^2, 故最终时间复杂度为 O(N^2)

   solution 3: 其实原理就是BFS求单源点最短路劲问题； 使用辅助数组dist， 遍历nums， 设置其cur的所有下一跳next的最小次数为 dist[next] = min(dist[next], dist[cur] + 1) 
		时间复杂度为O(N^2)
	
   solution 4: dp, 因为有 0 <= nums[i] <= 1000, 所以 dp[N] = min(dp[N-1000 ... N-1]) + 1
		时间复杂度为O(1000N)

   solution 5: 贪心算法1; 反向跳跃查找，每次找出能跳跃到当前点的最远的起点， 跳跃次数加1; O(1000N)

   solution 6: 贪心算法2, 正向跳跃查找，每次找出从当前起点能跳跃到的最远的点。
		时间复杂度O(N)
*/


/*
// solution 1: dfs 回溯， 枚举所有路径可能
class Solution {
public:
    int jump(vector<int>& nums) {   
        int res = INT_MAX;
        vector<bool> visit(nums.size(), false);  
        visit[0] = true;
        dfs(0, nums, visit, 0, res);
        return res; 
    }

    void dfs(int cur, const vector<int> &nums, vector<bool> &visit, int step, int &res) {
        int term = nums.size() - 1;
        if (cur == term) {
            res = step;
            return ;
        }

        // pruning
        if (step >= res - 1) return ;

        for (int next = min(term, cur + nums[cur]); next > cur; --next) {
            if (visit[next]) continue;
            visit[next] = true;
            dfs(next, nums, visit, step + 1, res);
            visit[next] = false;
        } 
    }
};
*/



/*
// solution 2: BFS
class Solution {
public:
    int jump(vector<int>& nums) {
        int term = nums.size() - 1, step = 0;
        if (0 == term) return step;
        vector<bool> visit(nums.size(), false);
        visit[0] = true;
        deque<int> que = {0};
        while (que.size()) {
            ++step;
            for(int cnt = que.size(); cnt; --cnt) {
                auto cur = que.front();
                que.pop_front();
                for (int next = min(term, cur+nums[cur]); next > cur; --next) {
                    if (visit[next]) continue;
                    if (next == term) return step;
                    visit[next] = true;
                    que.emplace_back(next);
                }
            }
        }
        return -1;
    }
};
*/



/*
// solution 3:类似BFS？
class Solution {
public:
    int jump(vector<int>& nums) {
        int term = nums.size() - 1;
        vector<int> dist(nums.size(), INT_MAX);
        dist[0] = 0;
        for (int i = 0; i < nums.size() && INT_MAX == dist[term]; ++i) {
            // if (INT_MAX == dist[i])  return -1;  // 因为题意确保一定可达， 故可以不用改判断
            for (int j = i + 1, e = min(term, i + nums[i]); j <= e; ++j) {
                dist[j] = min(dist[j], dist[i] + 1);
            }
        }
        return dist[term];
    }
};
*/

/*
/// solution 4: dp
class Solution {
public:
    int jump(vector<int>& nums) {
        vector<int> dp(nums.size(), INT_MAX);
        dp[0] = 0;
        for (int k = 1; k < nums.size(); ++k) {
            for (int j = max(0, k - 1000); j < k; ++j) {
                if (j + nums[j] >= k) dp[k] = min(dp[k], dp[j] + 1);
            }
        }
        return dp[nums.size() - 1];
 

        
    }
};
*/

/*
// solution 5: 贪心1, O(1000N)
class Solution {
public:
    int jump(vector<int>& nums) {
        int step = 0, term = nums.size() - 1;
        while (term) {
            ++step;
            // 因为确保一定有答案， 故这里不做不可达判断
            for (int idx = max(0, term - 1000); idx < term; ++idx) {
                if (idx + nums[idx] >= term) {
                    term = idx;
                    break;
                }
            }
        }
        return step;
    }
};
*/

/*
// solution 6: 贪心2, O(N)
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
*/

// solution 6: 贪心2, O(N)
class Solution {
public:
    int jump(vector<int>& nums) {
        int step = 0, maxIdx = 0, lastMaxId = -1, tmp = INT_MIN;
        while (maxIdx < nums.size() - 1) {
            ++step;
            // 寻找下一跳能够达到的最远距离
            for (int i = lastMaxId + 1; i <= maxIdx; ++i) {
                tmp = max(tmp, i + nums[i]);
            }
            lastMaxId = maxIdx;
            maxIdx = tmp;
        }
        return step;
    }
};




int main(int argc, char *argv[]) {

	return 0;
}
