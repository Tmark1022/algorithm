/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Fri 07 Jan 2022 10:52:50 AM CST
 @ File Name	: pure_virtual_function.cpp
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
		long a;
		virtual void func() = 0;
};

class B :public A{
	public:
		long b;
		void func() override {}
};

int main(int argc, char *argv[]) {
	B b;
	cout << sizeof(b) << endl;

	return 0;
}
