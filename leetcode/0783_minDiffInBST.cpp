/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Tue 13 Apr 2021 10:43:17 AM CST
 @ File Name	: 0783_minDiffInBST.cpp
 @ Description	: 783. 二叉搜索树节点最小距离 
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
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

/*
	BST 的inorder 是有序的， 最小距离仅可出现在有序列表中任意两个相邻的元素之间
	
	solution 1: BST inorder; <O(n), O(1)>
   */


// solution 1: BST inorder
class Solution {
public:
    int last_val = -100001;
    int minDiffInBST(TreeNode* root) {
	if (!root) return INT_MAX;	
	int lans = minDiffInBST(root->left);	
	int diff = root->val - last_val;    			
	last_val = root->val;
	int rans = minDiffInBST(root->right);	
	return min(lans, min(diff, rans));
    }
};



int main(int argc, char *argv[]) {

	return 0;
}
