/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Fri 23 Oct 2020 08:55:52 PM CST
 @ File Name	: 0160_getIntersectionNode.cpp
 @ Description	: 160. 相交链表
 ************************************************************************/
#include <iostream>
#include <unordered_map>

using std::cin;
using std::cout;
using std::endl;
using std::unordered_map;

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:

	// solution1 : 穷举; time[O(MN)], space[O(1)]	
	



	// solution2 : 借助哈希表; time[O(M+N)], space[O(N)]
	/*
	ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
		unordered_map<ListNode *, int> m;	
		for (ListNode * p1 = headA; p1 != nullptr; p1 = p1->next) {
			m[p1] = 1;
		}	
		
		unordered_map<ListNode *, int>::iterator i_end = m.end();	
		for (ListNode * p2 = headB; p2 != nullptr; p2 = p2->next) {
			if (m.find(p2) != i_end) {
				// done 
				return p2;
			}
		}	
			
		return nullptr;
	}
	*/
	
	// solution3 : 双指针同时跑; 假设A链中不想交的部分为a, B链中不相交的部分为b, 两个链相交的部分为all, 总是存在有 a+all+b == b+all+a, 如果相交， 每个指针在跑完A链加B链前总能跑到一起; 如果不相交， 两个指针一同跑完， 值都为nullptr 
	ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
		ListNode *p1 = headA, *p2 = headB;
		while (p1 != p2) {
			p1 = p1 ? p1->next : headB;
			p2 = p2 ? p2->next : headA;
		}
		return p1;
	}

};






int main(int argc, char *argv[]) {

	return 0;
}
