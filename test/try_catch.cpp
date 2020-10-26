/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Mon 26 Oct 2020 07:15:30 PM CST
 @ File Name	: try_catch.cpp
 @ Description	: try catch 捕捉异常
 ************************************************************************/
#include <iostream>
#include <stdexcept>

using std::cin;
using std::cout;
using std::endl;

class Solution{
public:		
	void foo() {
		int choice;
		while (cin >> choice) {
			try{
				if (choice) {
					throw std::runtime_error("choice error");
				} else {
					cout << "do it" << endl;
				}
			} catch (std::runtime_error err) {
				cout << "catch error : " << err.what() << endl; 
			}
		}	
	}
};




int main(int argc, char *argv[]) {

	Solution obj;
	obj.foo();


	return 0;
}
