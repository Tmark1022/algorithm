/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Wed 25 Nov 2020 03:41:18 PM CST
 @ File Name	: 0021_mergeTwoLists.cpp
 @ Description	: 21. 合并两个有序链表
 ************************************************************************/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// solution 1: 迭代实现
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
	ListNode dummy;       
	ListNode *prev = &dummy;	
	while (l1 && l2) {
		if (l1->val <= l2->val) {
			prev->next = l1;	
			l1 = l1->next;
		} else {
			prev->next = l2;	
			l2 = l2->next;
		}
		prev = prev->next;	
	}
	prev->next = l1 ? l1 : l2;
	return dummy.next;
    }
};

/*
// solution 2: 递归实现
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
	// terminator
	if (!l1) return l2;	 
	if (!l2) return l1;

	if (l1->val <= l2->val) {
		l1->next = mergeTwoLists(l1->next, l2);
		return l1;
	} else {
		l2->next = mergeTwoLists(l1, l2->next);
		return l2;
	}
    }
};
*/

int main(int argc, char *argv[]) {

	return 0;
}
