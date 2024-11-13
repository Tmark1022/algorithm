/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Tue 24 Nov 2020 02:02:09 PM CST
 @ File Name	: 0141_hasCycle.cpp
 @ Description	: 141. 环形链表 
 ************************************************************************/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_set>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::unordered_set;


/**
 * Definition for singly-linked list.
*/
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

/*
// solution 1: hashtable
class Solution {
public:
    bool hasCycle(ListNode *head) {
	unordered_set<ListNode*> set;	
	while (head != nullptr) {
		if (set.find(head) != set.end()) {
			return true;
		}		
		set.insert(head);
		head = head->next;
	}
	return false; 
    }
};
*/

/*
// solution 2: Floyd 判圈算法, 快慢指针
class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode *slow = head, *fast = head;
        while (fast && fast->next) {
            slow = slow->next; 
            fast = fast->next->next;
            if (slow == fast) return true;
        } 
        return false; 
    }

};
*/

/*
// solution 3: 遍历过程中， 修改节点值， 用于判断是否有环(判断结束点其实也就是入环点)
//		1): 因为-10^5 <= Node.val <= 10^5, 可以把遍历过的节点值都修改为100001 
//		2): 每个遍历过的节点的next指向自身,
class Solution {
public:
    bool hasCycle(ListNode *head) {
	ListNode * next;
	while (head) {
		if (head->next == head) return true;
		// 指向自己
		next = head->next; 
		head->next = head;
		head = next;
	}
	return false;
    }

    bool hasCycle(ListNode *head) {
        while (head) {
                if (head->val == 100001) return true;
                head->val = 100001;
                head = head->next;
        }
        return false;
    }
};
*/


// solution 4: 反转链表, 如果有环，反转后的头节点依然是head, 要排除只有一个节点的情况
//
class Solution {
public:
    bool hasCycle(ListNode *head) {
	if (nullptr == head || nullptr == head->next) return false; 
	ListNode * prev = nullptr, *cur = head, *next;
	while (cur) {
		next = cur->next;
		cur->next = prev;
		prev = cur;
		cur = next;
	}	
	return prev == head; 
    }

};


int main(int argc, char *argv[]) {

	return 0;
}
