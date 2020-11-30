/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Mon 30 Nov 2020 02:14:59 PM CST
 @ File Name	: 0889_constructFromPrePost.cpp
 @ Description	: 889. 根据前序和后序遍历构造二叉树 
 ************************************************************************/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::unordered_map;


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// solution 1: 递归， 假设先序遍历中当前节点的下一个节点总是左子树的
class Solution {
public:
    TreeNode* constructFromPrePost(vector<int>& pre, int pre_begin, int pre_end, vector<int>& post, int post_begin, int post_end, unordered_map<int, int>& map) {
        if (pre_begin > pre_end) return nullptr;
        else if (pre_begin == pre_end) return new TreeNode(pre[pre_begin]);

        int left_pivot = map[pre[pre_begin + 1]];       // 左孩子节点在后序排序中的idx
        int cnt = left_pivot - post_begin + 1;          // 左子树有多少个节点
        TreeNode *root = new TreeNode(pre[pre_begin]);
        root->left = constructFromPrePost(pre, pre_begin+1, pre_begin+cnt, post, post_begin, left_pivot, map);
        root->right= constructFromPrePost(pre, pre_begin+cnt+1, pre_end, post, left_pivot+1, post_end, map);
        return root;
    }

    TreeNode* constructFromPrePost(vector<int>& pre, vector<int>& post) {
        int len = post.size();
        if (!len) return nullptr;
        unordered_map<int, int> map;
        for (int i = 0; i < len; ++i) map[post[i]] = i;
        return constructFromPrePost(pre, 0, len-1, post, 0, len-1, map);
    }
};


int main(int argc, char *argv[]) {

	return 0;
}
