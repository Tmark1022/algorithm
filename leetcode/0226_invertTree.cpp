/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Tue 01 Dec 2020 02:28:22 PM CST
 @ File Name	: 0226_invertTree.cpp
 @ Description	: 226. 翻转二叉树 
 ************************************************************************/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stack>
#include <deque>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::stack;
using std::deque;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

/*
// solution 1: 递归， 使用二叉树的前序 or 后序遍历  
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
	if (!root) return root;		
	std::swap(root->left, root->right);	
	invertTree(root->left);	
	invertTree(root->right);	
	return root;
    }
};
*/

/*
// solution 2: 迭代， 使用栈模拟递归过程, 先序遍历 
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
	stack<TreeNode*> stk;
	stk.push(root);
	while (!stk.empty()) {
		TreeNode * cur = stk.top();
		stk.pop();
		
		if (!cur) continue;	
		std::swap(cur->left, cur->right);
		stk.push(cur->left);
		stk.push(cur->right);
	}
	return root;
    }
};
*/

// solution 3: 迭代，使用队列进行层次遍历 
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
	if (!root) return root;
	deque<TreeNode*> que;
	que.push_back(root);
	while(que.size()) {
		TreeNode * cur = que.front();
		que.pop_front();
		std::swap(cur->left, cur->right);
		if (cur->left) que.push_back(cur->left);	
		if (cur->right) que.push_back(cur->right);	
	}
	return root;
    }
};




int main(int argc, char *argv[]) {

	return 0;
}
