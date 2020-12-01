/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Tue 01 Dec 2020 02:07:43 PM CST
 @ File Name	: 0429_levelOrder.cpp
 @ Description	: 429. N 叉树的层序遍历 
 ************************************************************************/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <deque>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::deque;

// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};


/*
// solutin 1: 迭代， 使用队列, 每次循环遍历一层
class Solution {
public:
    vector<vector<int>> levelOrder(Node* root) {
	if (!root) return {};
	vector<vector<int>> ans;		
	deque<Node*> que; 
	que.push_back(root);	

	while (que.size()) {
		vector<int> tmp;
		int size = que.size(); 
		while (tmp.size() < size) {
			Node * cur = que.front();				
			que.pop_front();
			tmp.push_back(cur->val);
			for (auto &ptr: cur->children) que.push_back(ptr);			
		}
		ans.push_back(tmp);
	}
	return ans;
    }
};
*/

// solutin 2: 递归，dfs，记录每一层的level 
class Solution {
public:

	void dfs(Node * root, int level, vector<vector<int>>& ans) {
		if (!root) return ;
		if (level == ans.size()) ans.push_back({});
		ans[level].push_back(root->val);		
		for (auto &ptr : root->children) dfs(ptr, level+1, ans);	
	}

    vector<vector<int>> levelOrder(Node* root) {
	vector<vector<int>> ans;		
	dfs(root, 0, ans);
	return ans;
    }
};





int main(int argc, char *argv[]) {

	return 0;
}
