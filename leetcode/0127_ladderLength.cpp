/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Mon 07 Dec 2020 11:33:05 AM CST
 @ File Name	: 0127_ladderLength.cpp
 @ Description	: 127. 单词接龙 
 ************************************************************************/
#include <iostream>
#include <tuple>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <climits>
#include <deque>
#include <unordered_set>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::unordered_map;
using std::deque;
using std::unordered_set;


/*
一. 通过建图的方法来实现
	将worldlist使用邻接表的存储方式建图; 如果worldList 长度为N， 字符串的平均长度为C 
	顶点:
		worldlist里的每一个字符串就是一个图顶点。
	边:
		如果字符串A只改一个字符， 得到worldlist里的合法字符串B, 那么存在无向边<A,B>
		1) 使用暴力的组合两个字符串， 判断是否只有一个字符不同，【太慢, 时间复杂度为O(N^2 *C)】
		2) 创建虚拟节点， N个字符串都通过相同的虚拟节点来相连 
			
	算法分析:
		使用2)方法来构建边集， 总节点数为N*C + N, 总边数为N*C（无向边）/2*N*C（有向边）    
		BFS 时间复杂度为O((N*C + N) + 2*N*C), 即为O(NC)
		空间复杂度为O(NC), 因为最多存储2*NC条边


	solution : 
		1) BFS
		2) 双向BFS


二、 不建图 (leetcode 中跑起来不建图的会快很多))
	边:	
		枚举字符串每一位， 使用26个字符替换， 判断是否存在于worldList中	
		1) BFS
		2) 双向BFS
*/



/*
// solution 1: BFS
class Solution {
public:
	bool AddWord(string word) {
		if (map.find(word) != map.end()) return false;
		map[word] = wordCnt++;
		edge.emplace_back();	
		return true;
	}
	
	void AddEdge(string word) {
		if (!AddWord(word)) return ; 			
		int id1 = map[word];
		for (char &ch : word) {
			char tmp = ch;
			ch = '*';		
			AddWord(word);
			int id2 = map[word];
			edge[id1].push_back(id2);		
			edge[id2].push_back(id1);
			ch = tmp;
		}			
	}

    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
	// 构建顶点和边
	for (const auto& word : wordList) {
		AddEdge(word);	
	}
	
	// beginWord 未必存在于wordList 中
	AddEdge(beginWord);	

	// endWord 是否在顶点集中
	if (map.find(endWord) == map.end()) return 0; 
	
	vector<int> dist(wordCnt, INT_MAX);
	int begin_id = map.at(beginWord), end_id = map.at(endWord);   	
	dist[begin_id] = 0;
	deque<int> que;					
	que.push_back(begin_id);			
	while (que.size()) {
		int id = que.front();	
		que.pop_front();	
		for (const auto& eid : edge[id]) {
			if (dist[id] + 1 < dist[eid]) {
				dist[eid] = dist[id] + 1;		
				if (eid == end_id) return (dist[eid] / 2) + 1;
				que.push_back(eid);
			}
		}
	}
	return 0;	
    }

private: 
	unordered_map<string, int> map;				
	vector<vector<int>> edge;				
	int wordCnt = 0;
};

// solution 2: 双向BFS
class Solution {
public:
	bool AddWord(string word) {
		if (map.find(word) != map.end()) return false;
		map[word] = wordCnt++;
		edge.emplace_back();	
		return true;
	}
	
	void AddEdge(string word) {
		if (!AddWord(word)) return ; 			
		int id1 = map[word];
		for (char &ch : word) {
			char tmp = ch;
			ch = '*';		
			AddWord(word);
			int id2 = map[word];
			edge[id1].push_back(id2);		
			edge[id2].push_back(id1);
			ch = tmp;
		}			
	}

    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
	// 构建顶点和边
	for (const auto& word : wordList) {
		AddEdge(word);	
	}
	
	// beginWord 未必存在于wordList 中
	AddEdge(beginWord);	

	// endWord 是否在顶点集中
	if (map.find(endWord) == map.end()) return 0; 
	
	vector<int> dist_begin(wordCnt, INT_MAX), dist_end(wordCnt, INT_MAX);
	int begin_id = map.at(beginWord), end_id = map.at(endWord);   	
	dist_begin[begin_id] = 0, dist_end[end_id] = 0;
	deque<int> que_begin, que_end;					
	que_begin.push_back(begin_id), que_end.push_back(end_id);			
	
	while (que_begin.size() || que_end.size()) {

		// 每次遍历一层
		int begin_size = que_begin.size();	
		while (begin_size) {
			int id = que_begin.front();	
			que_begin.pop_front();	
			for (const auto& eid : edge[id]) {
				if (dist_begin[id] + 1 < dist_begin[eid]) {
					dist_begin[eid] = dist_begin[id] + 1;		
					que_begin.push_back(eid);
					if (dist_end[eid] < INT_MAX) return (dist_begin[eid] + dist_end[eid]) / 2 + 1;
				}
			}
			--begin_size;
		}

		int end_size = que_end.size();	
		while (end_size) {
			int id = que_end.front();	
			que_end.pop_front();	
			for (const auto& eid : edge[id]) {
				if (dist_end[id] + 1 < dist_end[eid]) {
					dist_end[eid] = dist_end[id] + 1;		
					que_end.push_back(eid);
					if (dist_begin[eid] < INT_MAX) return (dist_begin[eid] + dist_end[eid]) / 2 + 1;
				}
			}
			--end_size;
		}
	}
	return 0;	
    }

private: 
	unordered_map<string, int> map;				
	vector<vector<int>> edge;				
	int wordCnt = 0;
};
*/


/*
// solution 3: BFS，不建图 
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
	unordered_set<string> set(wordList.begin(),wordList.end());     
	if (!set.count(endWord)) return 0;
	int ladder = 0;
	deque<string> que;
	que.push_back(beginWord);	
	set.erase(beginWord);	

	while (que.size()) {
		++ladder;		
		// 每次遍历一整层
		int cnt = que.size();
		while (cnt) {
			string word = que.front();	
			que.pop_front();		

			for (auto &it : word) {
				char tmp = it;
				for (int i = 0; i < 26; ++i) {
					it = 'a' + i;
					// 找到下一顶点
					if (set.erase(word)) {
						if (endWord == word) return ladder + 1;
						que.push_back(word);			
					}
				}			
				it = tmp;
			}	
			--cnt;
		}
	}			
	return 0;
    }
};
*/

// solution 4: 双向BFS，不建图 
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
	unordered_set<string> set(wordList.begin(),wordList.end()), bset({beginWord}), eset({endWord});	
	unordered_set<string> *head = &bset, *tail = &eset;
	if (!set.count(endWord)) return 0;
	set.erase(beginWord);
	set.erase(endWord);

	int ladder = 0;
	while (bset.size() && eset.size()) {
		++ladder;
		// 每次选择size小的来进行遍历
		if (head->size() > tail->size()) std::swap(head, tail);
		// 每次遍历一整层
		unordered_set<string> tmp_set;
		for (auto word : *head) {
			for (auto &ch : word) {
				char tmp = ch;
				for (int i = 0; i < 26; ++i) {
					ch = 'a' + i;					
					if (tail->count(word)) return ladder + 1; 
					if (set.erase(word)) tmp_set.insert(word);				
				}			
				ch = tmp;
			}	
		}
		*head = tmp_set;		
	}			
	return 0;
    }
};

int main(int argc, char *argv[]) {

	return 0;
}
