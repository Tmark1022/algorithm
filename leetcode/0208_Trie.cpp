/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Thu 28 Jan 2021 11:29:18 AM CST
 @ File Name	: 0208_Trie.cpp
 @ Description	: 208. 实现 Trie (前缀树) 
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

class Trie {
	#define ALPHABET_SIZE 26 
	struct TrieNode {
		vector<TrieNode *> children;	
		bool end_of_word; 	
		TrieNode():children(ALPHABET_SIZE, nullptr), end_of_word(false) {}
	};	
public:
    /** Initialize your data structure here. */
    Trie() {	
	    root = new TrieNode();
    }
    /** Inserts a word into the trie. */
    void insert(string word) {
	TrieNode *cur = root;	
	for (auto &e : word) {
		if (!cur->children[e-'a']) cur->children[e-'a'] = new TrieNode();		
		cur = cur->children[e-'a'];
	}	
	cur->end_of_word = true;
    }
    TrieNode * GetWordPrefixNode(const string &word) {
	TrieNode * cur = root;	
	for (auto &e : word) {
		cur = cur->children[e - 'a'];	
		if (!cur) return nullptr;
	}		
	return cur;
    }
    /** Returns if the word is in the trie. */
    bool search(string word) {
	TrieNode *node = GetWordPrefixNode(word);
	return node && node->end_of_word;
    }
 
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
	TrieNode *node = GetWordPrefixNode(prefix);
	return node;
    }
private:
    TrieNode *root;
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 **/


int main(int argc, char *argv[]) {

	return 0;
}
