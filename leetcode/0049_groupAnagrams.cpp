/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Wed 11 Nov 2020 08:03:15 PM CST
 @ File Name	: 0049_groupAnagrams.cpp
 @ Description	:  49. 字母异位词分组
 ************************************************************************/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <cstring>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::unordered_map;


/*
 * 我们可以使用hashmap 来协议分组， 那么问题的核心就是使字母异位词算出相同的hash key
 * */

class Solution {
private :
    static string SortStr(const string & str) {
	int count[26] = {0};
	string ans;
	for (auto ch : str) 
		++count[ch - 'a'];
	
	char ch = 'a';
	for(auto cnt : count) {
		ans += string(cnt, ch++);
	}
	return ans;
    } 

public:
    /*
	// solution 1: 将字符串排序后作为key, 因为字符串中只含有小写字母， 所以我们可以使用counting sort 来优化排序 
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
	unordered_map<string, vector<string>> map;
	for (string str : strs) {
		string tmp = SortStr(str);
		auto it = map.find(tmp);
		if (it == map.end()) {
			map[tmp] = vector<string>{str};
		} else {
			it->second.push_back(str);
		}
	}
	
	vector<vector<string>> ans;
	for (auto elem : map) {
		ans.push_back(elem.second);
	}

	return ans;
    }
    */


    /*
	// solution 1: 解法1的代码优化版 
	vector<vector<string>> groupAnagrams(vector<string>& strs) {
		vector<vector<string>> ans;
        	unordered_map<string, int> map;       // string -> ans 的下标
        	unsigned idx = 0;

        	for (auto & str : strs) {
        	    string key = SortStr(str);
        	    auto it = map.find(key);
        	    if (it == map.end()) {
        	        ans.push_back(vector<string>({str}));
        	        map[key] = idx++;
        	    } else {
        	        ans[it->second].push_back(str);
        	    }
        	}
        	return ans;
	}
	*/


    /*
	// solution 2: 统计每一个字母的个数， 使用#连接起来作为key， 如 0#1#12#.......  
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
	unordered_map<string, vector<string>> map;
	int count[26];
	
	for (string str : strs) {
		bzero(count, sizeof(count));
		for (auto ch : str) {
			++count[ch - 'a'];
		}
		
		string key; 
		for (auto cnt : count) {
			key += std::to_string(cnt);
			key += "#";
		}		

		auto it = map.find(key);
		if (it == map.end()) {
			map[key] = vector<string>{str};
		} else {
			it->second.push_back(str);
		}
	}
	
	vector<vector<string>> ans;
	for (auto elem : map) {
		ans.push_back(elem.second);
	}

	return ans;
    }
    */

	// solution 3: 质数相乘当做key， 一个字母代表一个不同的质数， 那么相同的异位词乘积会一样 
	//
	// 唯一的问题就是如果字符串太长， 乘积会有溢出风险
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
	unordered_map<long, vector<string>> map;
	int prime[26] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101};
	//               2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113
	
	for (string str : strs) {
		unsigned long long key = 1;
		for (auto ch : str) {
			key *= prime[ch - 'a'];
		}

		auto it = map.find(key);
		if (it == map.end()) {
			map[key] = vector<string>{str};
		} else {
			it->second.push_back(str);
		}
	}
	
	vector<vector<string>> ans;
	for (auto elem : map) {
		ans.push_back(elem.second);
	}

	return ans;
    }

};


int main(int argc, char *argv[]) {
	vector<string> vec = {"eat","tea","tan","ate","nat","bat"};
	Solution obj;
	obj.groupAnagrams(vec);
	return 0;
}
