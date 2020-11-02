/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Mon 02 Nov 2020 05:40:42 PM CST
 @ File Name	: cpp_type.cpp
 @ Description	: 
 ************************************************************************/
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

void func(int, int);
class Solution {
	// 友元仅仅指定了访问权限（能访问该类的私有成员等）， 但不是真正意义上的函数声明。
	friend void func(int, int);
public:
	void foo();

};

// 类成员函数声明只能在类内， 类外只能存在成员函数的定义
// void Solution::foo();

void Solution::foo()
{
	cout << "hello world" << endl;
	func(10, 20);
}

int main(int argc, char *argv[]) {

	return 0;
}
