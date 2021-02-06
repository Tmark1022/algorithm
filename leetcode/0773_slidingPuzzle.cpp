/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Sat 06 Feb 2021 02:28:24 PM CST
 @ File Name	: 0773_slidingPuzzle.cpp
 @ Description	: 773. 滑动谜题 
 ************************************************************************/
#include <functional>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
#include <deque>
#include <unordered_map>
#include <unordered_set>
#include <queue>

using namespace std;

/*
	可以把棋盘的状态当做一个顶点，下一步棋所引起的状态改变为这两个顶点的边， 所以该问题其实就是图问题
	在m*n 的棋盘中， 共有(m*n)! 种状态（顶点， 其实就是棋盘的排列）, 0号棋子可以上下左右移动， 所以边数最多为 4*(m*n)!		

	solution 1: dfs 回溯, 时间复杂度为O(4^((m*n)!))  
 
	solution 2: bfs, 时间复杂度O(n+e), 如果使用字符串来表示每一个棋盘状态， 那么时间复杂度为 O(m*n * (m*n)!), 空间复杂度O(m*n * (m*n)!)

	solution 3: bi-bfs, 时空复杂度分析同solution 2

	solution 4: A*, 暂时没有搞懂为什么估价函数采取manhattan distance 必定能得到最优解(最短距离)
   */



/*
// solution 1: dfs 回溯 【完全跑不下去】
class Solution {
public:
	vector<vector<int>> xy_diff = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; 
	bool IsValidCoordinate(vector<vector<int>> &board, int x, int y) {
		return x >= 0 && x < board.size() && y >= 0 && y < board[0].size(); 
	}

	int ans = INT_MAX;
	void BackTracking(vector<vector<int>>& board, string &cur, string &target, unordered_set<string> &visit, int step) {
		cout << cur << "," << target << ", " << step << endl;
		if (cur == target) {
			ans = step;
			return ;
		} 
		if (step >= ans) return ;	
		int aa;

		int idx0 = cur.find('0'), n = board[0].size();			// cur 肯定包含0，这里不用校验了	
		int r = idx0 / n, c = idx0 % n;   	
		for (auto &diff : xy_diff) {
			int x = r + diff[0], y = c + diff[1];			
			if (!IsValidCoordinate(board, x, y)) continue;			
			int idx = x * n + y; 	
			swap(cur[idx0], cur[idx]);	
			if (!visit.count(cur)) {
				visit.insert(cur);
				BackTracking(board, cur, target, visit, step + 1);	
				visit.erase(cur);
			}
			swap(cur[idx0], cur[idx]);	
		}			
	}	

    int slidingPuzzle(vector<vector<int>>& board) {
	string cur, target;		
	for (int i = 0, val = '1'; i < board.size(); ++i) {
		for (int j = 0; j < board[i].size(); ++j) {
			cur += board[i][j] + '0';
			target += val++;	
		}
	}
	target.back() = '0';
	unordered_set<string> visit = {cur};
	BackTracking(board, cur, target, visit, 0);
	return ans == INT_MAX ? -1 : ans;
    }
};

// solution 2: BFS, 按照题意， 固定2*3 的 board
class Solution {
public:
    int slidingPuzzle(vector<vector<int>>& board) {
	vector<vector<int>> idx_map = {{1,3}, {0, 2, 4}, {1, 5}, {0, 4}, {1, 3, 5}, {2, 4}};	
	string cur, target = "123450";		
	for (auto &vec : board) {
		for (auto &e : vec) cur += '0' + e;
	}
	if (cur == target) return 0;
	unordered_set<string> visit = {cur};
	deque<string> que = {cur};
	int step = 0;
	while (que.size()) {
		++step;
		for (int cnt = que.size(); cnt; --cnt) {
			cur = que.front(); 
			que.pop_front();

			int idx0 = cur.find('0');			
			for (auto &idx : idx_map[idx0]) {
				swap(cur[idx0], cur[idx]);	
				if (cur == target) return step;
				if (!visit.count(cur)) {
					visit.insert(cur);	
					que.push_back(cur);
				}
				swap(cur[idx0], cur[idx]);	
			}

		}
	}
	return -1;	
    }
};

// solution 3: 双向BFS, 按照题意， 固定2*3 的 board
class Solution {
public:
    int slidingPuzzle(vector<vector<int>>& board) {
	vector<vector<int>> idx_map = {{1,3}, {0, 2, 4}, {1, 5}, {0, 4}, {1, 3, 5}, {2, 4}};	
	string src, target = "123450";		
	for (auto &vec : board) {
		for (auto &e : vec) src+= '0' + e;
	}
	if (src == target) return 0;

	unordered_set<string> visit = {src, target}, bset = {src}, eset = {target}, *head = &bset, *tail = &eset;
	int step = 0;
	while (head->size() && tail->size()) {
		++step;
		if (head->size() > tail->size()) swap(head, tail);
		unordered_set<string> tmp_set;
		for (auto cur : *head) {
			int idx0 = cur.find('0');			
			for (auto &idx : idx_map[idx0]) {
				swap(cur[idx0], cur[idx]);	
				if (tail->count(cur)) return step;
				if (!visit.count(cur)) {
					visit.insert(cur);	
					tmp_set.insert(cur);
				}
				swap(cur[idx0], cur[idx]);	
			}
		}		
		*head = tmp_set;
	}
	return -1;	
    }
};
*/

// solution 4: A*, 按照题意， 固定2*3 的 board
class Solution {
public:
	struct Node{
		int priority, distance;			
		string str;
		Node(int p, int d, string &s): priority(p), distance(d), str(s) {}
		bool operator>(const Node &p) const {
			return this->priority > p.priority;
		}	
	};				

	int Heuristic(const string &str) {
		int ans = 0; 
		for (int i = 0; i < str.size(); ++i) {
			if (str[i] == '0') continue;
			int ti = str[i] - '1'; 			
			ans += abs(i/3 - ti/3) + abs(i%3 - ti%3);
		}
		return ans;
	}

    int slidingPuzzle(vector<vector<int>>& board) {
	vector<vector<int>> idx_map = {{1,3}, {0, 2, 4}, {1, 5}, {0, 4}, {1, 3, 5}, {2, 4}};	
	string src, target = "123450";		
	for (auto &vec : board) {
		for (auto &e : vec) src += '0' + e;
	}

	unordered_set<string> visit;
	priority_queue<Node, vector<Node>, greater<Node>> que;
	que.push(Node(0, 0, src));

	while (que.size()) {
		Node cur = que.top();
		que.pop();
		
		// 是否已经访问
		if (visit.count(cur.str)) continue;
		visit.insert(cur.str);

		// 判断是否已经到达终点
		if (cur.str == target) return cur.distance;

		int idx0 = cur.str.find('0');			
		for (auto &idx : idx_map[idx0]) {
			swap(cur.str[idx0], cur.str[idx]);	
			if (!visit.count(cur.str))  que.push(Node(cur.distance + 1 + Heuristic(cur.str), cur.distance + 1, cur.str));	
			swap(cur.str[idx0], cur.str[idx]);	
		}
	}
	return -1;	
    }
};






int main(int argc, char *argv[]) {
	vector<vector<int>> board = {{1,2,3},{5,4,0}};
	Solution obj;
	cout << obj.slidingPuzzle(board) << endl; 
	return 0;
}
