/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Wed 25 Nov 2020 08:21:13 PM CST
 @ File Name	: 0066_plusOne.cpp
 @ Description	: 66. 加一 
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


// solution 1: 最低位+1, 如果不产生进位(不是9)那么循环便结束，如果产生进位， 那么就往高一位继续加1逻辑 
//		如果循环到最后一个元素还是产生进位， 那么就是全是9的数组， 如 999， 那么最后结果肯定是最高位为1， 其他全为0
class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
	//digits至少有一位元素， 所以-1并不会溢出 
	for (int i = digits.size() - 1; i >= 0; --i) {
		if (digits[i] == 9) {
			digits[i] = 0;
		} else {
			++digits[i];
			return digits;
		}
	}	
	digits[0] = 1;
	digits.push_back(0);
	return digits;
    }
};


int main(int argc, char *argv[]) {

	return 0;
}
