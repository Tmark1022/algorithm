/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Tue 01 Dec 2020 03:25:53 PM CST
 @ File Name	: 0111_minDepth.cpp
 @ Description	: 111. 二叉树的最小深度 
 ************************************************************************/
#include <cstdio>
#include <iostream>
#include <limits>
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

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


// solution 1: 递归, 后序遍历; 
//		需要注意只有一个孩子的节点的最小深度是 1 + minDepth(存在的孩子节点)
class Solution {
public:
    int minDepth(TreeNode* root) {
        if (!root) return 0;
        if (!root->left) return 1 + minDepth(root->right); 
        else if (!root->right) return 1 + minDepth(root->left); 
        else return 1 + std::min(minDepth(root->left), minDepth(root->right)); 
    }
};

/*
// solution 2: bfs, 遇到一个没有左右孩子的节点就break出所有循环
class Solution {
public:
    int minDepth(TreeNode* root) {
	if (!root) return 0;
	deque<TreeNode *> que;	
	que.push_back(root);
	int ans = 0;
	while (que.size()) {
		++ans;
		for (int cnt = que.size(); cnt; --cnt) {	
			TreeNode *cur = que.front();
			que.pop_front();	
			if (!cur->left && !cur->right) return ans;	
			if (cur->left) que.push_back(cur->left);
			if (cur->right) que.push_back(cur->right);
		}	
	}	
	return ans;
    }
};
*/

int main(int argc, char *argv[]) {

	return 0;
}
