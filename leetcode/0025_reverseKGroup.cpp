/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Tue 24 Nov 2020 07:53:39 PM CST
 @ File Name	: 0025_reverseKGroup.cpp
 @ Description	: 25. K 个一组翻转链表 
 ************************************************************************/
#include <iostream>
#include <utility>
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


/*
// solution 1: 迭代
class Solution {
public:
        // 反转 [begin, end), 并返回反转后的头和尾指针
        std::pair<ListNode*, ListNode*> ReverseList(ListNode *begin, ListNode *end) {
                ListNode dummy;
                ListNode *cur = begin, *next;
                while (cur != end) {
                        next = cur->next;
                        cur->next = dummy.next;
                        dummy.next = cur;
                        cur = next;
                }
                return std::make_pair(dummy.next, begin);
        }

    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode dummy(0, head);
        ListNode *prev = &dummy, *next;
        int count;
        while (true) {
                for (count = 0, next = prev->next; next && count < k; ++count,next=next->next);
                if (count != k) break;
                auto tmp = ReverseList(prev->next, next);
                prev->next = tmp.first;
                tmp.second->next = next;
                prev = tmp.second;
        }
        return dummy.next;
    }
};
*/

// solution 2: 递归
class Solution {
public:
        // 反转 [begin, end), 并返回反转后的头指针
        ListNode* ReverseList(ListNode *begin, ListNode *end) {
                ListNode dummy;
                ListNode *cur = begin, *next;
                while (cur != end) {
                        next = cur->next;
                        cur->next = dummy.next;
                        dummy.next = cur;
                        cur = next;
                }
		return dummy.next;
        }

    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode *next;
        int count;
        for (count = 0, next = head; next && count < k; ++count,next=next->next);
        if (count != k) return head;
        ListNode* new_head = ReverseList(head, next);
	head->next = reverseKGroup(next, k);		// 反转过后的最后一个节点就是head
	return new_head;
    }
};

int main(int argc, char *argv[]) {

	return 0;
}
