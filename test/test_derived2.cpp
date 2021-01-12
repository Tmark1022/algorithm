/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Mon 11 Jan 2021 08:41:25 PM CST
 @ File Name	: test_derived2.cpp
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





class Derived;
class Base {
	friend void func222(Derived &obj);
	public:
		Base(int a, int b, int c):a(a), b(b), c(c) {}
		int a;
		void func(Base &obj) {
			cout << obj.c << endl;		
		}

		void fun2(Derived &obj) ;

	protected:
		int b;
	private:
		int c;
};

class Derived : public Base {	
	friend void tmark1(Derived &b) ;
	friend class FF;
	public:
		Derived(int a, int b, int c):Base(a, b,c) {
			this->a = 1555;
		};
		
		void haha(Base &obj) {
			cout << this->b << endl;	
		}

		int aa;	

		using Base::a;
		using Base::b;
	protected:
		int bb;
	private:
		int cc;
};

class FF {
	public: 
		void abs(Derived &obj) {
			obj.bb = 123;
			cout << obj.bb << endl;	
		}
};

class BB:public FF{
	public: 
		void dddd(Derived &obj) {
			abs(obj);
		}	
};




void tmark(Base &a, Derived &b) {
	cout << a.a <<endl;
}  

void tmark1(Derived &b) {
	tmark(b,b);	
}  

void func222(Derived &obj) {
	
}



int main(int argc, char *argv[]) {
	Base obj1(10, 20, 30), obj2(111, 222, 333);
	Derived der(123, 456, 789);
	// obj1.func(obj2);				
	// obj1.func(der);				
	
	BB obj;
	obj.dddd(der);



	

	return 0;
}

