/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Wed 23 Dec 2020 09:29:04 AM CST
 @ File Name	: test_marco.cpp
 @ Description	: 
 ************************************************************************/
//#include <iostream>
//using namespace std;
void foo()
{
#ifdef AA
	cout << "in foo, AA :" << AA << endl; 
#else
	cout << "in foo, undefined marco AA :" << endl; 
#endif
}

class A {
#define AA 100
};

void func()
{
#define BB 999
}

int main(int argc, char *argv[]) {
#ifdef AA
	cout << "AA :" << AA << endl; 
#else
	cout << "undefined marco AA :" << endl; 
#endif

#ifdef BB
	cout << "BB :" << BB << endl; 
#else
	cout << "undefined marco BB :" << endl; 
#endif

// 重复定义宏
#define AA "change aa"
#define BB "change bb"

#ifdef AA
	cout << "AA :" << AA << endl; 
#else
	cout << "undefined marco AA :" << endl; 
#endif

#ifdef BB
	cout << "BB :" << BB << endl; 
#else
	cout << "undefined marco BB :" << endl; 
#endif
	return 0;
}

