/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Wed 27 Jan 2021 05:46:51 PM CST
 @ File Name	: Trie.cpp
 @ Description	: 
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

#define ALPHABET_SIZE 26			// 假设输入字符串为小写字母
struct TrieNode {
	TrieNode():children(ALPHABET_SIZE, nullptr), isLeaf(false) {}		
	vector<TrieNode *> children; 
	bool isLeaf;
};  

// root : root node of the trie
// key : string to be inserted into the trie
// If not present, inserts key into trie
// If the key is prefix of trie node, just marks leaf node
void insert(struct TrieNode *root, string key) {
	if (!root) return ;
	TrieNode *cur = root;							 
	for (auto &e : key) {
		if (!cur->children[e-'a']) cur->children[e-'a'] = new TrieNode();   	
		cur = cur->children[e - 'a'];
	}
	cur->isLeaf = true;
}

// root : root node of the trie
// key : string to search in the trie
// Returns true if key presents in trie, else false
bool search(struct TrieNode *root, string key) {
	if (!root) return false;
	TrieNode *cur = root;	
	for (auto &e :key) {
		cur = cur->children[e-'a'];				
		if (!cur) return false;  
	}
	return cur->isLeaf;
}


// 释放以root 为根的trie树
void FreeTrie(TrieNode *root) {
	if (!root) return ;
	for (auto &ptr : root->children) {
		if (!ptr) continue;
		FreeTrie(ptr);			
	}			
	delete root;
}


// 判断root 是否还有子节点
bool IsEmpty(TrieNode *root) {
	if (!root) return true;			
	for (auto &ptr : root->children) {
		if (ptr) return false;
	}	
	return true;
}

// 在root为根的trie树上删除key
TrieNode * _remove(TrieNode *root, const string &key, int idx) {
	// terminator
	if (!root) {
		cout << "miss char node, its char is : " << key[idx-1] << endl; 
		return root;	 
	}
	if (idx == static_cast<int>(key.size())) {
		if (root->isLeaf) {
			root->isLeaf = false;								
			cout << "set end char node isLeaf field to false!" << endl; 
		} else {
			cout << "end char node is not a leaf" << endl; 
		}

		if (IsEmpty(root) && idx) {
			delete root;
			root = nullptr;
			cout << "del useless node , it's character is " << key[idx-1] << endl; 
		}
		return root;
	}

	// drill down
	root->children[key[idx] - 'a'] = _remove(root->children[key[idx] - 'a'], key, idx+1);

	// 沿着路径bottom up 删除对应节点 【trie的根节点理应不能删除的，加入idx != 0 来防止根节点被删除】
	if (!root->isLeaf && IsEmpty(root) && idx) {
		delete root;
		root = nullptr;
		cout << "del useless node , it's character is " << key[idx-1] << endl; 
	}
	return root;
}

void remove(TrieNode *root, string key) {
	_remove(root, key, 0);
}

 
// dfs backtracking
void TraveralTrieHelp(TrieNode* root, string &tmp, vector<string>& ans) {
	// 遇到单词结尾的都加入ans
	if (root->isLeaf) ans.push_back(tmp);				

	for (int i = 0; i < root->children.size(); ++i) {
		if (!root->children[i]) continue;		
		tmp.push_back('a' + i);	
		TraveralTrieHelp(root->children[i], tmp, ans);
		tmp.pop_back();			
	}	
}

// 遍历trie树, 得出所有trie里边的字符串
vector<string> TraversalTrie(TrieNode* root) {
	if (!root) return {};
	vector<string> ans;
	string tmp;
	TraveralTrieHelp(root, tmp, ans);
	return ans;
}


// test case
int main(int argc, char *argv[]) {
	TrieNode *root = new TrieNode();		
	//vector<string> input = {"tmark", "i", "am", "best", "the", "tmux", "ttt", "tmmm", "t", "", "t"};
	vector<string> input = {"edadn", "wujvu", "oyrev", "tmmft","vhnva","dytrx","xxaxc","qvzzr","tprkt","ofgbk"};
	for (auto & e: input) insert(root, e);

	auto ans = TraversalTrie(root);	
	for(auto &e : ans) {
		if (e.size() == 0) cout << "\"\"" << ",";	
		else cout << e << ",";
	}
	cout << endl;

	string del_str;
	while (getline(cin, del_str)) {
		cout << "want to del key : " << del_str << endl;
		remove(root, del_str);
		ans = TraversalTrie(root);	
		for(auto &e : ans) {
			if (e.size() == 0) cout << "\"\"" << ",";	
			else cout << e << ",";
		}
		cout << endl;
	}


	return 0;
}
