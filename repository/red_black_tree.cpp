/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Wed 31 Mar 2021 11:23:53 AM CST
 @ File Name	: red_black_tree.cpp
 @ Description	: 红黑树实现 
 ************************************************************************/
#include <iostream>
#include <ostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
#include <deque>
#include <unordered_map>
#include <unordered_set>

using namespace std;

/***************************************************
* 数据类型定义 
***************************************************/
#define COLOR_RED	false  
#define COLOR_BLACK	true	
struct Node {
	int val;		
	bool color;	
	Node *left, *right, *parent;
	Node(int v = 0, bool c = COLOR_RED):val(v), color(c), left(nullptr), right(nullptr), parent(nullptr) {}
};

ostream & operator<<(ostream &out, const Node & node) {
	out << "<" << (node.color == COLOR_RED ? "R : " : "B : ") << node.val << ">";
	return out;
}

// 红黑树定义
class RBTree {
public:
	RBTree():root(nullptr), count(0) {}	
	~RBTree() {
		if (root) {
			FreeTree(root);
			root = nullptr;
			cout << "==== FreeTree ==== " << endl;
		}	
	}	

	// 二叉树 postorder 释放红黑树
	void FreeTree(Node * pcur) {		
		if (nullptr == pcur) return ; 
		FreeTree(pcur->left);
		FreeTree(pcur->right);
		delete pcur;
	}

	int size() const {
		return count;
	}

	Node * GetRoot() const {
		return root;
	}
	
	/***************************************************
	* traversal 
	***************************************************/
	void InOrderTraversal(const Node *pnode) const ;
	void LevelOrderTraversal(const Node *pnode) const ;

	/***************************************************
	* rotation 
	***************************************************/
	void LeftRotation(Node * pnode);
	void RightRotation(Node * pnode);

	/***************************************************
	* search 
	***************************************************/
	Node *Search(int val) {
		return SearchHelp(root, val);
	}		
	Node *SearchHelp(Node *pcur, int val);		

	/***************************************************
	* insertion 
	***************************************************/
	void Insert(int val) {
		if (Search(val)) return ;				// 已经存在	
		Node * pnode = new Node(val, COLOR_RED); 
		root = BSTInsert(root, pnode);
		ReblanceAfterInsert(pnode);
		++count;
	}
	
	Node *BSTInsert(Node *pcur, Node *pnode);	
	void ReblanceAfterInsert(Node * pnode);	
	

	/***************************************************
	* removal 
	***************************************************/
	void Delete(Node *pnode);		

private:
	Node * root;
	int count;
};


/***************************************************
* 成员函数类外定义 
***************************************************/
void RBTree::InOrderTraversal(const Node *pnode) const {
	if (!pnode) return ;				
	InOrderTraversal(pnode->left);
	cout << *pnode << endl;	
	InOrderTraversal(pnode->right);
}

void RBTree::LevelOrderTraversal(const Node *pnode) const {
	if (!pnode) return ;
	deque<const Node *> que = {pnode};
	while (que.size()) {
		for (int cnt = que.size(); cnt; --cnt) {
			const Node * p = que.front();
			que.pop_front();
			cout << *p << " "; 
			if (p->left) que.push_back(p->left);	
			if (p->right) que.push_back(p->right);	
		}
		cout << endl;
	}

}

void RBTree::LeftRotation(Node * pnode) {
	Node *right_child = pnode->right; 	
	// part 1:	
	pnode->right = right_child->left;	
	if (right_child->left) right_child->left->parent = pnode;

	// part 2:
	right_child->parent = pnode->parent;
	if (pnode->parent == nullptr) {
		// pnode 原来是根
		root = right_child;			// 更新新的根指针
	} else if (pnode == pnode->parent->left) {
		// pnode 是其父亲的左孩子
		pnode->parent->left = right_child;
	} else {
		// pnode 是其父亲的右孩子
		pnode->parent->right = right_child;
	}
	
	// part 3:
	right_child->left = pnode;	
	pnode->parent = right_child;
}

void RBTree::RightRotation(Node * pnode) {
	Node *left_child = pnode->left; 	
	
	// part 1:	
	pnode->left = left_child->right;	
	if (left_child->right) left_child->right->parent = pnode;

	// part 2:
	left_child->parent = pnode->parent;
	if (pnode->parent == nullptr) {
		// pnode 原来是根
		root = left_child;			// 更新新的根指针
	} else if (pnode == pnode->parent->left) {
		// pnode 是其父亲的左孩子
		pnode->parent->left = left_child;
	} else {
		// pnode 是其父亲的右孩子
		pnode->parent->right = left_child;
	}
	
	// part 3:
	left_child->right = pnode;	
	pnode->parent = left_child;
}


