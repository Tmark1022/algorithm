/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Tue 27 Oct 2020 07:37:47 PM CST
 @ File Name	: return_list_initialization.cpp
 @ Description	: 列表初始化返回值 
 ************************************************************************/
#include <iostream>
#include <initializer_list>
#include <vector>

using namespace std;

class Solution {
public:
	Solution() {
		cout << "solution()" << endl;
	}

	Solution(string a) {
		cout << "soution (a) , a==> " << a << endl; 
	}

	Solution(initializer_list<int> li) {
		cout << "soution (initializer_list) "<< endl; 
		for (auto e : li) {
			cout << e << " " ;
		}
		cout << endl;
	}
};


Solution foo() 
{
	return {};
}

Solution foo1() 
{
	return {"i am so handsome"};
}

Solution foo2() 
{
	return {1, 2, 3, 4};
}

int main(int argc, char *argv[]) {
	foo();
	foo1();
	foo2();
	return 0;
}
