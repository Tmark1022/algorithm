/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Tue 27 Oct 2020 08:30:23 PM CST
 @ File Name	: function_return_type.cpp
 @ Description	: 函数返回值类型 
 ************************************************************************/
#include <iostream>
#include <string> 

using std::cin;
using std::cout;
using std::endl;
using std::string;



// 函数func1, 
// 参数 :接受指向大小为6的数组的指针
// 返回值 : 返回指向大小为6的数组的指针 
int (* func1(int (*ptr)[6]) )[6] {
	cout << "func 1 ...." << endl;
	return ptr;	
}


// 函数func2, 
// 参数 :接受指向大小为6的数组的指针
// 返回值 : 返回指向大小为6的数组的引用
int (&func2(int (*ptr)[6]) )[6] {
	cout << "func 2 ...." << endl;
	return *ptr;	
}

void test(string a)
{
	cout << "func test, " << a << endl;
}

// 函数func3, 
// 参数 :函数指针
// 返回值 : 函数指针
void (*func3(void (*fp)(string)))(string ) {
	cout << "func 3 ...." << endl;
	fp("in func3");
	return fp;
}

int main(int argc, char *argv[]) {
	
	int arr[] = {1,2,3,4,5,6};

	int (*ptr)[6] = func1(&arr);
	for (auto e : *ptr) {
		cout << e << " ";
	}
	cout << endl;

	cout << "--------------------------------" << endl;	
	int (&r)[6] = func2(&arr);
	for (auto e : r) {
		cout << e << " ";
	}
	cout << endl;

	cout << "--------------------------------" << endl;	
	void (*func_ptr)(string) = func3(test); 
	func_ptr("in main");


	return 0;
}
