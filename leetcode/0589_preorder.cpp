/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Mon 30 Nov 2020 08:20:53 PM CST
 @ File Name	: 0589_preorder.cpp
 @ Description	: 589. N叉树的前序遍历 
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

                ans.push_back(root->val);
                for (auto &ptr : root->children)
                        dfs(ptr, ans);
        }

    vector<int> preorder(Node* root) {
        vector<int> ans;
        dfs(root, ans);
        return ans;
    }
};
*/

// solution 2: 迭代, 使用栈【存储调用状态】来模拟递归递归调用
class Solution {
public:
    vector<int> preorder(Node* root) {
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
		for(auto it = cur->children.rbegin(); it != cur->children.rend(); ++it) stk.push(*it);		
	}
        return ans;
    }
};


int main(int argc, char *argv[]) {

	return 0;
}
