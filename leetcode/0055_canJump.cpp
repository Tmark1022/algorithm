/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Thu 17 Dec 2020 08:13:40 PM CST
 @ File Name	: 0055_canJump.cpp
 @ Description	: 55. 跳跃游戏 
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


// solution 1: 这个其实可以转换为一个图寻找路径, 顶点就是所有的nums值, 边就是每一个顶点能够延伸到的范围值;
//		所以这个问题可以使用DFS 或者 BFS(因为知道起点和终点， 所以也能使用双向BFS)来解决; 时间复杂度为o(N+e), e极端情况下是N^2, 所以时间复杂度为O(N^2) 

// solution 2: 贪婪， 维护right值表示能从起点开始能到达的右边最远距离， right 大于nums.size() 即证明终点可达	


// solution 2
class Solution {
public:
    bool canJump(vector<int>& nums) {
	int right = 0;	
	for (int i = 0; i < nums.size(); ++i) {
		if (i > right) return false;
		right = max(right, i + nums[i]);
	}
	return true;
    }
};



int main(int argc, char *argv[]) {

	return 0;
}
