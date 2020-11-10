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
	//friend void func(int, int);
public:
	void foo();

	// const成员函数返回的是const 对象引用
	const Solution& my() const {
		return  *this;
	}

	Solution(int a, int b = 99):a(a), b(b) {
		cout << "call solution " << endl;
		
	}


public:
	int a, b;

};

// 类成员函数声明只能在类内， 类外只能存在成员函数的定义
// void Solution::foo();

void Solution::foo()
{
	cout << "hello world" << endl;
	//func(10, 20);
}

void Print(const Solution &obj) {
	cout << obj.a << ", " << obj.b << endl;
}


class Aggregate {

public:
	int a;
	int b;

	void print() {
		cout << a << ", " << b << endl;
	}

private:
	void hello() {};

};


int main(int argc, char *argv[]) {

	Print(10);
	Aggregate obj {10, 20};
	obj.print();

	return 0;
}
