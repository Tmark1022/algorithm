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
#include <initializer_list>

using namespace std;


void foo(initializer_list<int> il) {

	for_each(il.begin(), il.end(), [](int a){cout << a << endl;});	
}

void Test() {
	string * ptr = new string[10]();

	for (int i = 0; i < 10; ++i) {
		cout << i << ":" << ptr[i] << endl;
	}	


}

int main(int argc, char *argv[]) {
	Test();
	return 0;
}
