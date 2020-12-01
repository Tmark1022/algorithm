/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Tue 01 Dec 2020 02:44:34 PM CST
 @ File Name	: 0098_isValidBST.cpp
 @ Description	: 98. 验证二叉搜索树 
 ************************************************************************/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


/*
// solution 1: 中序遍历, 验证大小
class Solution {
public:
    bool isValidBST(TreeNode* root) {
	if (!root) return true;	 
	if (!isValidBST(root->left)) return false;
	if (last >= root->val) return false;
	last = root->val;
	return isValidBST(root->right);
    }
private: 
	long long last = LONG_MIN;			// int 可能取到INT_MIN， 所以要将int 提升到 long	
};
*/

// solution 2: 递归判断当前节点值大于左子树所有值， 小于右子树所有值。 注意是左右子树， 不是左右孩子
class Solution {
public:	
    bool isValidBST(TreeNode* root, long long lower, long long upper) {
	if (!root) return true; 	
	if (root->val <= lower || root->val >= upper) return false;  
	return isValidBST(root->left, lower, root->val) && isValidBST(root->right, root->val, upper);
    }
    bool isValidBST(TreeNode* root) {
	return isValidBST(root, LONG_MIN, LONG_MAX);
    }
};

int main(int argc, char *argv[]) {

	return 0;
}
