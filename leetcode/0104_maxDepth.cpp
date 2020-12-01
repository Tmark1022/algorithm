/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Tue 01 Dec 2020 03:08:27 PM CST
 @ File Name	: 0104_maxDepth.cpp
 @ Description	: 104. 二叉树的最大深度 
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

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


/*
// solution 1: 递归， 二叉树后序遍历
class Solution {
public:
    int maxDepth(TreeNode* root) {
	if (!root) return 0;	
	return std::max(maxDepth(root->left), maxDepth(root->right)) + 1;
    }
};
*/

// solution 2: 迭代， BFS，每次循环处理一层
class Solution {
public:
    int maxDepth(TreeNode* root) {
	if (!root) return 0;	
	deque<TreeNode*> que;
	que.push_back(root);
	int ans = 0;  
	while (que.size()) {
		for (int cnt = que.size(); cnt >= 0; --cnt) {
			TreeNode* cur = que.front();								
			que.pop_front();
			if (cur->left) que.push_back(cur->left);		
			if (cur->right) que.push_back(cur->right);		
		}
		++ans;
	}
	return ans;
    }
};


int main(int argc, char *argv[]) {

	return 0;
}
