/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Tue 27 Oct 2020 07:03:20 PM CST
 @ File Name	: function_parameter.cpp
 @ Description	: 函数传参问题 
 ************************************************************************/
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

void foo(int (*ptr)[10]) 
{
	// 指针
	cout << sizeof(ptr) << endl;
	
	// 数组, 解引用后还是一个数组对象
	cout << sizeof(*ptr) << endl;
	for (auto e : *ptr) {
		cout << e << " ";
	}
	cout << endl;
}

int main(int argc, char *argv[]) {
	int arr[] = {1,2,3,4,5,6,7,8,9,0};
	foo(&arr);
	return 0;
}
