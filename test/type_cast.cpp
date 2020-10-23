/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Fri 23 Oct 2020 08:02:34 PM CST
 @ File Name	: type_cast.cpp
 @ Description	: C++ 命名强制类型测试 
 ************************************************************************/
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int main(int argc, char *argv[]) {
	int a = 100;
	int *ptr_int = &a;
	double b = 123.456;

	/***************************************************
	* static_cast, static_cast, 不能转走底层const, 也不能直接从int * -> char *, 可以借助void * ， int * -> void * -> char *
	***************************************************/	
	short c = static_cast<short>(b);

	//char * ptr_ch = static_cast<char *>(ptr_int);	 // failed
	
	// bingo
	void * ptr_void = static_cast<void *>(ptr_int);
	char * ptr_ch = static_cast<char *>(ptr_void);

	// 不能去掉底层const
	const int * const_ptr = &a;
	// int * not_const_pty = static_cast<int *>(const_ptr); // failed

	/***************************************************
	* const_cast 
	***************************************************/	
	// bingo
	int * not_const_pty = const_cast<int *>(const_ptr);
	
	/***************************************************
	* reinterpret_cast 
	***************************************************/
	// bingo
	char * ptr_ch2 = reinterpret_cast<char *>(ptr_int);


	cout << "hello type cast" << endl;

	return 0;
}
