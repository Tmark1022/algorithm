/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Mon 30 Dec 2024 07:26:53 PM CST
 @ File Name	: 0240_searchMatrix.cpp
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

using namespace std;

// solution 1: brute force, 遍历寻找每一个数据，每次搜索问题规模缩小1， 时间复杂度O(MN)
// solution 2: 每行 or 每列 进行二分查找， 时间复杂度为O(mlogn) or O(nlogm)
// solution 3: 左下角开始遍历, 时间复杂度为O(M+N)


/*
// solution 2: 每行进行二分查找, O(mlogn)
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
	    for (const auto &vec : matrix) {
		    if (target < vec[0]) break;
		    if (target > vec.back()) continue;
		    if (binarySearch(vec, target)) return true;
	    }
	    return false;
    }
	
    bool binarySearch(const vector<int> &vec, int target) {
	    int low = 0, high = vec.size() - 1, mid;
	    while (low <= high) {
		    mid = low + (high - low) / 2;
		    if (vec[mid] == target) return true;
		    else if (vec[mid] < target) low = mid + 1;
		    else high = mid - 1;
	    }
	    return false;
    }
};
*/


// solution 2: 每行进行二分查找, O(mlogn)
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
	    int row = matrix.size(), col = matrix[0].size(), i = row - 1, j = 0;
	    while (i >= 0 && j < col) {
		    if (target == matrix[i][j]) return true;
		    else if (target < matrix[i][j]) --i;  
		    else ++j;
	    }
	    return false;
    }	
};









int main(int argc, char *argv[]) {

	return 0;
}
