/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Fri 06 Nov 2020 05:45:50 PM CST
 @ File Name	: delegating_constructor.cpp
 @ Description	: 测试委托构造函数的执行过程 
 ************************************************************************/
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int foo_b(void)
{
	cout << "call foo_b" << endl;
	return 100;
}

int foo_a(void)
{
	cout << "call foo_a" << endl;
	return 100;
}


class Solution {
public:
	Solution(int a, int b, int c):b(foo_b()), a(foo_a()), c(c){
		cout << "call Solution(int a, int b, int c) function body." << endl;
	}

	// delegating constuctor
	// 初始值列表中只能有唯一的被调用的构造函数， 不能有其他了
	Solution(): Solution(0,0,0) {
		cout << "call delegating constuctor  function body." << endl;	
	}

private:
	int a;
       	int b, c;

};


int main(int argc, char *argv[]) {
	Solution obj;
	return 0;
}
