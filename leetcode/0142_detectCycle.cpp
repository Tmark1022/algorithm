/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Tue 24 Nov 2020 03:03:33 PM CST
 @ File Name	: 0142_detectCycle.cpp
 @ Description	: 142. 环形链表 II  
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


// solution 1: hashtable 
// solution 2: floyd 判圈算法, 具体看题解(slow每次走一步， fast每次走两步， slow一定是在入圈后走不过一圈就被快的追上相遇)
// solution 3: 修改遍历过的节点, 到达入环节点时能检测出来（不过题意不允许修改原来的链表）
//		1) val 值设置为一个不可能出现的值
//		2) 遍历过的节点next都指向自己

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

// solution 2: Floyd 判圈算法
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
	// slow 和 fast 必须同一起点head， 不能像141写法, 不然slow 内层循环的slow 和 head 不能相遇
        ListNode *slow = head, *fast = head;

        while (fast != nullptr && fast->next != nullptr) {
                slow = slow->next;
                fast = fast->next->next;

                if (slow == fast) {
                        while (slow != head) {
                                slow = slow->next;
                                head = head->next;
                        }
                        return head;
                }
        }
        return nullptr;
    }
};

int main(int argc, char *argv[]) {

	return 0;
}
