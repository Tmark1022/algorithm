/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Wed 11 Nov 2020 05:37:03 PM CST
 @ File Name	: container.cpp
 @ Description	: 
 ************************************************************************/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;


void PrintVec(vector<int>& nums) 
{
	for (auto &e : nums) {
		cout << e << " ";
	}
	cout << endl;	
}

int main(int argc, char *argv[]) {
	vector<int> a(10, 1), b(20, 9);	
	copy(a.begin(), a.end(), b.begin());

	PrintVec(a);
	PrintVec(b);


	return 0;
}
