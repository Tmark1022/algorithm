/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Thu 19 Nov 2020 04:51:24 PM CST
 @ File Name	: cpp_iterator.cpp
 @ Description	: 
 ************************************************************************/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;




int main(int argc, char *argv[]) {
	string aa = "iam,hell,first";
	auto comma = std::find(aa.cbegin(), aa.cend(), ',');
	cout << string(comma, aa.cend()) << endl;


	// .base 得到rcomma指向位置的相邻下一个位置的正向迭代器
	auto rcomma = std::find(aa.crbegin(), aa.crend(), ',');
	cout << string(rcomma.base(), aa.cend()) << endl;


	return 0;
}
