/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Fri 23 Oct 2020 08:21:19 PM CST
 @ File Name	: sizeof.cpp
 @ Description	: sizeof 一些特性测试 
 ************************************************************************/
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

// definition
int foo1() 
{
	cout << "call foo1" << endl;
	return 0;
}

// declaration
char foo2();


// declaration; whit forward declaration Class A
class A;
A foo3();

int main(int argc, char *argv[]) {
	// sizeof 运算符 不会计算运算对象
	
	// 1. 结果 4, 没有输出call foo1 	
	cout << sizeof(foo1()) << endl;	

	// 2. 结果 1, 就算foo2只有声明， 没有定义，链接时也没有问题，因为不实际计算运算对象， 仅仅知道运算对象返回的类型就可， 就可以知道类型大小
	cout << sizeof(foo2()) << endl;	

	// 3. 报错， 相对于2., 就算不实际计算运算对象，但是最终也要知道运算对象的类型实际大小，才能得到sizeof的返回值，  但是只有class A forward declaration， 没有定义， 故报错 
	// cout << sizeof(foo3()) << endl;	
	
	// 4. 结果4, 其实就是*ptr 解引用对象的类型的大小， *ptr 类型为int， 故返回4; 需要知道因为sizeof 不计算运算对象， 所以对于解引用无效的ptr也没有任何问题。
	int * ptr = nullptr;
	cout << sizeof(*ptr) << endl;

	return 0;
}
