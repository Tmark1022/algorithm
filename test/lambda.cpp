/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Tue 17 Nov 2020 08:59:00 PM CST
 @ File Name	: lambda.cpp
 @ Description	: 
 ************************************************************************/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;


int main(int argc, char *argv[]) {
		
	auto fun = []()->int{
		int a = 100;
		int b;
		cin >> b;
		if (b) {
			return -1;
		}
		return a;}; 
	cout << fun() << endl;
	return 0;
}
