/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Wed 15 Jan 2025 07:19:43 PM CST
 @ File Name	: 1306_canReach.cpp
 @ Description	: 
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
// solution 1: dfs, time complexity O(N), space complexity O(N)
class Solution {
public:
    bool canReach(vector<int>& arr, int start) {
	vector<bool> visit(arr.size(), false);
	return dfs(start, arr, visit);
    }

    bool dfs(int idx, const vector<int> &arr, vector<bool> &visit) {
	    if (visit[idx]) return false;
	    visit[idx] = true;
	    if (arr[idx] == 0) return true;

	    if (idx + arr[idx] < arr.size()) {
		if (dfs(idx + arr[idx], arr, visit)) return true;
	    }

	    if (idx - arr[idx] >= 0) {
		if (dfs(idx - arr[idx], arr, visit)) return true;
	    }

	    return false;
    }
};
*/

// solution 2: bfs, time complexity O(N), space complexity O(N)
class Solution {
public:
    bool canReach(vector<int>& arr, int start) {
	    if (arr[start] == 0) return true;
	    int len = arr.size(), next;
	    vector<bool> visit(len, false);
	    visit[start] = true;

	    deque<int> que = {start};
	    while (que.size()) {
		    auto cur = que.front();
		    que.pop_front();

		    next = cur + arr[cur];
		    if (next < len && !visit[next]) {
			if (arr[next] == 0) return true;
			visit[next] = true;
			que.emplace_back(next);
		    }

		    next = cur - arr[cur];
		    if (next >= 0 && !visit[next]) {
			if (arr[next] == 0) return true;
			visit[next] = true;
			que.emplace_back(next);
		    }
	    }
	    return false;
    }
};





int main(int argc, char *argv[]) {

	return 0;
}
