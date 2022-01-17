/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Mon 17 Jan 2022 03:44:51 PM CST
 @ File Name	: explicit_template_instantiation_main.cpp
 @ Description	: 
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

template <class T>
class Tmark {
	public:
		T t;
};

template class Tmark<int>;
template class Tmark<string>;
extern void func_a(Tmark<int> &, Tmark<string>&);
extern void func_b(Tmark<int> &, Tmark<string>&);

int main(int argc, char *argv[]) {
	Tmark<int> a;
	Tmark<string> b;
	a.t = 99;
	b.t = "99";
	
	func_a(a, b);	
	func_b(a, b);	
	
	cout << a.t <<"," << b.t << endl;
	return 0;
}
