/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Wed 05 Jan 2022 01:52:26 PM CST
 @ File Name	: a.cpp
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

class A{
	public:
		A(long val):val(val) {}
		virtual void func() {}
		long get_val() {return val;}
		long val;	
		static long aa;
};

class B : virtual public A{
	public:
		B(long val) : A(val + 10000) {}
		long get_val_B() {return get_val();}
		void set_val_B(int val) {this->val = val;}
};

class C : virtual public A{
	public:
		C(long val) : A(val + 20000) {}
		long get_val_C() {return get_val();}
		void set_val_C(int val) {this->val = val;}

		static long aa;
};

class D: public B, public C {
	public:	
		D(long val):B(val), C(val), A(200){}
};

long A::aa = 100;
long C::aa = 2000;

int main(int argc, char *argv[]) {
	cout << A::aa << endl;		
	cout << B::aa << endl;		
	cout << C::aa << endl;		
	cout << D::C::aa << "," << D::B::aa << endl;		
	
	B::aa = 1999;

	cout << A::aa << endl;		
	cout << B::aa << endl;		
	cout << C::aa << endl;		
	cout << D::C::aa << "," << D::B::aa << endl;		

	cout << "===================split=========================" << endl;
	D d(123);	
	cout << d.get_val_B() << "," << d.get_val_C() << endl;	
	d.set_val_B(190), d.set_val_C(290);
	cout << d.get_val_B() << "," << d.get_val_C() << endl;

	cout << "===================split=========================" << endl;

	A * ap = &d; 	
	D * dp = dynamic_cast<D*>(ap);

	return 0;
}
