/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Wed 11 Nov 2020 05:21:57 PM CST
 @ File Name	: cpp_constructor.cpp
 @ Description	: 
 ************************************************************************/
#include <initializer_list>
#include <iostream>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;


class Type {
public:
	Type() {	
		cout << "default constructor " << endl;
	}
		
	// 转换构造函数 
	Type(int a, double b = 111.111):a(a), b(b) {
		cout << "converting/direct constructor" << endl;
	}; 
	Type(const Type &obj):a(obj.a), b(obj.b) {
		cout << "copy constructor" << endl;
	}

	Type(std::initializer_list<int> ini) {
		cout << "Type(std::initializer_list<int> ini)" << endl;;
		std::for_each(ini.begin(), ini.end(), [](int a){cout<<a<< endl;});
	}


	void Print() const  {
		cout << "a = " << a << "b = " << b << endl;
	}
	
private:
	int a;
	double b;
};

// 测试转换构造函数
// 这里形参不需要加const， 不加const 的引用类型需要被绑定值一定要同样类型； 加了const只要求表达式能够转换为对应类型即可， 所以这里就会使用转换构造函数转换为需要的类型， 完成函数调用。
void foo(const Type &obj)
{
	obj.Print();
}


int main(int argc, char *argv[]) {
	Type(10);
	Type aa = Type({1,6,5,43});
		
	return 0;
}
