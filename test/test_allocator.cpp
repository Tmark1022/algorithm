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




int main(int argc, char *argv[]) {

	allocator<string> alloc;
	string *p = alloc.allocate(10);
	alloc.construct(p, 10, 'c');
	cout << *p << endl;
	alloc.destroy(p);
	alloc.deallocate(p, 10);
	

	return 0;
}
