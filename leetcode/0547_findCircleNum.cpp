/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Fri 29 Jan 2021 07:25:45 PM CST
 @ File Name	: 0547_findCircleNum.cpp
 @ Description	: 547. 省份数量 
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
	solution 1: dfs	
	
	solution 2: bfs
	
	solution 3: disjoint set 	
   */

/*
// solution 1: dfs; 相当于用邻接矩阵来存储边关系， 所以时间复杂度为O(N^2)
class Solution {
public:
	void Dfs(vector<vector<int>> &isConnected, int row, vector<bool> &visit) {
		if (visit[row]) return ;	
		visit[row] = true;
		for (int i = 0; i < isConnected[row].size(); ++i) {
			if (isConnected[row][i] && !visit[i]) Dfs(isConnected, i, visit);
		}	
	}
    int findCircleNum(vector<vector<int>>& isConnected) {
	int len = isConnected.size(); 		
	vector<bool> visit(len, false);
	int ans = 0;
	for (int i = 0; i < len; ++i) {
		if (visit[i]) continue;
		++ans;
		Dfs(isConnected, i, visit);
	}
	return ans;
    }
};

// solution 2: bfs; 相当于用邻接矩阵来存储边关系， 所以时间复杂度为O(N^2)
class Solution {
public:
	void Bfs(vector<vector<int>> &isConnected, int row, vector<bool> &visit) {
		visit[row] = true;
		deque<int> que = {row};
		while (que.size()) {
			int cur = que.front();
			que.pop_front();	
			for (int i = 0; i < isConnected[cur].size(); ++i) {
				if (isConnected[cur][i] && !visit[i]) {
					que.push_back(i);
					visit[i] = true;
				}
			}	
		}
	}

    int findCircleNum(vector<vector<int>>& isConnected) {
	int len = isConnected.size(); 		
	vector<bool> visit(len, false);
	int ans = 0;
	for (int i = 0; i < len; ++i) {
		if (visit[i]) continue;
		++ans;
		Bfs(isConnected, i, visit);
	}
	return ans;
    }
};
*/

// solution 3: disjoint set
class UnionFindSet  {
public:
	vector<int> vec;	
	int amount;
	UnionFindSet(vector<vector<int>> &isConnected) {
		int len = isConnected.size();	
		vec.resize(len, -1);
		amount = len; 
		for (int i = 0; i < len; ++i) {
			for (int j = 0; j < len; ++j) {
				if (!isConnected[i][j]) continue;
				Union(i, j);
			}
		}				
	}
	void Union(int idx1, int idx2) {
		int p1 = find(idx1), p2 = find(idx2);
		if (p1 == p2) return ;
		if (vec[p1] <= vec[p2]) {
			vec[p1] += vec[p2];
			vec[p2] = p1; 
		} else {
			vec[p2] += vec[p1];
			vec[p1] = p2; 
		}	
		--amount;
	}
	int find(int idx) {
		if (vec[idx] < 0) return idx;
		vec[idx] = find(vec[idx]);
		return vec[idx];
	}
};

class Solution {
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
	UnionFindSet ufs(isConnected);
	return ufs.amount;
    }
};


int main(int argc, char *argv[]) {

	return 0;
}
