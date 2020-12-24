/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Thu 24 Dec 2020 10:24:26 AM CST
 @ File Name	: 0455_findContentChildren.cpp
 @ Description	: 455. 分发饼干 
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


// solution 1: 贪心算法， 优先使用小饼干满足胃口小孩子， 的局部最优解为每一个孩子刚好分配到刚刚满足的饼干
class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
	sort(g.begin(), g.end());	
	sort(s.begin(), s.end());
	int i = 0, j = 0, ans = 0;
	while (i < g.size() && j < s.size()) {
		if (g[i] <= s[j]) ++i, ++ans;
		++j;
	}
	return ans;
    }
};


int main(int argc, char *argv[]) {

	return 0;
}
