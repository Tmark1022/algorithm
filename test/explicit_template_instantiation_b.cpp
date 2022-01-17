/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Mon 17 Jan 2022 03:44:13 PM CST
 @ File Name	: explicit_template_instantiation_b.cpp
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

void func_b(Tmark<int> &a, Tmark<string>& b) 
{
	a.t += 900;
	b.t += "900";
}


