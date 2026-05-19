/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Tue 19 May 2026 11:05:00 AM CST
 @ File Name	: 0771_numJewelsInStones.cpp
 @ Description	: 771. 宝石与石头
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

class Solution {
public:
    int numJewelsInStones(string jewels, string stones) {
	    unordered_set<char> ss(jewels.begin(), jewels.end());
	    int res = 0;
	    for (auto &ch : stones) {
		    if (ss.count(ch)) ++res;
	    }
	    return res;
    }
};


int main(int argc, char *argv[]) {
	Solution obj;
	cout << obj.numJewelsInStones("aA","aAAbbbb");
	return 0;
}
