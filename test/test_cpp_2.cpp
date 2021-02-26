/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Fri 26 Feb 2021 03:10:00 PM CST
 @ File Name	: test_cpp_2.cpp
 @ Description	: 
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

class Base{
public:
	Base() = default;
	
	int a, p;
};

class Derived : public Base{	
public:
	Derived() = default;
	
	int p, b;	
};

void PrintElement(Derived &obj) {
	cout << obj.a << ", " << obj.Base::p << ", " << obj.b << ", " << obj.p << endl;
}

int main(int argc, char *argv[]) {
	Derived obj;	
	obj.a = 100;
	obj.b = 200;
	obj.Base::p = 111;
	obj.p = 222;

	PrintElement(obj);

	Base &r = obj;
	r.p = 1999;
	r.a = 19990; 
	PrintElement(obj);

	return 0;
}
