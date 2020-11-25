/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Wed 25 Nov 2020 01:54:14 PM CST
 @ File Name	: 0189_rotate.cpp
 @ Description	: 189. 旋转数组 
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

/*
题意只允许使用O(1)时间复杂度

solution 1: 每次移动一位，共移动K次， time complexity O(k*n)  
solution 2: 反转数组
solution 3: 环状替换, 从start下标开始, 每次找到最终的位置替换下来，被替换的元素也相应找其最终位置并替换， 直到所有都替换下来
	这里有两个关键点 1) 当前环中不会出现访问到之前已经访问过的下标， 因为之前访问过的下标都是由start开始计算出来的， 只有再次通过start下标， 才能在此到达之前已经访问过的位置。
			2) 每个环中含有的下标是不相交的
   */

/*
// solution 1:
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
	int len = nums.size();
	if (len <= 1) return ;
	k = k%len;	
	for (int i = 1; i <= k; ++i) {
		int tmp = nums[len-1];	
		for (int j = len-1; j > 0; --j) nums[j] = nums[j-1];
		nums[0] = tmp;
	}
    }
};
*/

/*
// solution 2
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
	int len = nums.size();
	if (len <= 1) return ;
	k = k%len;	
	if (k <= 0) return ;
	std::reverse(nums.begin(), nums.end());
	std::reverse(nums.begin(), nums.begin() + k);
	std::reverse(nums.begin()+k, nums.end());
    }
};
*/

// solution 3
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int len = nums.size();
        if (len <= 1) return ;
        k = k%len;
        for (int start = 0, count = 0; count < len; ++start) {
                int cur = start, prev = nums[start], tmp, next;
                do {
                        next = (cur + k)%len;
                        tmp = nums[next];
                        nums[next] = prev;
                        ++count;
                        cur = next;
                        prev = tmp;
                } while (start != cur);
        }
    }
};


int main(int argc, char *argv[]) {

	return 0;
}
