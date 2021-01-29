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

	solution 2: 使用words 构建 Trie树， 利用构建的Trie树的公共前缀 进行 dfs回溯;
			
			注意：
			之前是对一个word进行回溯， 回溯递归过程很快结束（因为不符合就退出了）,但是需要对每一个word都要进行一遍MN坐标气垫的回溯;
			而使用trie树后， 使用的是前缀trie结构来进行一遍MN起点的回溯， 但是因为trie结构相比word大很多(分支选择很多), 导致每一个backtracking 其实都很久;
			如果对于已经找到的word不在trie树中去掉， 那么后续的backtracking 还是会走对应的路径， 那么效率是很慢的


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

// solution 2: 构建Trie树进行 dfs回溯搜索; 找到word后并没有删除对应trie节点， 很慢, 仅超过5%
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
*/


// solution 2: 构建Trie树进行 dfs回溯搜索; word后删除对应trie节点【在这里不能直接free 对应节点， 因为在backtracking 过程中要使用到对应的node, 只能使用一些field来标记节点已经删除】, 快的一逼【0ms, 超过100%】
class Solution {
	#define ALPHABET_SIZE 26
	struct TrieNode {
		vector<TrieNode *> children;
		bool end_of_word;
		int pass;			// 经过该节点的次数， 0表示没有单词结果该节点了 	
		TrieNode(): children(ALPHABET_SIZE, nullptr), end_of_word(false), pass(0){}
	};
public:
	void Insert(TrieNode *root, const string &word) {
		TrieNode *cur = root; 				
		for (auto &e : word) {
			++cur->pass;
			if(!cur->children[e-'a']) cur->children[e-'a'] = new TrieNode();
			cur = cur->children[e-'a'];
		}
		cur->end_of_word = true;
		++cur->pass;
	}	
	
	/*
	// trie 中删除word， 这个实现的前提是word必定在trie中
	// 兼容word不在trie中的写法请使用word来实现
	void Remove(TrieNode *root, const string &word) {
		TrieNode *cur = root;
		for (auto &e : word) {
			--cur->pass;		
			cur = cur->children[e-'a'];
		}
		--cur->pass;
		cur->end_of_word = false; 
	} 
	*/
	
	// Remove 递归写法， 兼容word不在root里边的情况
	bool RemoveRecur(TrieNode *node, const string &word, int idx) {
		// terminator
		if (!node) return false;			
		if (idx == word.size()) {
			if (node->end_of_word) {
				// 找到要删除的单词
				node->end_of_word = false;					
				--node->pass;
				return true;
			} else {
				// 没有找到单词
				return false;
			}
		}

		// drill down
		bool flag = RemoveRecur(node->children[word[idx] - 'a'], word, idx+1);
		if (flag) --node->pass;
		return flag;
	} 
	
	void Remove(TrieNode *root, const string &word) {
		RemoveRecur(root, word, 0);
	} 



	vector<vector<int>>xy_diff = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};	
	bool IsValidCoordinate(vector<vector<char>> &board, int x, int y) {
		return x >= 0 && x < board.size() && y >= 0 && y < board[0].size();
	}

	void BackTracking(vector<vector<char>>& board, int r, int c, TrieNode *node, string &word, vector<string>& ans) {
		if (node->end_of_word) {
			ans.push_back(word);
			Remove(root, word);		// 避免重复加入ans 且 标记删除对应节点
		}
		if (!IsValidCoordinate(board, r, c) || !board[r][c] || !node->pass || !node->children[board[r][c] - 'a']) return ;
		
		char tmp = board[r][c]; 
		board[r][c] = 0;
		word.push_back(tmp);
		for (auto &diff : xy_diff) BackTracking(board, r+diff[0], c+diff[1], node->children[tmp - 'a'], word, ans);	
		board[r][c] = tmp;
		word.pop_back();
	}				

    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
	// step 1: 构建Trie 树
	root = new TrieNode;	
	for (auto &word : words) Insert(root, word);

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
private:
    TrieNode *root;
};








int main(int argc, char *argv[]) {

	return 0;
}
