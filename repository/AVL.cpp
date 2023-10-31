/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Fri 06 Nov 2020 10:21:26 AM CST
 @ File Name	: AVL.cpp
 @ Description	: 参考geeks for geeks AVL 树的描述 
 ************************************************************************/
#include <cstdint>
#include <iostream>
#include <cmath>
#include <bits/stdc++.h>
#include <ostream>
#define MAXN 2000

using namespace std;

/* The structure of the Node is */
struct Node
{
    int data;
    Node *left;
    Node *right;
    int height;

    Node() = default;
    Node(int x):data(x), left(nullptr), right(nullptr), height(1) {}
};

int Height(Node * node) 
{
    if (nullptr == node) return 0;
    return node->height;
}

int Balance(Node * node) 
{
	return Height(node->left) - Height(node->right);
}

// 右旋操作, 返回旋转后子树的根
Node * RightRotation(Node * node)  
{	
	Node * tmp = node->left;	
	node->left = tmp->right;
	tmp->right = node;	

	// update height	
	node->height = std::max(Height(node->left), Height(node->right)) + 1;	
	tmp->height = std::max(Height(tmp->left), Height(tmp->right)) + 1;
	
	return tmp;
}

// 左旋操作, 返回旋转后子树的根
Node * LeftRotation(Node * node)  
{
	Node * tmp = node->right;	
	node->right = tmp->left;
	tmp->left = node;	

	// update height	
	node->height = std::max(Height(node->left), Height(node->right)) + 1;	
	tmp->height = std::max(Height(tmp->left), Height(tmp->right)) + 1;
	
	return tmp;
}

// re-balance with LL case 
Node * SingleRotateWithLL(Node * node)
{
	return RightRotation(node);
}

// re-balance with LR case 
Node * DoubleRotateWithLR(Node * node)
{
	node->left = LeftRotation(node->left);
	return RightRotation(node);
}

// re-balance with RR case 
Node * SingleRotateWithRR(Node * node)
{
	return LeftRotation(node);
}

// re-balance with RL case 
Node * DoubleRotateWithRL(Node * node)
{
	node->right = RightRotation(node->right);
	return LeftRotation(node);
}

/*
// 插入时， CheckBalancePorperty(Node *node) 可以这样实现
// 删除时， 只能使用下边的实现， 下边的实现也能用在插入
Node * CheckBalanceProperty(Node *node, int data)  
{
	if (Balance(node) > 1) {
		if (data < node->left->key) {
			// LL case
			node = SingleRotateWithLL(node);
		} else {
			// LR case
			node = DoubleRotateWithLR(node);
		}
	} else if (Balance(node) < -1) {
		if (data > node->right->key) {
			// RR case
			node = SingleRotateWithRR(node);
		} else {
			// RL case
			node = DoubleRotateWithRL(node);
		}
	}
	return node;
}
*/

Node * CheckBalanceProperty(Node *node)  
{		
	if (Balance(node) == 2) {
		if (Balance(node->left) >= 0) {			// 插入节点时， 不会出现 == 0 的情况; 删除时， 会出现 == 0 的情况
			// LL case
			node = SingleRotateWithLL(node);
		} else {
			// LR case
			node = DoubleRotateWithLR(node);
		}
	} else if (Balance(node) == -2) {
		if (Balance(node->right) <= 0) {
			// RR case
			node = SingleRotateWithRR(node);
		} else {
			// RL case
			node = DoubleRotateWithRL(node);
		}
	}

	return node;
}

/*You are required to complete this method */
Node* insertToAVL(Node* node, int data)
{
	if (nullptr == node) {
		Node * new_node =  new Node(data); 
		return new_node;
	}		

	if (data < node->data) {
		node->left = insertToAVL(node->left, data);
	} else if (data > node->data) {
		node->right = insertToAVL(node->right, data);
	} else {
		// already exist, do noting
		return node;	
	}

	// check balance property
	// node = CheckBalanceProperty(node, data);  
	node = CheckBalanceProperty(node);  
	
	// update height	
	node->height = std::max(Height(node->left), Height(node->right)) + 1;	
	return node;
}

