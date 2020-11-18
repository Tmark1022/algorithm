/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Tue 17 Nov 2020 08:59:00 PM CST
 @ File Name	: lambda.cpp
 @ Description	: 
 ************************************************************************/
#include <iostream>
#include <iterator>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;


void PrintVec(vector<int> &vec) {
	for (auto &e : vec) {
		cout << e << " ";
	}
	cout << endl;
}


bool BinaryPredicate(int a, int b) {
	return a >= b; 
}

class Solution{
	public:
		Solution():a(100), b("123"){}

		void foo() {
			
			auto ff = [this](){
				cout << a << endl;	
				cout << b << endl;
				this->a = 111;
				this->b+= "adf";

			};

			ff();
			cout << "-----------" << endl;
			cout << a << endl;	
			cout << b << endl;
		}
	
	private:
		int a ;
		string b;

};


int main(int argc, char *argv[]) {
	Solution obj;	
	obj.foo();
}
