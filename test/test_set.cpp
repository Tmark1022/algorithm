/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Thu 18 Mar 2021 05:05:39 PM CST
 @ File Name	: test_set.cpp
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
#include <set>

using namespace std;

int main(int argc, char *argv[]) {
	set<int> s1; 
	s1.insert(10);
	s1.insert(2);
	s1.insert(5);
	s1.insert(1);
	for (auto &e : s1) {
		cout << e << endl;
	}
	cout << "================= : " << *(s1.begin()) << endl;
	return 0;
}
