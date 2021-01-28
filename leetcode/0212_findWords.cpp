/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Thu 28 Jan 2021 07:51:31 PM CST
 @ File Name	: 0212_findWords.cpp
 @ Description	: 212. 单词搜索 II 
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
 *
	tips : 
	If the current candidate does not exist in all words' prefix, you could stop backtracking immediately. What kind of data structure could answer such query efficiently? Does a hash table work? Why or why not? How about a Trie? If you would like to learn how to implement a basic trie, please work on this problem: Implement Trie (Prefix Tree) first.

	其中M和N 是board的行和列， k为单词word的平均长度， S是words数组的长度
solution 1: 对words中的每一个 word 执行 dfs回溯搜索; 可以参考leetcode 79; 时间复杂度为 O(M*N*4^K * S), 空间复杂度O(1)【如果算上递归深度的栈消耗， 则为O(K)】

	solution 2: 使用words 构建 Trie树， 利用构建的Trie树的公共前缀 对 dfs回溯进行 pruning;
			构建 Trie 树 时间O(Sk), 空间O(Sk * 26) 【26是字母表大小】
			使用trie树进行dfs 回溯搜索, 可以利用字符串的前缀一次搜索多个字符串。 时间O(M*N*4^K)	

			总时间复杂度为O(M*N*4^K + SK), 空间复杂度O(SK)

		
		拓展: 为什么不能使用哈希表?
		答  : 因为哈希表查找字符串需要完整的字符串匹配， 并不能用于在dfs回溯过程中的进行共同字符串前缀的剪枝
   */


/*
// solution 1: 对words中的每一个 word 执行 dfs回溯搜索
class Solution {
public:
	vector<vector<int>>xy_diff = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};	
	bool IsValidCoordinate(vector<vector<char>> &board, int x, int y) {
		return x >= 0 && x < board.size() && y >= 0 && y < board[0].size();
	}

	bool BackTracking(vector<vector<char>>& board, int r, int c, string &word, int idx) {
		if (idx == word.size()) return true;
		if (!IsValidCoordinate(board, r, c) || board[r][c] != word[idx]) return false;

		char tmp = board[r][c];
		board[r][c] = 0;
		bool flag = false;
		for (auto & diff : xy_diff) {
			flag = BackTracking(board, r+diff[0], c+diff[1], word, idx+1);
			if (flag) break;
		}	
		board[r][c] = tmp;
		return flag;
	}				

    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
	vector<string> ans;		
	for (auto &word : words) {
		for (int i = 0, found = 0; i < board.size() && !found; ++i) {
			for (int j = 0; j < board[i].size() && !found; ++j) {
				if (BackTracking(board, i, j, word, 0)) {
					ans.push_back(word);
					found = 1;		// 避免重复找到加入ans 	
				}	
			}
		}
	}
	return ans;
    }
};
*/


// solution 2: 构建Trie树进行 dfs回溯搜索 
class Solution {
	#define ALPHABET_SIZE 26
	struct TrieNode {
		vector<TrieNode *> children;
		bool end_of_world;
		TrieNode(): children(ALPHABET_SIZE, nullptr), end_of_world(false) {}
	};
public:
	vector<vector<int>>xy_diff = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};	
	bool IsValidCoordinate(vector<vector<char>> &board, int x, int y) {
		return x >= 0 && x < board.size() && y >= 0 && y < board[0].size();
	}

	void BackTracking(vector<vector<char>>& board, int r, int c, TrieNode *node, string &word, vector<string>& ans) {
		if (node->end_of_world) {
			ans.push_back(word);
			node->end_of_world = false;		// 避免重复加入ans
		}
		if (!IsValidCoordinate(board, r, c) || !board[r][c] || !node->children[board[r][c] - 'a']) return ;
		
		char tmp = board[r][c]; 
		board[r][c] = 0;
		word.push_back(tmp);
		for (auto &diff : xy_diff) BackTracking(board, r+diff[0], c+diff[1], node->children[tmp - 'a'], word, ans);	
		board[r][c] = tmp;
		word.pop_back();
	}				

    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
	// step 1: 构建Trie 树
	TrieNode * root = new TrieNode;	
	for (auto &word : words) {
		TrieNode *cur = root;	
		for (auto &ch : word) {
			if (!cur->children[ch - 'a']) cur->children[ch - 'a'] = new TrieNode();
			cur = cur->children[ch - 'a'];
		}
		cur->end_of_world = true;
	}

	// step 2: 以每一个坐标<i, j> 为起点，进行dfs回溯搜索， 注意结构有重复的问题
	vector<string> ans;
	string word;
	for (int i = 0; i < board.size(); ++i) {
		for (int j = 0; j < board[i].size(); ++j) {
			BackTracking(board, i, j, root, word, ans);
		}
	}
	return ans;
    }
};






int main(int argc, char *argv[]) {

	return 0;
}
