/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Tue 27 Oct 2020 09:31:22 AM CST
 @ File Name	: 0001_twoSum.cpp
 @ Description	: 1. 两数之和 
 ************************************************************************/
#include <iostream>
#include <vector> 
#include <unordered_map>
using namespace std;

class Solution {
public:
	/*
    vector<int> twoSum(vector<int>& nums, int target) {
	unordered_map<int, int> map;		
	int rem;
	for (int i = 0, j = nums.size(); i < j; ++i) {
		rem = target - nums[i];
		if (map.find(rem) != map.end()) {
			return {i, map[rem]};
		}	
		map[nums[i]] = i;
	}
	return {-1, -1};
    }
    */

    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> map;
        for (int i = 0, j = nums.size(); i < j; ++i) {
                unordered_map<int, int>::iterator it = map.find(target - nums[i]);
                if (it != map.end()) {
                        return {it->second, i};
                }
                map[nums[i]] = i;
        }
        return {-1, -1};
    }
};


int main(int argc, char *argv[]) {
	Solution obj;
	vector<int> vec{2, 7, 11, 15};
	vector<int> res = obj.twoSum(vec, 9);
	cout << "[";	
	for (auto elem : res) {
		cout << elem << ","; 
	}
	cout << "]" << endl;
	return 0;
}
