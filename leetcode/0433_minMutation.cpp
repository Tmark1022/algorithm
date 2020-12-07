/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Mon 07 Dec 2020 07:55:59 PM CST
 @ File Name	: 0433_minMutation.cpp
 @ Description	: 433. 最小基因变化 
 ************************************************************************/
#include <iostream>
#include <tuple>
#include <vector>
#include <string>
#include <algorithm>
#include <deque>
#include <unordered_set>
#include <climits>

using namespace std;

/*
// solution 1: BFS
class Solution {
public:
    int minMutation(string start, string end, vector<string>& bank) {
        unordered_set<string> set(bank.begin(), bank.end());
        if (!set.count(end)) return -1;
        set.erase(start);

        string letter = "ACGT";
        deque<string> que;
        que.push_back(start);
        int step = 0;
        while (que.size()) {
                ++step;
                int cnt = que.size();
                while (cnt) {
                        string cur = que.front();
                        que.pop_front();
                        for (auto &ch : cur) {
                                char tmp = ch;
                                for (const auto &t : letter) {
                                        ch = t;
                                        if (set.erase(cur)) {
                                                if (cur == end) return step;
                                                que.push_back(cur);
                                        }
                                }
                                ch = tmp;
                        }
                        --cnt;
                }
        }
        return -1;
    }
};
*/

/*
// solution 2: 双向BFS【最佳】
class Solution {
public:
    int minMutation(string start, string end, vector<string>& bank) {
        unordered_set<string> set(bank.begin(), bank.end()), bset({start}), eset({end});
	unordered_set<string> *head = &bset, *tail = &eset;
        if (!set.erase(end)) return -1;
        set.erase(start);
        string letter = "ACGT";

        int step = 0;
        while (bset.size() && eset.size()) {
                ++step;
		if (head->size() > tail->size()) std::swap(head, tail);

		unordered_set<string> tmp_set;
		for (auto cur : *head) {
                        for (auto &ch : cur) {
                                char tmp = ch;
                                for (const auto &t : letter) {
                                        ch = t;
					if (tail->count(cur)) return step;	
					if (set.erase(cur)) tmp_set.insert(cur);                  
				}
                                ch = tmp;
                        }
                }
		*head = tmp_set;
        }
        return -1;
    }
};
*/

// solution 3: 回溯DFS, 使用set记录可以使用的字符串
//		因为重复计算一些路径, 最后得出最小值， 效率不如BFS
class Solution {
public:
	void BackTracking(string& start, string& end, unordered_set<string>& set, int step) {
		if (start == end) {
			minStep = std::min(step, minStep);		
			return ;
		}

		string letter = "ACGT"; 	
		for (auto &ch : start) {
			char tmp = ch;
			for (auto &t : letter) {
				ch = t;
				if (!set.erase(start)) continue;	
				BackTracking(start, end, set, step+1);		
				set.insert(start);
			}	
			ch = tmp;
		}	
	}

    int minMutation(string start, string end, vector<string>& bank) {
        unordered_set<string> set(bank.begin(), bank.end()), bset({start}), eset({end});
        if (!set.count(end)) return -1;
	set.erase(start);
	BackTracking(start, end, set, 0);
	return minStep == INT_MAX ? -1: minStep; 
    }

private:
    int minStep = INT_MAX;
};




int main(int argc, char *argv[]) {

	return 0;
}
