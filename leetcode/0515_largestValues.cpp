/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Fri 11 Dec 2020 08:41:50 PM CST
 @ File Name	: 0515_largestValues.cpp
 @ Description	: 515. 在每个树行中找最大值 
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
// solution 1: BFS
class Solution {
public:
    vector<int> largestValues(TreeNode* root) {
        if (!root) return {};
        vector<int> ans;
        deque<TreeNode *> que;
        que.push_back(root);
        while(que.size()) {
                int minVal = INT_MIN;
                for (int cnt = que.size(); cnt; --cnt) {
                        TreeNode * cur = que.front();
                        que.pop_front();
                        minVal = max(minVal, cur->val);
                        if (cur->left) que.push_back(cur->left);
                        if (cur->right) que.push_back(cur->right);
                }
                ans.push_back(minVal);
        }
        return ans;
    }
};

// solution 2: DFS, 二叉树先序遍历
class Solution {
public:

	void preorder(TreeNode *root, int level, vector<int>& ans) {
		if (!root) return ;	
		if (level == ans.size()) ans.push_back(INT_MIN);
		ans[level] = max(ans[level], root->val);

		preorder(root->left, level + 1, ans);
		preorder(root->right, level + 1, ans);
	}

    vector<int> largestValues(TreeNode* root) {
        if (!root) return {};
	vector<int> ans;
	preorder(root, 0, ans);
        return ans;
    }
};
*/

// solution 3: divide and conquer
class Solution {
public:
    vector<int> largestValues(TreeNode* root) {
        if (!root) return {};
        vector<int> lres = largestValues(root->left);
        vector<int> rres = largestValues(root->right);
        vector<int> ans = {root->val};
        for (int i = 0, j = 0; i < lres.size() || j < rres.size();) {
                if (i >= lres.size()) ans.push_back(rres[j++]);
                else if (j >= rres.size()) ans.push_back(lres[i++]);
                else ans.push_back(max(lres[i++], rres[j++]));
        }
        return ans;
    }
};

int main(int argc, char *argv[]) {

	return 0;
}
