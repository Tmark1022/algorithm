/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Wed 23 Dec 2020 11:45:46 AM CST
 @ File Name	: test_volatile.cpp
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
#include <csignal>

using namespace std;

int num = 10;

void SigInt(int signo) 
{
	num = 100;
}

int main(int argc, char *argv[]) {
	signal(SIGINT, SigInt);
	while (true) {
		cout << num << endl;
	}

	return 0;
}
