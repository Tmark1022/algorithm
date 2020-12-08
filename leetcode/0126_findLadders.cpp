/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Tue 08 Dec 2020 01:33:52 PM CST
 @ File Name	: 0126_findLadders.cpp
 @ Description	: 126. 单词接龙 II 
 ************************************************************************/
#include <array>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <deque>
#include <unordered_map>
#include <unordered_set>
#include <climits>

using namespace std;

/*
题目分析:
	要找出图的所有最短路径， 自然而然想到通过图的遍历， 图的遍历有DFS 和 BFS;
	计算最小路径使用BFS会更加合适， 但是常规的BFS过程中，单纯计算最短路径长度, 并没有能够记录所有可能路径 
	而DFS的回溯方法 更加适合记录所有可能的路径， 单纯计算最小路径时， 效率较差【因为要计算很多无效的路径】


其他注意点: 进行DFS 和 BFS遍历时， 需要使用一种记录已经访问过了的顶点的方法:
	1) 使用一个visit数据结构来记录 （常规方法, 可靠）
	2) 使用原来的顶点集数据， 已经访问过就在顶点集中删除对应顶点（回溯过程中就先删除， 再加入来恢复）

solution 1: 单纯DFS回溯方法, 比较记录最小路径; 不过因为需要遍历过多无效路径， 效率很差 
		如终点在第四层（BFS）, 在DFS中过程中会绕来绕去， 重复计算许多根本不可能得出最小路径的过程
		如 直接路径为 第一层 -> 第二层 -> 第三层 -> 第四层(target)
		但计算中可能出现返回之前层次等行为  一 -> 二 -> 三 -> 二 -> 三 -> 四(target)
		但计算中可能出现超越目标层次 再 返回计算的行为  一 -> 二 -> 三 -> 四 -> 五  -> 四(target)	
			
		后面的方法2，3的优化思想， 都是通过剪枝， 让dfs往正确的路径方向上进行计算， 减少搜索空间大小


solution 2: BFS + DFS回溯; 我们通过BFS 记录经过的顶点的邻接顶点（successor）, 并用邻接表的形式存储来下， 然后对得出的邻接表数据进行DFS得出最后所有最小路径
		因为key是字符串， 所以我们使用hashtable 来存储领接表

solution 3: 双向BFS + DFS回溯【最佳】， 因为知道源点和终点， 可以使用双向BFS, 进一步缩小搜索空间， 还是使用邻接表的形式记录经过的顶点的邻接顶点

solution 4: 单纯BFS，queue中存储的不是顶点， 是从源点到该顶点的一条路径, 每次处理一整层数据

*/


/*
// solution 1: DFS
class Solution {
public:
	void BackTracking(string &beginWord, string &endWord, vector<string> &tmp, int step, unordered_set<string> &set) {
		if (beginWord == endWord) {
			if (step < minStep) {
				minStep = step;
				ans = {tmp};	
			} else {
				ans.push_back(tmp);			
			}	
			return ;
		}	
		// 提前剪枝
		if (step >= minStep) return ;
		for (auto &ch : beginWord) {
			char t = ch;			
			for (char i = 'a'; i <= 'z'; ++i) {
				ch = i;	
				if (!set.erase(beginWord)) continue;
				tmp.push_back(beginWord);
				BackTracking(beginWord, endWord, tmp, step+1, set);
				tmp.pop_back();
				set.insert(beginWord);
			}
			ch = t;
		}
	}		

    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
	unordered_set<string> set(wordList.begin(), wordList.end());
	if (!set.count(endWord)) return {};	
	set.erase(beginWord);
	vector<string> tmp;
	tmp.push_back(beginWord);
	BackTracking(beginWord, endWord, tmp, 0, set);
	return ans;
    }

private:
    int minStep = INT_MAX;
    vector<vector<string>> ans;
};

// solution 2: BFS + DFS
class Solution {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
	int num = 0;	
	unordered_map<string, int> map;	
	for (auto &word : wordList) map[word] = num++;  
	if (!map.count(endWord)) return {};
	if (!map.count(beginWord)) map[beginWord] = num++, wordList.push_back(beginWord);
	vector<vector<int>> edge(num);		

	// 并没有找到一条到终点的路径
	if (!bfs(map[beginWord], map[endWord], map, edge, wordList)) return {};
	vector<vector<string>> ans;
	vector<string> tmp({beginWord});
	dfs(map[beginWord], map[endWord], tmp, ans, edge, wordList);

	return ans;
    }

    bool bfs(int bid, int eid, unordered_map<string, int>& map, vector<vector<int>>& edge, vector<string>& wordList) {
	vector<bool> visit(map.size(), false);	
	deque<int> que;
	que.push_back(bid);		
	visit[bid] = true;

	bool found = false;
	while (que.size()) {
		vector<bool> sub_visit = visit;	
		for (int cnt = que.size(); cnt; --cnt) {
			int cid = que.front();		
			que.pop_front();

			for (auto &adj : GetAdjacentVertex(wordList[cid], map)) {
				if (visit[adj]) continue;
				if (adj == eid) found = true; 
				edge[cid].push_back(adj);			// 加入边， （successor）
				// 避免顶点重复入队
				if (sub_visit[adj]) continue; 
				sub_visit[adj] = true;
				que.push_back(adj);
			}	
		}		
		if (found) break;	
		visit = sub_visit;
	}
	return found;
    }

    vector<int> GetAdjacentVertex(string &word, unordered_map<string, int>& map) {
	vector<int> ret;
	for (auto &ch : word) {
		char tmp = ch;
		for (char i = 'a'; i <= 'z'; ++i) {
			ch = i;
			if (!map.count(word)) continue;
			ret.push_back(map[word]);
		}
		ch = tmp;
	}
	return ret; 
    }

    void dfs(int bid, int eid, vector<string>& tmp, vector<vector<string>>& ans, vector<vector<int>>& edge, vector<string>& wordList) {
	if (bid == eid) {
		ans.push_back(tmp);
		return ;
	}		
	
	for (auto &adj : edge[bid]) {
		tmp.push_back(wordList[adj]);
		dfs(adj, eid, tmp, ans, edge, wordList);
		tmp.pop_back();
	}
    }
};
*/

