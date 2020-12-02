/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Thu 26 Nov 2020 07:34:11 PM CST
 @ File Name	: test_cpp.cpp
 @ Description	: 
 ************************************************************************/
#include <ios>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <initializer_list>

using namespace std;


void foo(initializer_list<int> il) {

	for_each(il.begin(), il.end(), [](int a){cout << a << endl;});	
}

void Test() {
	string a = "123 34 56 ";
	istringstream ss(a); 
	string tmp;	
	while (ss>>tmp) {
		cout << tmp << endl;
	}

	cout << "----------------------" << endl;
	string lala = "yiu,11111111111111111111111111111111111111111";
	ostringstream os(lala, ios_base::ate);
	cout << os.str() << endl;
	os << "hello" << " ";
	os << "tmark" << " "; 
	os << "|";
	cout << os.str() << endl;
	
	os.str("123 | 333333333333333333333333");
	cout << os.str() << endl;
	os << "asdfsadf";
	cout << os.str() << endl;


}

int main(int argc, char *argv[]) {
	Test();
	return 0;
}
