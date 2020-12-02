/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Tue 01 Dec 2020 08:18:16 PM CST
 @ File Name	: 0297_serialize_and_deserialize.cpp
 @ Description	: 297. 二叉树的序列化与反序列化 
 ************************************************************************/
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <deque>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::ostringstream;
using std::istringstream;
using std::deque;

/*
	tips:
		1) 使用istringstream 来读取序列化数据	
		2) 使用ostringstream 来输出序列化数据

	solutions :
	1: dfs, 空节点使用X指示, 如下二叉树
	     1
	    / \
	   /   \
	 2       3
        / \     / \
       /   \   /   \
       X   X  4     5	
	     / \   / \
	    X  X  X   X
	
	序列化格式为 [1,2,X,X,3,4,X,X,5,X,X]

	2: bfs, 空节点使用null指示, 序列化格式参考leetcode 官方

	3: 保存先序和中序遍历的结果， 然后根据这两个结果构造二叉树，这里就不实现了
   */


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


/*
// solution 1: dfs【先序遍历】, 分隔符“,”使用空格" "替代，方便C++ istring 读取
#define DELIMITER " "
class Codec {
public:

	void DoSerialize(TreeNode *root, ostringstream &os)  {
		if (!root) {
			os << "x" << DELIMITER; 
			return ;
		}					
		os << std::to_string(root->val) << DELIMITER;	
		DoSerialize(root->left, os);
		DoSerialize(root->right, os);
	}
	
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
	ostringstream os;  		
	DoSerialize(root, os);
	return os.str();
    }

	TreeNode *DoDeserialize(istringstream &is) {
		string tmp;							
		is >> tmp;
		if (tmp == "x") return nullptr;
			
		TreeNode * root = new TreeNode(std::stoi(tmp));	
		root->left = DoDeserialize(is);
		root->right = DoDeserialize(is);
		return root;
	}

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
	istringstream is(data);		
	return DoDeserialize(is);	
    }
};
*/

// solution 2: bfs, 分隔符“,”使用空格" "替代，方便C++ istring 读取
#define DELIMITER " "
class Codec {
public:	
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
	ostringstream os;  		
	deque<TreeNode*> que;
	que.push_back(root);

	while (que.size()) {
		TreeNode * cur = que.front();	
		que.pop_front();
		if (!cur) {
			os << "x" << DELIMITER;
		} else {		
			os << std::to_string(cur->val) << DELIMITER;
			que.push_back(cur->left);
			que.push_back(cur->right);
		}
	}
	return os.str();
    }

    /*
	// 这个版本是上边serialize 函数的优化版，剔除了最后连续的x
    string serialize(TreeNode* root) {
        ostringstream os;
        deque<TreeNode*> que;
        que.push_back(root);
        TreeNode *last = root;
        while (que.size()) {
                TreeNode * cur = que.front();
                que.pop_front();
                if (!cur) {
                        os << "x" << DELIMITER;
                } else {
                        os << std::to_string(cur->val) << DELIMITER;
                        que.push_back(cur->left);  
                        if (cur->left) last = cur->left; 
                        que.push_back(cur->right);
                        if (cur->right) last = cur->right; 
                }
                if (cur == last) break;
        }
        return os.str();
    }
    */

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
	istringstream is(data);		
	TreeNode *root = nullptr;
	deque<TreeNode **> que;
	que.push_back(&root);	
	string tmp;
	while (is >> tmp) {
		TreeNode **cur = que.front();	
		que.pop_front();	
		if ("x" == tmp) {
			*cur = nullptr;
		} else {
			*cur = new TreeNode(std::stoi(tmp));	
			que.push_back(&(*cur)->left);							
			que.push_back(&(*cur)->right);							
		}	
	}
	return root;
    }
};

int main(int argc, char *argv[]) {

	return 0;
}
