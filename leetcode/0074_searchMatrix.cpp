/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Fri 25 Dec 2020 09:12:29 AM CST
 @ File Name	: 0074_searchMatrix.cpp
 @ Description	: 74. 搜索二维矩阵 
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
	solution 1: 暴力, O(MN)	
	solution 2: 从左下角或右上角开始搜索， 每次排除一行或一列, O(M+N)
	solution 3: 二分查找, O(logMN)
   */


/*
// solution 2: 从左下角开始搜索
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
	if (!matrix.size()) return false;
	int m = matrix.size(), n = matrix[0].size();
	for (int x = m-1, y = 0; x >= 0 && y < n;) {
		if (matrix[x][y] == target) return true;
		else if (matrix[x][y] < target) ++y;
		else --x;
	}	
	return false;
    }
};
*/

// solution 3: 二分查找 
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
	if (!matrix.size()) return false;
	int m = matrix.size(), n = matrix[0].size();
	int low = 0, high = m*n-1;
	while (low <= high) {
		int mid = low + (high - low) / 2;
		if (matrix[mid/n][mid%n] == target) return true;
		else if (matrix[mid/n][mid%n] < target) low = mid + 1;
		else high = mid - 1;
	}
	return false;
    }
};


int main(int argc, char *argv[]) {

	return 0;
}
