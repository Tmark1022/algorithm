/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Mon 30 Nov 2020 08:07:08 PM CST
 @ File Name	: 0590_postorder.cpp
 @ Description	: 590. N叉树的后序遍历 
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

class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};

/*
// solution 1:递归, dfs
class Solution {
public:	
	void dfs(Node * root, vector<int>& ans) {
		if (!root) return ;

		for (auto &ptr : root->children)
			dfs(ptr, ans);
		ans.push_back(root->val);	
	}	

    vector<int> postorder(Node* root) {
	vector<int> ans;	
	dfs(root, ans);
	return ans;
    }
};
*/

// solution 2: 迭代, 使用栈【存储调用状态】来模拟递归递归调用
//		1) 使用状态标记是否已经产生了子状态
//		2) reverse 结果（inspired by 二叉树后续遍历的迭代模板写法）, 根 -> 最右子树 -> 最左子树 ==>reverse==> 最左子树 -> 最右子树 -> 根 
class Solution {
public:
	
	/*
	// 1) method	
	struct Status{
		Node *ptr;		
		int flag;		// 0:等待产生子状态 / 1:等待访问
		Status(Node*a, int b):ptr(a), flag(b) {}
	};	

    vector<int> postorder(Node* root) {
        if (!root) return {};
        vector<int> ans;
        stack<Status> stk;
        stk.push(Status(root, 0));

        while (!stk.empty()) {
                Status cur  = stk.top();
                stk.pop();
		
		if (cur.flag) {
			ans.push_back(cur.ptr->val);
		} else {
			stk.push(Status(cur.ptr, 1));
			for (auto it = cur.ptr->children.rbegin(); it != cur.ptr->children.rend(); ++it) stk.push(Status(*it, 0)); 
		}
        }
        return ans;
    }
    */

    // 2) method
    vector<int> postorder(Node* root) {
	if (!root) return {};
        vector<int> ans;
	stack<Node*> stk;
	stk.push(root);
	while (!stk.empty()) {
		Node * cur  = stk.top();
		stk.pop();
		// 访问
		ans.push_back(cur->val);		
		// 子状态入栈（注意入栈顺序）
		for (auto &ptr: cur->children) stk.push(ptr);
	}
	reverse(ans.begin(), ans.end());		// 最后反转结果
        return ans;
    }
};

int main(int argc, char *argv[]) {

	return 0;
}
