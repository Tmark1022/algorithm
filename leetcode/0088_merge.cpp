/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Wed 25 Nov 2020 04:04:09 PM CST
 @ File Name	: 0088_merge.cpp
 @ Description	: 88. 合并两个有序数组 
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

// solution 1: nums2 数据加入到nums1上， 然后排序nums1 
// solution 2: nums1 数据移动到辅助数组 nums1_copy, 然后进行merge (nums1_copy, nums2) -> nums1 
// solution 3: 后到前merge


/*
// solution 1
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
	std::copy(nums2.begin(), nums2.begin() + n, nums1.begin() + m);  	 
	std::sort(nums1.begin(), nums1.begin()+m+n);
    }
};
*/

/*
// solution 2
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
	vector<int> nums1_copy(nums1.begin(), nums1.begin() + m);
	
	int i = 0, j = 0;
	while (i < m && j < n) {
		if (nums1_copy[i] <= nums2[j]) {
			nums1[i+j] = nums1_copy[i];	
			++i;
		} else {
			nums1[i+j] = nums2[j];	
			++j;
		}	
	}		
	
	while (i<m) {
		nums1[i+j] = nums1_copy[i]; 	
		++i;
	}

	while (j<n) {
		nums1[i+j] = nums2[j]; 	
		++j;
	}
    }
};
*/


// solution 3
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
	while (n) {
		if (!m || nums2[n-1] >= nums1[m-1]) {
			nums1[n+m-1] = nums2[n-1];
			--n;
		} else {
			nums1[n+m-1] = nums1[m-1];
			--m;
		}	
	}
    }
};

int main(int argc, char *argv[]) {

	return 0;
}
