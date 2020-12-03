/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Thu 03 Dec 2020 01:47:04 PM CST
 @ File Name	: 0236_lowestCommonAncestor.cpp
 @ Description	: 236. 二叉树的最近公共祖先
 ************************************************************************/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

/*
solution 1: 回溯， 一趟dfs(先序)遍历找到从root 到 p, q的路径, 对比两个路径， 最后一个相同的节点就是最近公共祖先
		时间复杂度O（N）， 空间复杂度O（N）

solution 2: 一遍先序遍历使用hashtable 记录每个节点的父亲节点信息， p q 各自在hashtable中寻找到root的路径， 第一个相遇的就是最近公共祖先
		时间复杂度O（N）， 空间复杂度O（N）

solution 3: solution 1的优化版，直接在递归遍历【后序遍历】中进行判断。 【最佳】
		时间复杂度O（N）， 空间复杂度O（N）【除了递归用到的栈空间， 不用其他辅助空间】
*/

/*
// solution 1: 回溯， 使用vector 记录root 到 p, q的路径 
class Solution {
public:
	void preorder(TreeNode *root, TreeNode *p, TreeNode* q, vector<TreeNode *>& tmp, vector<vector<TreeNode *>> &path) {
		if (!root || path.size() == 2) return ;	
		tmp.push_back(root);			
		// 这里必须分开两次判断，因为p, q可能指向同一个节点
		if (root == p) path.push_back(tmp);
		if (root == q) path.push_back(tmp);
		preorder(root->left, p, q, tmp, path);	
		preorder(root->right, p, q, tmp, path);	
		tmp.pop_back();
	}

    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
	vector<TreeNode *> tmp;
	vector<vector<TreeNode *>> path;
	preorder(root, p, q, tmp, path);

	if (path.size() != 2) return nullptr;
	TreeNode *ans = path[0][0]; 	
	for (int i = 1; i < path[0].size() && i < path[1].size(); ++i) {
		if (path[0][i] != path[1][i]) break;
		ans = path[0][i];
	}
	return ans;
    }
};

// solution 2: hashtable
class Solution {
public:
        void preorder(TreeNode *root, unordered_map<TreeNode*, TreeNode*>& map) {
                if (root->left) {
                        map[root->left] = root;
                        preorder(root->left, map);
                }
                if (root->right) {
                        map[root->right] = root;
                        preorder(root->right, map);
                }
        }

    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        unordered_map<TreeNode*, TreeNode *> map;
        unordered_set<TreeNode*> visit;
        preorder(root, map);
        map[root] = nullptr;

        while (p) {
                visit.insert(p);
                p = map.at(p);
        }

        while (q) {
                if (visit.count(q)) return q;
                q = map.at(q);
        }
        return nullptr;
    }
};
*/

// solution 3: 直接在递归遍历中判断
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
	if (!root || root == p || root == q) return root;	
	TreeNode *l = lowestCommonAncestor(root->left, p, q); 		
	TreeNode *r = lowestCommonAncestor(root->right, p, q); 		
	if (!l) return r;
	else if (!r) return l;
	else return root;
    }
};

int main(int argc, char *argv[]) {

	return 0;
}
