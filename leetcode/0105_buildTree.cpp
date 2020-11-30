/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Mon 30 Nov 2020 11:41:10 AM CST
 @ File Name	: 0105_buildTree.cpp
 @ Description	: 105. 从前序与中序遍历序列构造二叉树 
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
    TreeNode* buildTree(vector<int>& preorder, int pre_begin, int pre_end, vector<int>& inorder, int in_begin, int in_end, unordered_map<int, int >& map) {
	if (pre_begin > pre_end) return nullptr;

	int val = preorder[pre_begin];			
	int pivot = map[val];		// 因为肯定知道map存在key为val的值， 所以才可以这么写
	int cnt = pivot - in_begin;  
	TreeNode* root = new TreeNode(val);	
	root->left = buildTree(preorder, pre_begin + 1, pre_begin + cnt, inorder, in_begin, pivot - 1, map);    
	root->right = buildTree(preorder, pre_begin + cnt + 1, pre_end, inorder, pivot + 1, in_end, map);    
	return root;
    }

    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
	int len = inorder.size();	
	if (!len) return nullptr;

	unordered_map<int, int> map;					
	for (int i = 0; i < len; ++i) {
		map[inorder[i]] = i;
	}
	
	return buildTree(preorder, 0, len - 1, inorder, 0, len - 1, map); 
    }
};

int main(int argc, char *argv[]) {

	return 0;
}
