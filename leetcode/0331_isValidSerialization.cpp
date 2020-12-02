/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Wed 02 Dec 2020 08:47:23 PM CST
 @ File Name	: 0331_isValidSerialization.cpp
 @ Description	: 331. 验证二叉树的前序序列化 
 ************************************************************************/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

using namespace std;

/*
// solution 1: 按照序列化数据构造二叉树， 看是否合法(需要刚好用完preorder的内容), 不过按题意， 并不允许在通过构造二叉树来判断
class Solution {
public:
    bool isValidSerialization(istringstream &is) {		
	if (is.eof()) return false;
	string tmp;		
	getline(is, tmp, ',');
	if ("#" == tmp) {
		return true;	
	} else {	
		// 判断左子树 和 右子树
		return isValidSerialization(is) && isValidSerialization(is); 
	}
    }

    bool isValidSerialization(string preorder) {		
	if (!preorder.size()) return true; 
	istringstream is(preorder);	
	bool flag = isValidSerialization(is);
	return flag && is.eof(); 	
    }
};
*/

// solution 2: 计算槽位 
//		1) # 占一个槽位
//		2) 非# 占一个槽位， 同时产生两个槽位

class Solution {
public:
    bool isValidSerialization(string preorder) {		
	if (!preorder.size()) return true; 
	istringstream is(preorder);	

	int slots = 1;
	string tmp;
	while (getline(is, tmp, ',')) {
		if (--slots < 0) return false;
		if ("#" != tmp) slots += 2;
	}
	return 0 == slots;
    }
};


int main(int argc, char *argv[]) {

	return 0;
}
