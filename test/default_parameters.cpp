/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Fri 30 Oct 2020 05:33:08 PM CST
 @ File Name	: default_parameters.cpp
 @ Description	: 默认实参测试
 ************************************************************************/
#include <iostream>
#include <string>

using namespace std;

int a = 100;
string b = "hello";
string c = "tmark"; 


// 函数定义
void foo(int pa, string pb, string pc)
{
	cout << pa << "," << pb << " " << pc << endl;
}

// 1.函数可以多次声明，但是每个形参的默认实参只能指定一次
void foo(int, string, string = c);
void foo(int, string = b, string);
void foo(int = a, string, string);

int main(int argc, char *argv[]) {	
	foo();
	foo(22);
	foo(33, "sad");
	foo(44, "sad", "jace");

	// 2. 默认实参的解析（名字寻找）是在函数声明的作用域内进行的 
	int a = 888;			// 定义同名变量，企图替代外层作用域的a变量，但是函数调用时根本不在函数调用位置开始解析名字， 而是在函数声明位置进行	
	foo();

	// 3. 默认实参的求值是在函数调用时进行的
	b = "nihao";
	c = "mingli";
	foo(1000);		// 函数调用时默认实参使用了最新的b,c变量的值

	return 0;
}
