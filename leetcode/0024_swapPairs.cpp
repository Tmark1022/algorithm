/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Thu 12 Nov 2020 08:06:26 PM CST
 @ File Name	: 0024_swapPairs.cpp
 @ Description	: 24. 两两交换链表中的节点 
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

class Solution {
public:
	/*
	// solution 1: 迭代
    ListNode* swapPairs(ListNode* head) {
	// 借助一个哨兵 
	ListNode sentinel;	
	sentinel.next = head;

	ListNode *ptr = &sentinel, *cur=head, *next;
	while (cur) {
		next = cur->next;
		if (!next) break; 
		
		cur->next = next->next;	
		next->next = cur;
		ptr->next = next;

		ptr = cur;	
		cur = cur->next;
	}
	
	return sentinel.next;
    }
    */

	// solution 2: 递归, 可以通过递归的方式实现两两交换链表中的节点。递归的终止条件是链表中没有节点，或者链表中只有一个节点，此时无法进行交换。
    ListNode* swapPairs(ListNode* head) {
	if (nullptr == head || nullptr == head->next) {
		return head;	
	}

	ListNode * next = head->next;
	head->next = swapPairs(next->next);
	next->next = head;
	return next;
    }
};

int main(int argc, char *argv[]) {

	return 0;
}
