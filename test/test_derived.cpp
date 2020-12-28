/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Fri 25 Dec 2020 05:47:23 PM CST
 @ File Name	: test_derived.cpp
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
	
	void vfunc() {
		cout << "base vfunc" << endl;
	}

	static int sta;
protected:
	int share;
private:
	int a;
	int b;
};

class Derived: public Base{
public:
	Derived():Base(){}

	virtual void vfunc(){
		cout << "derived vfunc" << endl;
	}

protected:
	void foo() {
		cout << this->share << endl;
	}

private:
	int c;
};

class Derived2: public Derived{
public:
	Derived2():Derived(){}

	void vfunc(){
		cout << "derived222 vfunc" << endl;
	}

protected:
	void foo() {
		cout << this->share << endl;
	}

private:
	int c;
};

class CCC {

};

void Func(Base ha) {
	cout << "FUNC" << endl; 
}


int Base::sta = 100;
int main(int argc, char *argv[]) {
	Base ba;	
	Derived der;
	Derived2 der2;


	return 0;
}
