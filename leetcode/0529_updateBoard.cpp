/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Wed 09 Dec 2020 11:21:53 AM CST
 @ File Name	: 0529_updateBoard.cpp
 @ Description	: 529. 扫雷游戏 
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

using namespace std;


/*
如果一个地雷（'M'）被挖出，游戏就结束了- 把它改为 'X'。
如果一个没有相邻地雷的空方块（'E'）被挖出，修改它为（'B'），并且所有和其相邻的未挖出方块都应该被递归地揭露。
如果一个至少与一个地雷相邻的空方块（'E'）被挖出，修改它为数字（'1'到'8'），表示相邻地雷的数量。
*/

/*
// solution 1: dfs
class Solution {
public:
        vector<vector<int>> xy_diff = {{-1,-1}, {-1,0}, {-1,1}, {0,-1}, {0,1}, {1,-1}, {1,0}, {1,1}};
        bool isValidCoordinate(int m, int n, int r, int c) {
                return r >= 0 && r < m && c >= 0 && c < n;
        }

    // 进入dfs的都是E
    void dfs(vector<vector<char>>& board, int r, int c) {
        // 计算周围地雷数量
        int m = board.size(), n = board[0].size(), mines = 0;
        for (auto &diff : xy_diff) {
                int x = r+diff[0], y = c+diff[1];
                if (isValidCoordinate(m, n, x, y) && (board[x][y] == 'M' || board[x][y] == 'X')) ++mines;
        }
        // 如果周围有地雷
        if (mines) board[r][c] = '0' + mines;
        else {
                // 没有地雷， 递归dfs
                board[r][c] = 'B';
                for (auto &diff : xy_diff) {
                        int x = r+diff[0], y = c+diff[1];
                        if (isValidCoordinate(m, n, x, y) && board[x][y] == 'E') dfs(board, x, y);
                }
        }
    }
	// click 指向的一定是E 或 M
    vector<vector<char>> updateBoard(vector<vector<char>>& board, vector<int>& click) {
        int r = click[0], c = click[1];
        if ('M' == board[r][c]) board[r][c] = 'X';
        else dfs(board, click[0], click[1]);
        return board;
    }
};
*/

// solution 2: bfs, 需要visit来作为辅助, 避免一个坐标重复加入队列
class Solution {
public:
	vector<vector<int>> xy_diff = {{-1,-1}, {-1,0}, {-1,1}, {0,-1}, {0,1}, {1,-1}, {1,0}, {1,1}};	
	bool isValidCoordinate(int m, int n, int r, int c) {
		return r >= 0 && r < m && c >= 0 && c < n;
	}

    vector<vector<char>> updateBoard(vector<vector<char>>& board, vector<int>& click) {
        int r = click[0], c = click[1];
        if ('M' == board[r][c]) {
		board[r][c] = 'X';
		return board;
	}
	// que里边全都是E
	deque<pair<int, int>> que;	
	que.push_back({r, c});
	int m = board.size(), n = board[0].size(); 
	vector<vector<bool>> visit(m, vector<bool>(n, false));
	visit[r][c] = true;
	while(que.size()) {
		pair<int, int> cur = que.front();
		que.pop_front();
		r = cur.first, c = cur.second; 
		// 计算周围地雷数量		
		int mines = 0;
		for (auto &diff : xy_diff) {
			int x = r+diff[0], y = c+diff[1];
			if (isValidCoordinate(m, n, x, y) && (board[x][y] == 'M' || board[x][y] == 'X')) ++mines;	
		}	
		// 如果周围有地雷
		if (mines) board[r][c] = '0' + mines;	
		else {	
			// 没有地雷， 递归dfs		
			board[r][c] = 'B'; 
			for (auto &diff : xy_diff) {
				int x = r+diff[0], y = c+diff[1];
				if (isValidCoordinate(m, n, x, y) && board[x][y] == 'E' && !visit[x][y]) {
					que.push_back({x,y});	
					visit[x][y] = true;
				}
			}	
		}	
	}
	return board;
    }
};




int main(int argc, char *argv[]) {

	return 0;
}
