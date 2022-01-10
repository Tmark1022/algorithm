/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Mon 10 Jan 2022 04:16:26 PM CST
 @ File Name	: typeid.cpp
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

class A {
	virtual void func() {};
};

class B : public A{
	virtual void func() {};
};

typedef A A2;
using B2 = B;

int main(int argc, char *argv[]) {
	if (typeid(A) == typeid(A2)) {
		cout << "A == A2" << endl; 
	} else {
		cout << "A != A2" << endl; 
	}
	
	if (typeid(B) == typeid(B2)) {
		cout << "B == B2" << endl; 
	} else {
		cout << "B != B2" << endl; 
	}

	if (typeid(A) == typeid(B)) {
		cout << "A == B" << endl; 
	} else {
		cout << "A != B" << endl; 
	}

	A *ap = new A(); 
	A *bp = new B(); 
	cout << typeid(ap).name() << "," <<typeid(*ap).name() << "," << typeid(bp).name() << "," << typeid(*bp).name() << endl;
	
	if (typeid(ap).before(typeid(bp))) {
		cout << "ap before bp" << endl;
	} else {
		cout << "ap not before bp" << endl;
	}	

	if (typeid(*ap).before(typeid(*bp))) {
		cout << "*ap before *bp" << endl;
	} else {
		cout << "*ap not before *bp" << endl;
	}	
		
	return 0;
}
