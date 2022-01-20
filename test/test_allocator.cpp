/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Fri 14 Jan 2022 11:54:51 AM CST
 @ File Name	: test_allocator.cpp
 @ Description	: 
 ************************************************************************/
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
#include <deque>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class MyString : public string {
	public:
	using string::string;		// 继承的构造函数

	~MyString() {
		cout << "destory MyString : " << this << endl;
	}	
};
	
int main(int argc, char *argv[]) {

	allocator<MyString> alloc;
	MyString *p = alloc.allocate(1);
	alloc.construct(p, 10, 'c');
	cout << *p << endl;


	MyString * p10 = alloc.allocate(10);
	uninitialized_fill_n(p10, 10, *p);	

	cout << "-------------------------------------------------" << endl;
	p10[2] += "hello world"; 
	for (MyString* beginptr = p10, *endptr = p10 + 10; beginptr != endptr; ++beginptr) {
		cout << *beginptr << endl;

		// destroy
		alloc.destroy(beginptr);
	}
		
	alloc.destroy(p);
	alloc.deallocate(p, 1);	
	alloc.deallocate(p10, 10);

	return 0;
}
