/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Wed 02 Dec 2020 08:13:41 PM CST
 @ File Name	: 0449_serialize_and_deserialize.cpp
 @ Description	: 449. 序列化和反序列化二叉搜索树 
 ************************************************************************/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <deque>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


/*
	solution 1: 可以直接使用 leetcode 297 二叉树的序列化和反序列化来实现
	
	solution 2: solution 1中没有使用到BST的特性，而是在序列化的数据中使用x等来标记空节点， 进而来指定二叉树的结构
		而对于BST树， 我们可以利用其特性（当前节点大于左子树所有节点， 小于右子树所有节点）来指定二叉树的结构。
		这里我们只需要BST树的先序遍历结果即可进行反序列化【其实BST的中序遍历就是有序数组， 所以其实知道其先序或后序遍历结果都能构造出来】
   */

// solution 2: 递归， 依据BST先序遍历结果, 这里使用空格“ ”替代“,”， 方便C++ istringstream读取
#define DELIMITER " "
class Codec {
public:
	void DoSerialize(TreeNode *root, ostringstream &os) {
		if (!root) return ;
		os << to_string(root->val) << DELIMITER;
		DoSerialize(root->left, os);
		DoSerialize(root->right, os);
	}

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
	ostringstream os;  
	DoSerialize(root, os);
	return os.str();
    }

    TreeNode * DoDeserialize(deque<int>& pre, int lower, int upper) {
	if (!pre.size() || pre.front() <= lower || pre.front() >= upper) return nullptr;
	TreeNode * root = new TreeNode(pre.front());
	pre.pop_front();
	root->left = DoDeserialize(pre, lower, root->val);
	root->right = DoDeserialize(pre, root->val, upper);	
	return root;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
	// buildtree 时需要取值来判断大小， 故不能直接使用istringstream, 因为 >> 取值了后， 下次就不能继续取了
	istringstream is(data);    	
	deque<int> pre;
	string tmp;
	while (is >> tmp) {
		pre.push_back(stoi(tmp));
	}
	return DoDeserialize(pre, -10001, 10001);	
    }
};




int main(int argc, char *argv[]) {

	return 0;
}
