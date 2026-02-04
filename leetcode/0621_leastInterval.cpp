/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Wed 20 Jan 2021 11:19:40 AM CST
 @ File Name	: 0621_leastInterval.cpp
 @ Description	: 621. 任务调度器 
 ************************************************************************/
#include <bits/c++config.h>
#include <iostream>
#include <iterator>
#include <utility>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
#include <deque>
#include <unordered_map>
#include <unordered_set>
#include <numeric>

using namespace std;

/*
	solution 1: 回溯
	
	solution 2: 贪心; 模拟调度过程， 每次选取可调度的任务中剩余任务数最多的进行调度; 时间O(N * 26 * 2) 【2是考虑最差情况， 执行一个任务， 下一个任务就要等待， 且进行跳转】, 空间 O(1)

	solution 3: 桶思想， 使用大小为n+1的桶分割cpu等待区域; 
			ans = max(tasks.size(),  (A-1) * (n + 1) + B); 其中 A 是所有任务种类中任务数最大的值， B是任务数为A的任务种类数
   */

/*
// solution 1: 回溯, 在作死边缘疯狂试探
class Solution {
public:
	int ans = INT_MAX;	
	void BackTracking(vector<int>& cnt, vector<int>& time, int remain_tasks, int n, int step) {
		if (!remain_tasks) {
			ans = min(ans, step);
		}			

		// 剪枝
		if (step + 1 >= ans) return; 	

		// drill down 任何一个当前可以调度的任务
		int min_time = INT_MAX, call_cnt = 0;			// min_time下一个可调度的任务的最小时间， call_cnt 当前轮次能够调度的任务个数
		for (int i = 0; i < cnt.size(); ++i) {
			if (cnt[i] <= 0) continue;		
			min_time = min(min_time, time[i]);
			if (time[i] > step) continue;

			// call
			++call_cnt;
			--cnt[i];		
			int tmp = time[i];
			time[i] = step + n + 1;
			BackTracking(cnt, time, remain_tasks-1, n, step+1);
			++cnt[i];		
			time[i] = tmp;
		}	

		// 当前如果没有能够调度的， 直接跳过等待时间， 直接到下一个可调用的step处
		if (!call_cnt)	BackTracking(cnt, time, remain_tasks, n, min_time);
	}

    int leastInterval(vector<char>& tasks, int n) {
	vector<int> cnt(26, 0), time(26, 0);
	for (auto &e : tasks) ++cnt[e-'A']; 
	BackTracking(cnt, time, tasks.size(), n, 0);	
	return ans;
    }
};

// solution 2: 贪心
class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
	vector<int> cnt(26, 0), time(26, 0);
	for (auto &e : tasks) ++cnt[e-'A']; 
	int step = 0;
	for (int remain_tasks = tasks.size(); remain_tasks > 0;) {
		int min_time = INT_MAX, next_task = -1, next_task_cnt = 0;		// min_time下一个可调度的任务的最小时间， call_cnt 当前轮次能够调度的任务个数
		for (int i = 0; i < cnt.size(); ++i) {
			if (cnt[i] <= 0) continue;		
			min_time = min(min_time, time[i]);					// 下一个可调用任务的最小时间
			if (time[i] > step) continue;
			if (cnt[i] > next_task_cnt) next_task = i, next_task_cnt = cnt[i];	// 选取可调用任务的剩余任务数最大的作为下一个任务进行调度
		}	
		
		if (next_task >= 0) {
			// 找到可调度的任务
			--remain_tasks;
			--cnt[next_task];
			time[next_task] = step + n + 1;
			++step;
		} else {
			// 没有找到可调度的任务, 直接跳到下一个可调度任务的time
			step = min_time;
		} 
	}	
	return step;
    }
};

// solution 2: greedy
class Node{
public:
    Node(char key, int val):key(key), val(val) {}
    bool operator<(const Node &obj) const {
        return this->val <= obj.val;
    }
    char key;
    int val;
};

class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        if (0 == n) return tasks.size(); 

        unordered_map<char, int> amountMap;
        for (auto &e : tasks) ++amountMap[e];         
        priority_queue<Node> que;
        for (auto &p : amountMap) que.emplace(p.first, p.second);

        int remain = tasks.size(), step = 0;
        unordered_map<int, char> stepMap;

        while (remain > 0) {
            if (que.size()) {
                auto t = que.top().key; 
                que.pop();
                --remain;
                if (--amountMap[t] > 0) stepMap[step + n] = t;      // 还有未完成的，加入map，到了指定的step就加回来priority_queue 
            } else {
                // idle
            }

            if (stepMap.count(step)) {
                auto t = stepMap[step];
                que.emplace(t, amountMap[t]);
                stepMap.erase(step);
            } 
            ++step;
        }
        return step;  
    }
};
*/

// solution 3: 桶思想, ans = max(tasks.size(),  (A-1) * (n + 1) + B); 其中 A 是所有任务种类中任务数最大的值， B是任务数为A个的任务种类数
class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
	vector<int> cnt(26, 0);
	for (auto &e : tasks) ++cnt[e-'A'];		// 所有任务种类的任务数
	int A = *std::max_element(cnt.begin(), cnt.end());
	int B = std::accumulate(cnt.begin(), cnt.end(), 0, [=](const auto &init, const auto & first)->int{return init + (first == A);});
	return max(static_cast<int>(tasks.size()), (A-1) * (n+1) + B);
    }
};


int main(int argc, char *argv[]) {

	return 0;
}