Node * RBTree::SearchHelp(Node *pcur, int val) {
	// BST 的查找方式	
	if (pcur == nullptr) return pcur;		
	if (pcur->val == val) return pcur;
	else if (pcur->val > val) return SearchHelp(pcur->left, val); 
	else return SearchHelp(pcur->right, val);
}

Node * RBTree::BSTInsert(Node *pcur, Node *pnode) {
	// terminator
	if (pcur == nullptr) {
		return pnode;
	}

	if (pcur->val > pnode->val) {
		pcur->left = BSTInsert(pcur->left, pnode); 		
		pcur->left->parent = pcur;
	} else {
		pcur->right = BSTInsert(pcur->right, pnode);
		pcur->right->parent = pcur;
	}	
	return pcur;
}

void RBTree::ReblanceAfterInsert(Node * pnode) {
	// case 1: 是否为根节点
	if (pnode == root) {
		pnode->color = COLOR_BLACK;
	} else {
		// case 2: 父亲节点的颜色?
		Node *parent = pnode->parent;	
		if (parent->color == COLOR_BLACK) {
			// 父亲颜色为黑色， 可以直接结束
			return ; 
		} else {
			// 父亲颜色为红色
			Node * grandpa = parent->parent; // 父亲为红色，根据红黑树的定义， 父亲节点绝对不是根节点， 所以肯定有祖父节点的存在 
			Node * uncle = nullptr;		// uncle 节点有可能是NIL 节点【也算是黑色节点】
			if (parent == grandpa->left) uncle = grandpa->right;	
			else uncle = grandpa->left;

			// case 3 : uncle 的颜色?
			if (uncle && uncle->color == COLOR_RED) {
				// uncle 为红色
				grandpa->color = COLOR_RED;		
				parent->color = uncle->color = COLOR_BLACK;
				ReblanceAfterInsert(grandpa);			// 以grandpa节点为起点，递归调用ReblanceAfterInsert
			} else {
				// uncle 为黑色, 分四种情况进行rotation
				if (parent == grandpa->left) {
					if (pnode == parent->left)  {
						// case 1: left left case
						RightRotation(grandpa);		
						swap(parent->color, grandpa->color);
					} else {
						// case 2: left right case
						LeftRotation(parent);
						swap(parent, pnode);
						RightRotation(grandpa);		
						swap(parent->color, grandpa->color);
					}
				} else {
					if (pnode == parent->right) {
						// case 3: right right case
						LeftRotation(grandpa);	
						swap(parent->color, grandpa->color);
					} else {
						// case 4: right left case
						RightRotation(parent);	
						swap(parent, pnode);
						LeftRotation(grandpa);
						swap(parent->color, grandpa->color);
					}
				}	
			}
		}
	}	
}

/***************************************************
* 测试用例 
***************************************************/
void TestSearch(RBTree &rbt, int val) {
	Node *res = rbt.Search(val);		
	cout << "find val : " << val << " ==> ";
	if (res) cout << *res << endl;	
	else cout << "not found" << endl;
}

void PrintTraversalData(const RBTree &rbt) {
	cout << "rbt size is : " << rbt.size() << endl;;
	cout << "================= InOrderTraversal ============ " << endl;
	rbt.InOrderTraversal(rbt.GetRoot());
	cout << "================= LevelOrderTraversal ============ " << endl;
	rbt.LevelOrderTraversal(rbt.GetRoot());
}

void TestEntry() {
	RBTree rbt;
	rbt.Insert(3);
	rbt.Insert(21);
	rbt.Insert(32);
	rbt.Insert(15);

	TestSearch(rbt, 10);
	TestSearch(rbt, 20);
	TestSearch(rbt, 15);
	TestSearch(rbt, 32);
	TestSearch(rbt, 21);
	TestSearch(rbt, 3);
	cout << "size : " << rbt.size() << endl;

	PrintTraversalData(rbt);
	rbt.Insert(17);
	PrintTraversalData(rbt);
		
	rbt.Insert(33);
	PrintTraversalData(rbt);
	rbt.Insert(34);
	PrintTraversalData(rbt);

	rbt.Insert(35);
	PrintTraversalData(rbt);
	rbt.Insert(-1);
	PrintTraversalData(rbt);
	rbt.Insert(4);
	PrintTraversalData(rbt);
	rbt.Insert(-100);
	PrintTraversalData(rbt);


}

int main(int argc, char *argv[]) {
	TestEntry();
	return 0;
}
