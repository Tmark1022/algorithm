/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Thu 26 Nov 2020 07:34:11 PM CST
 @ File Name	: test_cpp.cpp
 @ Description	: 
 ************************************************************************/
#include <ios>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>
#include <string>
#include <algorithm>
#include <initializer_list>
#include <cstdio>

using namespace std;


void foo(initializer_list<int> il) {

	for_each(il.begin(), il.end(), [](int a){cout << a << endl;});	
}

void Test() {
	string a = "9,3,4,#,#,1,#,#,2,#,6,#,#";
	istringstream ss(a); 
	string tmp;	
	while (true) {
		cout << "&&&&" <<  ss.eof()  << "---" << ss.fail() << endl;
		if (!getline(ss, tmp, ',')) {
			cout << "-----" << ss.eof()  << "---" << ss.fail() << endl;
			break;
		}
		cout << tmp << endl;
	}
	if (ss) cout << "not end, 000000000000000000" << endl;
	else cout << "end 11111111111111111" << endl;

	cout << "----------------------" << endl;
	string lala = "yiu,11111111111111111111111111111111111111111";
	ostringstream os(lala, ios_base::ate);
	cout << os.str() << endl;
	os << "hello" << " ";
	os << "tmark" << " "; 
	os << "|";
	cout << os.str() << endl;
	
	os.str("123 | 333333333333333333333333");
	cout << os.str() << endl;
	os << "asdfsadf";
	cout << os.str() << endl;

}

void TestBit() {
	int i = 1;	
	while (i) {
		printf("%08x\n", i);	
		i <<= 1;
	}
}

class A{
public:	
	A() = default;
	~A();
	A(int a){}
	A(const A &);
	void foo(int a, int b);
	void foo(int a, double b) {
		cout << "void foo(int a, double b)" << endl;
	}
	void oper() {
		foo(10,20);
	}
};

void A::foo(int a, int b){
	cout << "void foo(int a, int b)" << endl;
}	


void TestRightValReference() {
	int b = 10;
	int && a = std::move(b);


}

void Print2dMatrix(vector<vector<int>> vec)
{
	cout << "****************" << endl;
	for (auto &e : vec) {
		for (auto &e1 : e) {
			cout << e1 << " ";	
		}
		cout << endl; 
	}
}

int main(int argc, char *argv[]) {
	vector<vector<int>> vec = {{1,2,3}, {4,5,6,7}, {8,9,10,11,12}};
	Print2dMatrix(vec);
	vector<vector<int>> dp(vec);	
	Print2dMatrix(dp);
	
	cout << "-----------"	<< endl;
	dp[0][0] = 123;
	Print2dMatrix(vec);
	Print2dMatrix(dp);
	
	return 0;
}
