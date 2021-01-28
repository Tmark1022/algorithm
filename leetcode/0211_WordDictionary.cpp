/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Thu 28 Jan 2021 01:55:42 PM CST
 @ File Name	: 0211_WordDictionary.cpp
 @ Description	: 211. 添加与搜索单词 - 数据结构设计 
 ************************************************************************/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
#include <deque>
#include <unordered_map>
#include <unordered_set>
#include <regex>

using namespace std;


/*
// solution 1: trie
class WordDictionary {
	#define ALPHABET_SIZE 26
	struct TrieNode {
		vector<TrieNode *> children; 
		bool end_of_word;
		TrieNode():children(ALPHABET_SIZE, nullptr), end_of_word(false) {} 
	};
public:
    WordDictionary() {
	root = new TrieNode();	
    } 

    void addWord(string word) {
	TrieNode *cur = root;	
	for(auto &e : word) {
		if (!cur->children[e-'a']) cur->children[e-'a'] = new TrieNode();	
		cur = cur->children[e-'a'];
	}
	cur->end_of_word = true;
    }
 
    bool search(string word) {
	return _search(root, word, 0);
    }

    bool _search(TrieNode *node, string &word, int idx) {
	if (idx == word.size())	return node->end_of_word;
	if ('.' == word[idx]) {
		for (auto &ptr : node->children) {
			if (ptr && _search(ptr, word, idx+1)) return true;
		}	
		return false;
	} else {
		if (node->children[word[idx] - 'a']) return _search(node->children[word[idx] - 'a'], word, idx+1);
		else return false;
	} 	
    }
private:
	TrieNode *root; 
};
*/


// solution 2: 正则表达式 【超时】
class WordDictionary {
public:
    /** Initialize your data structure here. */
    WordDictionary():words("#") {
    }
    
    void addWord(string word) {
	words += word;	
	words += "#";
    }
    
    bool search(string word) {
	// 注意regex_match 是匹配整一个字符串, pattern 需要写成 “.*#” + word + "#.*"
	return std::regex_search(words, std::regex("#" + word + "#"));
    }
private:
    string words;
};



/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */

int main(int argc, char *argv[]) {

	return 0;
}
