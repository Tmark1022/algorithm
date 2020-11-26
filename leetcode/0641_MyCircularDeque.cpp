/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Thu 26 Nov 2020 10:55:02 AM CST
 @ File Name	: 0641_MyCircularDeque.cpp
 @ Description	: 641. 设计循环双端队列
 ************************************************************************/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stack>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::stack;

/*
	solution 1: 使用vector实现双向循环队列
	solution 2: 使用两个栈来实现 
	solution 3: 使用双向链表实现， 快等于就是直接调用接口了， 这里不具体实现了
*/



//// solution 1: 使用vector 实现, k肯定大于0
//class MyCircularDeque {
//public:
//    /** Initialize your data structure here. Set the size of the deque to be k. */
//    MyCircularDeque(int k):front(0), rear(0), size(0), capacity(k), vec(k, 0){ 
//    }
//    
//    /** Adds an item at the front of Deque. Return true if the operation is successful. */
//    bool insertFront(int value) {
//	if (size >= capacity) return false;
//	front = front ? front - 1: capacity - 1;
//	vec[front] = value;
//	++size;
//	return true;
//    }
//    
//    /** Adds an item at the rear of Deque. Return true if the operation is successful. */
//    bool insertLast(int value) {
//	if (size >= capacity) return false;
//	vec[rear] = value;
//	rear = (rear + 1) % capacity;		
//	++size;
//	return true;
//    }
//    
//    /** Deletes an item from the front of Deque. Return true if the operation is successful. */
//    bool deleteFront() {
//	if (size <= 0) return false; 
//	front = (front + 1) % capacity;
//	--size;	
//	return true;
//    }
//    
//    /** Deletes an item from the rear of Deque. Return true if the operation is successful. */
//    bool deleteLast() {
//	if (size <= 0) return false; 
//	rear = rear ? rear - 1 : capacity - 1;	
//	--size;	
//	return true;
//    }
//    
//    /** Get the front item from the deque. */
//    int getFront() {
//	if (size <= 0) return -1;
//	return vec[front];
//    }
//    
//    /** Get the last item from the deque. */
//    int getRear() {
//	if (size <= 0) return -1;
//	return vec[rear ? rear - 1 : capacity - 1];	
//    }
//    
//    /** Checks whether the circular deque is empty or not. */
//    bool isEmpty() {
//	return size <= 0;
//    }
//    
//    /** Checks whether the circular deque is full or not. */
//    bool isFull() {
//	return size >= capacity;
//    }
//
//private:	
//	// front 指向当前存储的首元素位置
//	// rear 指向当前存储的尾元素的下一个位置
//	int front, rear, size, capacity;
//	vector<int> vec;
//};



// solution 2: 使用两个栈实现, k大于0
class MyCircularDeque {
public:
    /** Initialize your data structure here. Set the size of the deque to be k. */
    MyCircularDeque(int k):size(0), capacity(k) {
    }
    
    /** Adds an item at the front of Deque. Return true if the operation is successful. */
    bool insertFront(int value) {
	if (size >= capacity) return false;	
	front.push(value);
	++size;
	return true;
    }
    
    /** Adds an item at the rear of Deque. Return true if the operation is successful. */
    bool insertLast(int value) {
	if (size >= capacity) return false;	
	rear.push(value);
	++size;
	return true;
    }
	
    // transfer all stack data from stk1 to stk2
    void transferStack(stack<int> &stk1, stack<int> &stk2) {
	while (!stk1.empty()) {
		stk2.push(stk1.top());
		stk1.pop();
	}	
    }
    
    /** Deletes an item from the front of Deque. Return true if the operation is successful. */
    bool deleteFront() {
	if (size <= 0) return false;	
	if (front.empty()) transferStack(rear, front);
	front.pop();
	--size;
	return true;
    }
    
    /** Deletes an item from the rear of Deque. Return true if the operation is successful. */
    bool deleteLast() {
	if (size <= 0) return false;	
	if (rear.empty()) transferStack(front, rear);
	rear.pop();
	--size;
	return true;
    }
    
    /** Get the front item from the deque. */
    int getFront() {
	if (size <= 0) return -1;	
	if (front.empty()) transferStack(rear, front);
	return front.top();	
    }
    
    /** Get the last item from the deque. */
    int getRear() {
	if (size <= 0) return -1;	
	if (rear.empty()) transferStack(front, rear);
	return rear.top();
    }
    
    /** Checks whether the circular deque is empty or not. */
    bool isEmpty() {
	return size<= 0;
    }
    
    /** Checks whether the circular deque is full or not. */
    bool isFull() {
	return size >= capacity;
    }
private:
	int size, capacity; 
	stack<int> front, rear;
};

/**
 * Your MyCircularDeque object will be instantiated and called as such:
 * MyCircularDeque* obj = new MyCircularDeque(k);
 * bool param_1 = obj->insertFront(value);
 * bool param_2 = obj->insertLast(value);
 * bool param_3 = obj->deleteFront();
 * bool param_4 = obj->deleteLast();
 * int param_5 = obj->getFront();
 * int param_6 = obj->getRear();
 * bool param_7 = obj->isEmpty();
 * bool param_8 = obj->isFull();
 */

int main(int argc, char *argv[]) {

	return 0;
}
