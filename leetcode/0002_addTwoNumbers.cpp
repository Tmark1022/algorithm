/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Wed 21 Oct 2020 07:47:37 PM CST
 @ File Name	: 0002_addTwoNumbers.cpp
 @ Description	: 2. 两数相加


给出两个 非空 的链表用来表示两个非负的整数。其中，它们各自的位数是按照 逆序 的方式存储的，并且它们的每个节点只能存储 一位 数字。
如果，我们将这两个数相加起来，则会返回一个新的链表来表示它们的和。
您可以假设除了数字 0 之外，这两个数都不会以 0 开头。

示例：

输入：(2 -> 4 -> 3) + (5 -> 6 -> 4)
输出：7 -> 0 -> 8
原因：342 + 465 = 807

 ************************************************************************/
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

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
	// 解法1
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode * l3 = new ListNode();
        ListNode * cur = l3;
        int carry = 0;  // 进位
        int sum;
        while (l1 || l2) {
                sum = (l1 ? l1->val : 0) + (l2 ? l2->val : 0) + carry;
                cur->next = new ListNode(sum % 10);
                cur = cur->next;
                carry = sum / 10;
                l1 && (l1 = l1->next);
                l2 && (l2 = l2->next);
        }
        
        if (carry) {
                cur->next = new ListNode(carry);
        }
        return l3->next;
    }

    */

		 

	// 解法二， 使用递归，简洁	
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		return foo(l1, l2, 0);
	}

	ListNode * foo(ListNode *l1, ListNode *l2, int carry) {
		if (!l1 && !l2 && !carry) {
			return nullptr;
		}

		int val1 = l1 ? l1->val : 0;			
		int val2 = l2 ? l2->val : 0; 
		int sum = val1 + val2 + carry;
		
		ListNode * tmp = new ListNode(sum % 10); 	

        	l1 && (l1 = l1->next);
		l2 && (l2 = l2->next);
		tmp->next = foo(l1, l2, sum / 10);
		
		return tmp;	
	}	

};


int main(int argc, char *argv[]) {

	return 0;
}
