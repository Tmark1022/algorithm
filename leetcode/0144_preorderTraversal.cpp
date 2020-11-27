/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Fri 27 Nov 2020 03:22:49 PM CST
 @ File Name	: 0144_preorderTraversal.cpp
 @ Description	: 144. 二叉树的前序遍历 
 ************************************************************************/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

/*
// solution 1: 递归
class Solution {
public:

	void Preorder(TreeNode *root, vector<int>& ans) {
		if (!root) return ; 
		ans.push_back(root->val);
		Preorder(root->left, ans);
		Preorder(root->right, ans);
	}

    vector<int> preorderTraversal(TreeNode* root) {
	vector<int> ans;
	Preorder(root, ans);
	return ans;
    }
};
*/



/*
// solution 2: 迭代， 使用栈保存递归状态信息， 模拟递归过程
class Solution {
public:

    vector<int> preorderTraversal(TreeNode* root) {
	vector<int> ans;
	stack<TreeNode *> stk;
	stk.push(root);	

	while (!stk.empty()) {
		TreeNode * cur = stk.top();
		stk.pop();

		if (!cur) continue;

		ans.push_back(cur->val);
		stk.push(cur->right);
		stk.push(cur->left);
	}
	return ans;
    }
};
*/

// solution 3: 迭代，morris遍历 
class Solution {
public:

    vector<int> preorderTraversal(TreeNode* root) {
	vector<int> ans;	

	while (root) {	
		if (root->left) {
			TreeNode* predecessor = root->left; 	
			while (predecessor->right && root != predecessor->right) predecessor = predecessor->right;  

			if (predecessor->right) {
				predecessor->right = nullptr;
				root = root->right;
			} else {
				ans.push_back(root->val);
				predecessor->right = root;	
				root = root->left;
			}
		} else {
			ans.push_back(root->val);
			root = root->right;
		}
	}

	return ans;
    }
};

int main(int argc, char *argv[]) {

	return 0;
}
