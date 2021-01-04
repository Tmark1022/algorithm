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
	
	virtual void vfunc(int arg = 11111) {
		cout << "base vfunc" << arg << endl;
	}

	static int sta;
	int haha = 99;
protected:
	int share;
private:
	int a;
	int b;
};

class Derived: public Base{
public:
	Derived():Base(){}

	virtual void vfunc(int arg = 2222222){
		cout << "derived vfunc" << arg << endl;
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

	void vfunc(int arg = 333333){
		cout << "derived222 vfunc" << arg <<  endl;
	}

protected:
	void foo() {
		cout << this->share << endl;
	}

private:
	int c;
};

void Func(Base *ha) {
	ha->haha = 7788;
	cout << "func" << ha->haha << endl;
}

int Base::sta = 100;
int main(int argc, char *argv[]) {
	Base ba;	
	Derived der;
	Derived2 der2;

	Base &r1 = der2;
	r1.vfunc();

	Derived &r2 = der2;
	r2.vfunc();
	

	return 0;
}
