/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Tue 13 Apr 2021 11:17:54 AM CST
 @ File Name	: 0530_getMinimumDifference.cpp
 @ Description	: 530. 二叉搜索树的最小绝对差 
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

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

/*
	题目 与 leetcode 783 一样

	solution 1: bst inorder;
   */

/* 
// solution 1: bst inorder
class Solution {
public:
    int pre_val = -1; 
    int getMinimumDifference(TreeNode* root) {
	if (!root) return INT_MAX; 
	int lans = getMinimumDifference(root->left);
	int diff = INT_MAX; 
	if (pre_val >= 0) diff = root->val - pre_val;		
	pre_val = root->val;
	int rans = getMinimumDifference(root->right);
	return min(lans, min(diff, rans));
    }
};
*/

// solution 1: bst inorder
class Solution {
public:
    int pre_val = -1, ans = INT_MAX; 
    void Inorder(TreeNode *node) {
	    if (!node) return ;
	    Inorder(node->left);	    
	    if (pre_val >= 0) ans = min(ans, node->val - pre_val);
	    pre_val = node->val;
	    Inorder(node->right);	    
    }
    int getMinimumDifference(TreeNode* root) {
	    Inorder(root);
	    return ans;
    }
};



int main(int argc, char *argv[]) {

	return 0;
}
