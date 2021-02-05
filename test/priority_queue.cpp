/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Fri 05 Feb 2021 07:30:29 PM CST
 @ File Name	: priority_queue.cpp
 @ Description	: 
 ************************************************************************/
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
#include <deque>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <functional>

using namespace std;

bool Comp(pair<int, pair<int, int>> &p1, pair<int, pair<int, int>> &p2) {
	return p1.first >= p2.first;  
}

int main(int argc, char *argv[]) {
	priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, std::greater<pair<int, pair<int, int>>>> que;

	//priority_queue<pair<int, pair<int, int>>> que(std::greater<pair<int, pair<int, int>>>);
	que.push(make_pair(100, make_pair(10, 2)));
	que.push(make_pair(20, make_pair(1, 1)));
	que.push(make_pair(999, make_pair(0, 1)));
	que.push(make_pair(9, make_pair(0, 111)));


	while (!que.empty()) {
		pair<int, pair<int, int>> cur = que.top();
		que.pop();
		cout << cur.first << "," << "(" << cur.second.first << "," << cur.second.second << ")" << endl;
	}
	return 0;
}