// solution 3: 双向BFS + DFS
class Solution {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
	int num = 0;	
	unordered_map<string, int> map;	
	for (auto &word : wordList) map[word] = num++;  
	if (!map.count(endWord)) return {};
	if (!map.count(beginWord)) map[beginWord] = num++, wordList.push_back(beginWord);
	vector<vector<int>> edge(num);		

	// 并没有找到一条到终点的路径
	if (!bi_bfs(map[beginWord], map[endWord], map, edge, wordList)) return {};
	vector<vector<string>> ans;
	vector<string> tmp({beginWord});
	dfs(map[beginWord], map[endWord], tmp, ans, edge, wordList);

	return ans;
    }

    bool bi_bfs(int bid, int eid, unordered_map<string, int>& map, vector<vector<int>>& edge, vector<string>& wordList) {
	vector<bool> visit(map.size(), false);	
	visit[bid] = true, visit[eid] = true;
	unordered_set<int> bset({bid}), eset({eid});   
	unordered_set<int> *head = &bset, *tail = &eset;   
	bool direction = true, found = false;

	while (bset.size() && eset.size()) {
		// 遍历小的表
		if (head->size() > tail->size()) std::swap(head, tail), direction = !direction;

		unordered_set<int> tmp_set;
		for (auto cid : *head) {
			for (auto &adj : GetAdjacentVertex(wordList[cid], map)) {
				if (tail->count(adj)) found = true; 	
				if (!visit[adj] || tail->count(adj)) {			// 如果没有访问过，或者当前访问adj节点就是tail 的当前层次，就加入边
					tmp_set.insert(adj);				
					if (direction) edge[cid].push_back(adj);
					else edge[adj].push_back(cid);
				}
			}	
		}		

		if (found) break;	
		*head = tmp_set;
		for(auto &id : tmp_set) visit[id] = true;
	}
	return found;
    }

    vector<int> GetAdjacentVertex(string &word, unordered_map<string, int>& map) {
	vector<int> ret;
	for (auto &ch : word) {
		char tmp = ch;
		for (char i = 'a'; i <= 'z'; ++i) {
			ch = i;
			if (!map.count(word)) continue;
			ret.push_back(map[word]);
		}
		ch = tmp;
	}
	return ret; 
    }

    void dfs(int bid, int eid, vector<string>& tmp, vector<vector<string>>& ans, vector<vector<int>>& edge, vector<string>& wordList) {
	if (bid == eid) {
		ans.push_back(tmp);
		return ;
	}		
	
	for (auto &adj : edge[bid]) {
		tmp.push_back(wordList[adj]);
		dfs(adj, eid, tmp, ans, edge, wordList);
		tmp.pop_back();
	}
    }
};




int main(int argc, char *argv[]) {

	return 0;
}
