/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Wed 08 Nov 2023 05:36:51 PM CST
 @ File Name	: type_transition.cpp
 @ Description	: 
 ************************************************************************/
#include <cmath>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
#include <deque>
#include <unordered_map>
#include <unordered_set>

using namespace std;

int main(int argc, char *argv[]) {

	int a = std::pow(2,31) - 1; 
	float b = a;
	int c = b;
	long d = b;

	cout << sizeof(a) << "," << a << endl;
	cout << sizeof(b) << "," << b << endl;
	cout << sizeof(c) << "," << c << endl;
	cout << sizeof(d) << "," << d << endl;

	return 0;
}
