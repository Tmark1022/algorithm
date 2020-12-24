/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Thu 24 Dec 2020 11:34:29 AM CST
 @ File Name	: 0874_robotSim.cpp
 @ Description	: 874. 模拟行走机器人 
 ************************************************************************/
#include <functional>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
#include <deque>
#include <unordered_map>
#include <unordered_set>

using namespace std;


// solution 1: 直接模拟走路, 每次走一步， 判断当前坐标是否有障碍, 因为每条前进指令的最大行走步数为 1~9, 所以时间复杂度为O(N+K), N为command大小， K为obstacle大小
//		使用unordered_set存储坐标， 因为pair没有对应的hash类， 所以可以转成字符串来使用unordered_set;
//		不要使用set， set使用红黑树来存储数据， 每次查找性能为log(n)

class Solution {
public:
    int robotSim(vector<int>& commands, vector<vector<int>>& obstacles) {
	if (!commands.size()) return 0;
	vector<vector<int>> xy_diff = {{0,1}, {1, 0}, {0, -1}, {-1, 0}};	// 北 东 南 西	
	unordered_set<string> set;
	for (const auto &ob : obstacles) set.insert(to_string(ob[0]) + "," + to_string(ob[1]));			
	
	int x = 0, y = 0, direct = 0, ans = 0;
	for (auto &co : commands) {
		if (co == -2) direct = (direct + 3) % 4;  		
		else if (co == -1) direct = (direct + 1) % 4;
		else {
			vector<int> diff = xy_diff[direct];
			for (int dist = 1; dist <= co; ++dist) {
				if (set.count(to_string(x+diff[0]) + "," + to_string(y+diff[1]))) break;
				x += diff[0], y += diff[1];
				ans = max(ans, x*x + y*y);
			}	
		}
	}	
	return ans;	
    }
};



int main(int argc, char *argv[]) {

	return 0;
}
