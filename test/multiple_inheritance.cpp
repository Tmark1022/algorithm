/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Mon 10 Jan 2022 03:38:45 PM CST
 @ File Name	: multiple_inheritance.cpp
 @ Description	: 多重继承下， 指针判断相等的一些问题
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

class A {
	public:
		long a;
};

class B {
	public:
		long b;
};

class C: public A, public B {
	public:
		long c;
};

int main(int argc, char *argv[]) {
	C * cp = new C();
	A * ap = cp;
	B * bp = cp;

	cout << ap << endl << bp << endl << cp << endl;

	if (ap == cp) {
		cout << "ap == cp" << endl;		
	} else {
		cout << "ap != cp" << endl;		
	}	

	// bp的地址值是不等于cp的， 但是对于用户来说， 多重继承中地址的转换对于用户是透明的， 故这里==判断是否相等时， 有特殊处理 
	// Bear in mind that the two addresses are not actually equal (r is off by 8 bytes). However, that should be completely transparent to the user; so, the compiler actually subtracts the 8 bytes from r before comparing it to b; thus, the two addresses are considered equal.
	if (bp == cp) {
		cout << "bp == cp" << endl;		
	} else {
		cout << "bp != cp" << endl;		
	}	

	return 0;
}
