/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Fri 06 Nov 2020 12:00:39 AM CST
 @ File Name	: 0155_MinStack.cpp
 @ Description	: 155. 最小栈
 ************************************************************************/
/*
// 解法思路参考 : https://leetcode-cn.com/problems/min-stack/solution/xiang-xi-tong-su-de-si-lu-fen-xi-duo-jie-fa-by-38/

solution 1: 利用两个栈实现， 一个存储数据， 一个存储最小值(存储最小值的可与数据存储的同步或不同步)
solution 2: 较为取巧， 使用一个stack， stack内装的是 {val, min_val}的二元组。该解法如果问题限定在只能使用存储单个整型变量的栈来实现时就走不通。
solution 3: 使用一个栈和一个min_val变量实现， 当最小值需要变化时， 把旧的最小值也压入栈中保存，pop出新的最小值时再恢复pop出来设置min_val值
solution 4: 使用一个栈和一个min_val变量实现，栈中保存的是x-min_val的差值， 差值是负数时min_val的转变是该方法的核心。 不过唯一需要注意的地方是这里使用到减法的差值， 所以需要注意两个int 减法溢出的问题，故需要使用long long 来存储差值（真是脑洞大开） 

*/

#include <iostream>

using std::cin;
using std::cout;
using std::endl;

class MinStack {
public:
    /** initialize your data structure here. */
    MinStack() {
        
    }
    
    void push(int x) {
        
    }
    
    void pop() {
        
    }
    
    int top() {
        
    }
    
    int getMin() {
        
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(x);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */





int main(int argc, char *argv[]) {

	return 0;
}
