/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Wed 31 Mar 2021 02:29:00 PM CST
 @ File Name	: 0064_sumNums.cpp
 @ Description	: 剑指 Offer 64. 求1+2+…+n 
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


/*
	求 1+2+...+n ，要求不能使用乘除法、for、while、if、else、switch、case等关键字及条件判断语句（A?B:C）。

	可以使用递归实现， 不过在递归中不能使用if 来作为条件判断作为terminator， 可以利用逻辑运算符的短路特性 &&  
	
	solution 1: 递归实现； <O(n), O(n)【考虑递归深度】>		

   */

// solution 1:
class Solution {
public:
    int sumNums(int n) {
	n && (n += sumNums(n-1));			// 利用逻辑运算符短路特性完成条件判断
	return n;
    }
};


int main(int argc, char *argv[]) {

	return 0;
}
