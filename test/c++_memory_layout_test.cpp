/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Fri 31 Dec 2021 03:45:53 PM CST
 @ File Name	: a.cpp
 @ Description	: C++ 内存layout
 ************************************************************************/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
#include <deque>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class A {
	public:
		A():a(0), b(0) {}		
		A(int v1, int v2):a(v1), b(v2) {}		
		int a, b;
};


// sizeof(B) == 16， B类新添加的a,b变量并没有覆盖继承于A的a,b变量， 仅仅是作用域嵌套于A内
class B :public A{
	public:
		B(int v1, int v2):A(v1, v2), a(v1), b(v2) {}
		int a, b;
};




int main(int argc, char *argv[]) {
	B obj(10, 20);

	cout << obj.a << "," << obj.b << endl;
	cout << obj.A::a << "," << obj.A::b << endl;

	obj.a = 1111, obj.b = 2222;
	obj.A::a = 3333, obj.A::b = 4444;
	cout << obj.a << "," << obj.b << endl;
	cout << obj.A::a << "," << obj.A::b << endl;

	return 0;
}
