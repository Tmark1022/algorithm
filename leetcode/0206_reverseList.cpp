/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Thu 12 Nov 2020 07:38:18 PM CST
 @ File Name	: 0206_reverseList.cpp
 @ Description	: 206. 反转链表
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
    ListNode(int x) : val(x), next(NULL) {}
};


class Solution {
public:
	/*
	// solution 1: 迭代， 双指针， 一个pre， 一个cur
    ListNode* reverseList(ListNode* head) {
	ListNode * pre = nullptr, *cur = head, *nextptr;
	while(cur) {
		nextptr = cur->next;	
		cur->next = pre;
		pre = cur;
		cur = nextptr;
	}		
	return pre;	
    }
    */

/*
	// solution 2: 迭代, 后续的链表节点每次插入到头节点中， 这里借助一个哨兵节点来方便编码
    ListNode* reverseList(ListNode* head) {
	ListNode sentinel(0);
	ListNode *nextptr;

	while(head) {
		nextptr = head->next;	
		head->next = sentinel.next;
		sentinel.next = head;
		head = nextptr;
	}		
	return sentinel.next;	
    }
    */

	// solution 3:递归
	/*
	使用递归函数，一直递归到链表的最后一个结点，该结点就是反转后的头结点，记作 ret.
	此后，每次函数在返回的过程中，让当前结点的下一个结点的 next 指针指向当前节点。
	同时让当前结点的 next 指针指向 NULL ，从而实现从链表尾部开始的局部反转
	当递归函数全部出栈后，链表反转完成。
	*/
	/*
    ListNode* reverseList(ListNode* head) {
	// terminator
	if (nullptr == head || nullptr == head->next) {
		return head;	
	}

	ListNode *ret = reverseList(head->next);
	head->next->next = head;
	head->next = nullptr;
	return ret;
    }
    */


	// solution 4:递归, solution 2的强行递归解法(尾递归)
	void reverseListRecursion(ListNode * head, ListNode *sentinel) {
		if (nullptr == head) {
			return ;
		}

		ListNode * nextptr = head->next;
		head->next = sentinel->next;
		sentinel->next = head;
		reverseListRecursion(nextptr, sentinel);
	}


    ListNode* reverseList(ListNode* head) {
	// terminator
	ListNode sentinel(0);
	reverseListRecursion(head, &sentinel);
	return sentinel.next; 
    }


};



int main(int argc, char *argv[]) {

	return 0;
}
