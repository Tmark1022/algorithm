/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Mon 17 Jan 2022 03:43:15 PM CST
 @ File Name	: explicit_template_instantiation_a.cpp
 @ Description	: 
 ************************************************************************/
#include <string>
using std::string;

template <class T>
class Tmark {
	public:
		T t;
};

extern template class Tmark<int>; 
extern template class Tmark<string>; 


void func_a(Tmark<int> &a, Tmark<string> b) 
{
	a.t += 100;
	b.t += "100";
}


