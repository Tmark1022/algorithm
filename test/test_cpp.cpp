/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Thu 26 Nov 2020 07:34:11 PM CST
 @ File Name	: test_cpp.cpp
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
	vector<string> v1;
	vector<string> v2 = {"hello world", "adsf", "asdf"};
	v1 = v2;	
	v1[0].push_back('0');
	cout << "v1 --------------" << endl;
	std::for_each(v1.begin(), v1.end(), [](const string &tmp){cout << tmp << endl;});  
	cout << "v2 --------------" << endl;
	std::for_each(v2.begin(), v2.end(), [](const string &tmp){cout << tmp << endl;});  




	return 0;
}
