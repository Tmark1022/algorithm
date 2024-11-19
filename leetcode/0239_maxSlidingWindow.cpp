/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Tue 10 Nov 2020 07:15:02 PM CST
 @ File Name	: 0239_maxSlidingWindow.cpp
 @ Description	: 239. 滑动窗口最大值
 ************************************************************************/
#include <iostream>
#include <vector>
#include <deque>
#include <climits>
#include <cmath>

using namespace std;

// 单调队列类
class MonotonicQueue {
public:
	// 入队
	void Push(int val) {
		while (!que.empty() && que.back() < val) que.pop_back(); 
		que.push_back(val);
	}

	// 出队  
	void Pop(int val) {
		if (que.front() == val) que.pop_front();
	}

	int Max() {
		return que.front();
	}

private:
	// 采用双端队列来实现
	deque<int> que;	
};

void PrintVec(const vector<int> &nums) {
	for (auto elem : nums) {
		cout << elem << " ";
	}
	cout << endl;
}

class Solution {
public:
	/*
	// solution 1: 暴力
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
	vector<int> res;
	int len = nums.size();	

	for(int left = 0; left <= len - k; ++left) {
		int max = nums[left];
		for (int i = left + 1, right = left + k - 1; i <= right; ++i) {
			max = std::max(max, nums[i]);
		}	
		res.push_back(max);	
	}
	
	return res;
    }
    */

	/*
    // solution 2: 使用priority_queue 替代solution1中的内层循环， log(n) 时间复杂度入队， 然后O(1)找出最大值 
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> res;
        auto cmp = [](const pair<int, int> &a, const pair<int, int> &b){return a.first <= b.first;};
        priority_queue<pair<int, int>, vector<pair<int,int>>, decltype(cmp)> pq(cmp);

        for (int i = 0; i < k - 1; ++i) pq.push({nums[i], i});
        for (int i = k-1; i < nums.size(); ++i) {
            pq.push({nums[i], i});
            while (pq.top().second <= i - k) pq.pop();
            res.push_back(pq.top().first);
        } 
        return res; 
    }
    */

	// solution 3: 单调队列; 相对于暴力， 要提高效率可以从如何更快地从滑动窗口中找到最大值;
	// 这里我们可以借助递减队列(单调队列)来快速找到最大值， 递减队列存储的是滑动窗口中可能作为下一个最大值的值下标， 队头是当前滑动窗口的最大值 
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
	vector<int> res;
	int len = nums.size();	
	MonotonicQueue que;

	for(int i = 0; i < len; ++i) {
		que.Push(nums[i]);
		if (i >= k-1) {
			res.push_back(que.Max());
			que.Pop(nums[i-k+1]);
		}
	}		
	return res;
    }

	/*
	// solution 4: dp, 将数组划分为大小k的子数组， 
	// 分别计算left数组(所在的K大小子数组左侧到当前下标的最大值) 和 right数组(所在的K大小子数组右侧到当前下标的最大值)
	//
	// 那么对于大小为K的[li, ri]滑动窗口中， 最大值就是max(right[li], left[ri]) 
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {

        vector<int> res;
        int len = nums.size();
        vector<int> left(len, 0), right(len, 0); 

        // 计算left数组
        for(int i = 0; i < len; ++i) {
                // 左
                if (0 == i%k) left[i] = nums[i];
                else left[i] = max(left[i-1], nums[i]);
        }

        // 计算right数组
        for(int i = len - 1; i >= 0; --i) {
                if (i == len - 1 || i%k == k-1) right[i] = nums[i];
                else right[i] = max(right[i+1], nums[i]);
        }


        for(int i = 0; i <= len - k; ++i) {
                res.push_back(max(right[i], left[i + k - 1]));
        }

        return res;
    }
    */
};


int main(int argc, char *argv[]) {
	Solution obj;	
	vector<int> nums = {9,10,9,-7,-4,-8,2,-6};
	PrintVec(nums);
	PrintVec(obj.maxSlidingWindow(nums, 5));
	return 0;
}
