/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Mon 07 Dec 2020 07:23:56 PM CST
 @ File Name	: 0797_allPathsSourceTarget.cpp
 @ Description	: 797. 所有可能的路径 
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

// solution 1: DFS, 回溯方式实现
class Solution {
public:
    void allPathsSourceTarget(vector<vector<int>>& graph, int id, vector<int>& tmp, vector<vector<int>>& ans) {
	if (id == graph.size()-1) {
		ans.push_back(tmp);
		return;
	}
	for (auto &e : graph[id]) {
		tmp.push_back(e);
		allPathsSourceTarget(graph, e, tmp, ans);	
		tmp.pop_back();
	}
    }

    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
	vector<vector<int>> ans;	
	vector<int> tmp;
	tmp.push_back(0);
	allPathsSourceTarget(graph, 0, tmp, ans);
	return ans;
    }
};

int main(int argc, char *argv[]) {

	return 0;
}
