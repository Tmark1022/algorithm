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

/***************************************************
* 2222222222222222222222 
***************************************************/
template<class T, class Q> 
class Base {
	public:
		static void print() {
			cout << "1111" << endl;
		}
};

// Q 是double 的特例化
template<class T>
class Base<T, double> {
	public:
		static void print() {
			cout << "2222" << endl;
		}
};

// T和Q都是指针的特例化
template<class T, class Q>
class Base<T*, Q*> {
	public:
		static void print() {
			cout << "3333" << endl;
		}
};

// T是int， Q 是float的特例化
template<>
class Base<int, float> {
	public:
		static void print() {
			cout << "444444444" << endl;
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

	cout << "------------------------ split line -----------------------" << endl;
	Base<int, int>::print();
	Base<int, float>::print();
	Base<float, int>::print();
	Base<int, Tmark<double>>::print();
	Base<int *, int *>::print();
	Base<int, double *>::print();
	Base<int, double>::print();
	Base<double, int>::print();


	return 0;
}