// 查找子树node的最小节点
Node * FindMin(Node * node) 
{
	if (nullptr == node) {
		return nullptr;
	}	

	while (node->left != nullptr) {
		node = node->left;
	}

	return node;
}

// 查找子树node的最大节点
Node * FindMax(Node * node) 
{
	if (nullptr == node) {
		return nullptr;
	}	

	while (node->right != nullptr) {
		node = node->right;
	}

	return node;
}

Node* deleteNode(Node* root, int data)
{ 
	// 遵循BST的删除方式， 然后对路径进行re-balance检查 
	if (nullptr == root) {
		return root;
	}		

	if (data < root->data) {
		root->left = deleteNode(root->left, data);
	} else if (data > root->data) {
		root->right = deleteNode(root->right, data);
	} else {
		// BST 的删除方式	
		if (nullptr == root->left || nullptr == root->right) {
			Node * tmp = root;
			root = root->left ? root->left : root->right;
			delete tmp;

			// root 为被删除的节点的某一子树（有可能为nullptr）， 因为原本的子树肯定平衡的， 故这里无需继续进行下面的逻辑
                        return root;
		} else {
			// 删除节点左右子树都存在， 找后驱节点替换删除
			Node * del_node = FindMin(root->right); 	
			root->data = del_node->data;
			root->right = deleteNode(root->right, del_node->data);	
		}
	}	
	
	// check balance property
	root = CheckBalanceProperty(root);  
	
	// update height	
	root->height = std::max(Height(root->left), Height(root->right)) + 1;	
	return root;
}


/***************************************************
* 测试检验代码 
***************************************************/
// 先序遍历判断是否为BST 树
bool isBST(Node *n, int lower, int upper)
{
	if(!n) return 1;
	if( n->data <= lower || n->data >= upper ) return 0;
	return isBST(n->left, lower, n->data) && isBST(n->right, n->data, upper) ;
}

// 后序遍历判断 AVL 树的平衡因子
pair<int,bool> isBalanced(Node* n)
{
	if(!n) return pair<int,bool> (0,1);

	pair<int,bool> l = isBalanced(n->left);
	pair<int,bool> r = isBalanced(n->right);

	if( abs(l.first - r.first) > 1 ) return pair<int,bool> (0,0);

	return pair<int,bool> ( 1 + max(l.first , r.first) , l.second && r.second );
}

bool isBalancedBST(Node* root)
{
	if( !isBST(root, INT_MIN, INT_MAX) )
		cout<< "BST voilated, inorder traversal : ";

	else if ( ! isBalanced(root).second )
		cout<< "Unbalanced BST, inorder traversal : ";

	else return 1;
	return 0;
}

void printInorder(Node* n)
{
	if(!n) return;
	printInorder(n->left);
	cout<< n->data << " ";
	printInorder(n->right);
}

Node* insertToAVL( Node* node, int data);

int main()
{
	int ip[MAXN];
    
    int t;
	cout << "loop cnt : ";
	std::flush(cout);
	
    cin>>t;
    while(t--)
    {
	cout << "input cnt : ";
	std::flush(cout);
	
        int n;
        cin>>n;
        
	cout << "input data list : " ;
	std::flush(cout);
        for(int i=0; i<n; i++)
            cin>> ip[i];
        
        Node* root = NULL;
        
	cout << "begin to run" << endl; ;
        for(int i=0; i<n; i++)
        {
            root = insertToAVL( root, ip[i] );
            
            if ( ! isBalancedBST(root) )
                break;
        printInorder(root);
	cout << endl;
        }
        
        printInorder(root);
        cout<< endl;
    }
    return 0;
}// } Driver Code Ends

