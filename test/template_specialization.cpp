/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Tue 18 Jan 2022 02:33:43 PM CST
 @ File Name	: template_specialization.cpp
 @ Description	: 模板特例化测试 
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

template<class T>
class Tmark{
	public:
		void func() {
			cout << "type " << typeid(T).name() << ", normal template instantiation" << "size is " << sizeof(T) << endl; 
		}
};

// T 为 double 类型时， 进行模板特例化
template<> 
class Tmark<double>{
	public:
		void func() {
			cout << "type " << typeid(double).name() << ", template specialization." << "size is " << 10086 << endl; 
		}
};

// 对所有指针类型进行特例化 
template<class T>
class Tmark<T *> {
	public:
		void func() {
			cout << "type " << typeid(T *).name() << ", pointer template specialization." << "size is " << 12345 << endl; 
		}
};


int main(int argc, char *argv[]) {
	Tmark<char>().func();
	Tmark<char *>().func();
	Tmark<int>().func();
	Tmark<int *>().func();
	Tmark<int[10]>().func();
	Tmark<float>().func();
	Tmark<double>().func();
	Tmark<double *>().func();

	return 0;
}
