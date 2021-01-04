/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Mon 04 Jan 2021 07:04:20 PM CST
 @ File Name	: 0337_rob.cpp
 @ Description	: 337. 打家劫舍 III
 ************************************************************************/
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
#include <deque>
#include <unordered_map>
#include <unordered_set>

using namespace std;


/*
	solution 1: dp, 设 f(root, 0) 代表以root为根的二叉树中不掠夺root时最大的掠夺金额, f(root, 1) 代表以root为根的二叉树中掠夺root时最大的掠夺金额;
		    有如下状态转移方程:
			f(root, 1) = f(left, 0) + f(right, 0) + root->val;
			f(root, 0) = max(f(left, 0), f(left, 1)) + max(f(right, 0), f(right, 1));  // root不选择时， 左右字节点都能处于选择或不选择状态中
	
			使用二叉树后序遍历来遍历每一个节点。 可以使用unordered_map<TreeNode, int> 来存储dp状态
			因为当前root的状态只与其孩子节点的状态有关， 可以优化掉dp表
   */

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


// solution 1: dp
class Solution {
public:
	pair<int, int> PostOrder(TreeNode *root) {
		if (!root) return make_pair(0, 0);		
		pair<int, int> resl = PostOrder(root->left); 
		pair<int, int> resr = PostOrder(root->right); 
		return make_pair(max(resl.first, resl.second) + max(resr.first, resr.second), resl.first + resr.first + root->val);
	}	
    int rob(TreeNode* root) {
	pair<int, int> ans = PostOrder(root);
	return max(ans.first, ans.second);
    }
};


int main(int argc, char *argv[]) {

	return 0;
}
