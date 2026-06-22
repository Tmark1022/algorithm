/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Mon 22 Jun 2026 10:55:01 AM CST
 @ File Name	: 1189.maxNumberOfBalloons.cpp
 @ Description	: 1189. “气球” 的最大数量
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

class Solution {
public:
    int maxNumberOfBalloons(string text) {
        unordered_map<char, int> mm1, mm2;
        string pat = "balloon";
        for (auto ch : text) ++mm1[ch];
        for (auto ch : pat) ++mm2[ch];
        int res = INT_MAX;
        for (auto p : mm2) {
            res = min(res, mm1[p.first] / p.second);
        }
        return res;
    }
};

int main(int argc, char *argv[]) {

	return 0;
}
