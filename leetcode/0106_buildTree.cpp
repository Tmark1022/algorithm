/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Mon 30 Nov 2020 01:57:35 PM CST
 @ File Name	: 0106_buildTree.cpp
 @ Description	: 106. 从中序与后序遍历序列构造二叉树 
 ************************************************************************/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::unordered_map;



struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// solution 1: 递归
class Solution {
public:        
    TreeNode* buildTree(vector<int>& postorder, int post_begin, int post_end, vector<int>& inorder, int in_begin, int in_end, unordered_map<int, int >& map) {
	if (post_begin > post_end) return nullptr;

	int val = postorder[post_end];			
	int pivot = map[val];		// 因为肯定知道map存在key为val的值， 所以才可以这么写
	int cnt = in_end - pivot;  
	TreeNode* root = new TreeNode(val);	
	root->right = buildTree(postorder, post_end - cnt, post_end - 1, inorder, pivot + 1, in_end, map);    
	root->left = buildTree(postorder, post_begin, post_end - cnt - 1, inorder, in_begin, pivot - 1, map);    
	return root;
    }

    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
	int len = inorder.size();	
	if (!len) return nullptr;

	unordered_map<int, int> map;					
	for (int i = 0; i < len; ++i) {
		map[inorder[i]] = i;
	}
	
	return buildTree(postorder, 0, len - 1, inorder, 0, len - 1, map); 
    }
};


int main(int argc, char *argv[]) {

	return 0;
}
