/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Fri 27 Nov 2020 10:17:45 AM CST
 @ File Name	: 0094_inorderTraversal.cpp
 @ Description	: 94. 二叉树的中序遍历 
 ************************************************************************/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stack>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::stack;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


/*
// solution 1:递归
class Solution {
public:
	void Help(TreeNode *root, vector<int> &ans) {
		if (!root) return ;

		Help(root->left, ans);	
		ans.push_back(root->val);
		Help(root->right, ans);
	}


    vector<int> inorderTraversal(TreeNode* root) {
	vector<int> ans;	
	Help(root, ans);
	return ans;
    }		
};
*/

/*
// solution 2: 迭代,使用栈来模拟递归调用过程
class Solution {
public:
	struct Status {
		TreeNode *ptr;
		int flag;		// 0:需要递归产生其字状态/ 1:可访问状态 	
		Status(TreeNode *a, int b):ptr(a), flag(b){}
	};

    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> ans;
        stack<Status> stk;
        stk.push({root, 0});

        while (!stk.empty()) {
                Status cur = stk.top();
                stk.pop();

                if (!cur.ptr) {
                    continue;
                }

                if (cur.flag) {
                        ans.push_back(cur.ptr->val);
                        continue;
                } else {
                        stk.push({cur.ptr->right, 0});
                        stk.push({cur.ptr, 1});
                        stk.push({cur.ptr->left, 0});
                }
        }

        return ans;
    }
};
*/

/*
// solution 3: 迭代， 使用栈 
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> ans;
        stack<TreeNode *> stk;	// 保留的是等待回来访问的父亲节点

	while (root || !stk.empty()) {		
		// 左
		while (root) {
			stk.push(root);
			root = root->left;
		}	

		// 访问父节点
		root = stk.top();	
		stk.pop();
		ans.push_back(root->val);

		// 右
		root = root->right;
	}	
	return ans;
    }
};
*/

// solution 4: morris 中序遍历, 对于solution 3，使用栈作为辅助数组进行往回追溯
//		而morris 将当前节点赋值为前驱节点的右孩子， 进行往回追溯
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> ans;

	while (root) {		
		if (root->left) {
			// 存在左孩子， 那么访问左孩子前， 先把当前节点地址赋值给前驱节点的右子树， 用于到时往回追溯
			TreeNode* predecessor = root->left;	
			while (predecessor->right && predecessor->right != root) predecessor = predecessor->right;	

			if (predecessor->right) {
				// 当前节点的前驱部位空【其实值就是当前访问的节点, 之前访问左子树前记录下来的】, 证明当前节点的左子树都访问完了	
				ans.push_back(root->val);	
				predecessor->right = nullptr;
				root = root->right;
			} else {
				predecessor->right = root;
				root = root->left;
			}
		} else {
			// 不存在左孩子，那么直接访问当前节点 	
			ans.push_back(root->val);		
			root = root->right;
		}
	}	
	return ans;
    }
};





int main(int argc, char *argv[]) {

	return 0;
}
