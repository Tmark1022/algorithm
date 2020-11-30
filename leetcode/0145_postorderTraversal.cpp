/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Fri 27 Nov 2020 07:03:43 PM CST
 @ File Name	: 0145_postorderTraversal.cpp
 @ Description	: 
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
// solution 1: 递归
class Solution {
public:

	void PostOrder(TreeNode *root, vector<int> &ans) {
		if (!root) return ;
		PostOrder(root->left, ans);
		PostOrder(root->right, ans);
		ans.push_back(root->val);
	}

    vector<int> postorderTraversal(TreeNode* root) {
	vector<int> ans;	
	PostOrder(root, ans);
	return ans; 
    }
};
*/


/*
// solution 2: 迭代， 栈记录递归状态
class Solution {
public:
	struct Status{
		TreeNode * ptr;
		int flag;			// 0:还没产生子状态 / 1:已经产生子状态了， 等待回来被访问

	};

    vector<int> postorderTraversal(TreeNode* root) {
	vector<int> ans;	
	stack<Status> stk;
	stk.push({root, 0});
		
	while (!stk.empty()) {
		Status cur = stk.top();
		stk.pop();
		if (!cur.ptr) continue;
		if (cur.flag) {
			ans.push_back(cur.ptr->val);	
		} else {
			stk.push({cur.ptr, 1});
			stk.push({cur.ptr->right, 0});
			stk.push({cur.ptr->left, 0});
		}
	}	
	return ans; 
    }
};



// solution 2: 使用栈
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> ans;    
        stack<TreeNode*> stk; 

        while (root || !stk.empty()) {
            if (root) {
                ans.push_back(root->val);
                stk.push(root);
                root = root->right; 
            }  else {
                root = stk.top();
                stk.pop();
                root = root->left;
            } 
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};
*/


// solution 3: 迭代，morris 遍历 
class Solution {
public:
	void GetAnsData(TreeNode *ptr, vector<int>& ans) {
		vector<int> tmp;
		while (ptr) {
			tmp.push_back(ptr->val);
			ptr = ptr->right;
		}
		ans.insert(ans.end(), tmp.rbegin(), tmp.rend());
	}
	
    vector<int> postorderTraversal(TreeNode* root) {
	vector<int> ans;	
	TreeNode dummy(0, root, nullptr);
	TreeNode *cur = &dummy;

	// 循环总是终结于中序遍历中最后的一个节点， 这里最后会最后会是null;
	// 在morris遍历中， 只有最后一个节点的right是nullptr， 其他节点的right都会在遍历过程中修改为其后驱节点
	while (cur) {
		if (cur->left) {
			// 计算前驱节点
			TreeNode * predecessor = cur->left;
			while (predecessor->right && predecessor->right != cur) predecessor = predecessor->right;			

			if (predecessor->right) {
				// cur 的左子树都已经完成访问了
				predecessor->right = nullptr;		
				GetAnsData(cur->left, ans);
				cur = cur->right;
			} else {
				// cur 的左子树没有访问过
				predecessor->right = cur;		
				cur = cur->left;
			}	
		} else {
			// cur没有左子树, 直接转去右子树
			cur = cur->right;
		}			
	}
	return ans; 
    }
};



int main(int argc, char *argv[]) {

	return 0;
}
