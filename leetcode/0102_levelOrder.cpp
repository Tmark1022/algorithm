/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Fri 04 Dec 2020 09:32:48 AM CST
 @ File Name	: 0102_levelOrder.cpp
 @ Description	: 102. 二叉树的层序遍历 
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
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

/*
// solution 1 : BFS
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
	if (!root) return {};
	vector<vector<int>> ans;			
	deque<TreeNode *> que; 
	que.push_back(root);
	
	while (que.size()) {
		int cnt = que.size();
		vector<int> tmp;
		while (cnt) {
			TreeNode * cur = que.front();
			que.pop_front();
			tmp.push_back(cur->val);	
			if (cur->left) que.push_back(cur->left);	
			if (cur->right) que.push_back(cur->right);	
			--cnt;
		}
		ans.push_back(tmp);
	}	
	return ans;
    }
};
*/

// solution 2 : DFS
class Solution {
public:

	void dfs(TreeNode *root, int level, vector<vector<int>> &ans) {
		if (!root) return ;	
		if (ans.size() == level) ans.push_back({});	
		ans[level].push_back(root->val);
		dfs(root->left, level + 1, ans);
		dfs(root->right, level + 1, ans);
	}

    vector<vector<int>> levelOrder(TreeNode* root) {
	vector<vector<int>> ans;			
	dfs(root, 0, ans);
	return ans;
    }
};



int main(int argc, char *argv[]) {

	return 0;
}
