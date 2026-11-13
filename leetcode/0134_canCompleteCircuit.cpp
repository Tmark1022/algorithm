/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Fri 13 Nov 2026 03:37:55 PM CST
 @ File Name	: 0134_canCompleteCircuit.cpp
 @ Description	: 134.加油站 
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
// solution 1: brute force， 枚举每一个起点， 然后模拟走一遍; O(N^2)
class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int len = gas.size();
        for (int i = 0; i < len; ++i) {
            gas[i] -= cost[i];
        }
        for (int i = 0; i < len; ++i) {
            int remain = 0, j = i;
            do {
                remain += gas[j++];
                j %= len;
            } while (remain >= 0 && i != j);
            if (remain >= 0 && i == j) return i;
        }
        return -1;
    }
};


// solution 2: 有一个关键点， 就是如果从i开始枚举， 直到j下边发现走不通了， 那么其实i ~ j都不会是可行的起点。
//              照这样可以缩减枚举规模， 时间复杂度O(N)
class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int len = gas.size();
        for (int i = 0; i < len; ++i) {
            gas[i] -= cost[i];
        }
        for (int i = 0; i < len;) {

            // 开始模拟走
            int remain = 0, j = i;
            do {
                remain += gas[j++];
                j %= len;
            } while (remain >= 0 && i != j);

            if (remain >= 0 && i == j) {
                // 成功了
                return i;
            } else {
                // 失败了,  这里remain 一定小于0， 枚举下一个起点
                if (j > i) i = j;
                else i = len;       // 直接终止
            }
        }
        return -1;
    }
};
*/

// solution 2.1: solution 2 好写一点的写法
class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int len = gas.size();
        for (int i = 0; i < len;) {
            // 开始模拟走
            int remain = 0, step = 0, j;
            while (step < len) {
                j = (i + step) % len;
                remain += gas[j] - cost[j];
                if (remain < 0) break;
                ++step;
            }
            if (step == len) return i;
            else i += step + 1;
        }
        return -1;
    }
};



int main(int argc, char *argv[]) {

	return 0;
}
