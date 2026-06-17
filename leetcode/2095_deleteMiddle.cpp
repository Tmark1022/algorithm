/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Wed 17 Jun 2026 11:35:13 AM CST
 @ File Name	: 2095_deleteMiddle.cpp
 @ Description	: 2095. 删除链表的中间节点
 ************************************************************************/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
#include <deque>
#include <unordered_map>
#include <unordered_set>

using namespace std;


// solution 1: 两遍循环， 第一遍找到链表长度N， 第二遍遍历到middle 然后删除
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* deleteMiddle(ListNode* head) {
        int n = 0;
        for (auto cur = head; cur; cur = cur->next) ++n;

        int m = n / 2;
        if (!m) return head->next;

        ListNode *prev = nullptr, *cur = head;
        for (int i = 0; i < m; ++i) {
            prev = cur;
            cur = cur->next;
        }
        prev->next = cur->next;
        return head;
    }
};

// solution 2: 快慢指针， 一遍循环 
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* deleteMiddle(ListNode* head) {
       ListNode *prev = nullptr, *cur = head, *fast = head;  
       while (fast && fast->next) {
        prev = cur;
        cur = cur->next;
        fast = fast->next->next;
       }

       if (prev) {
            prev->next = cur->next;
            return head;
       } else {
            return head->next;
       }
    }
};

int main(int argc, char *argv[]) {

	return 0;
}
