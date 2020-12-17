/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Thu 17 Dec 2020 09:28:57 AM CST
 @ File Name	: 0860_lemonadeChange.cpp
 @ Description	: 860. 柠檬水找零 
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
// solution 1: 贪婪, 优先可使用身上面额大的钱币来找零， 因为这里小的面额总能组合成大的面额
class Solution {
public:
    vector<int> money = {20, 10, 5};
    bool lemonadeChange(vector<int>& bills) {
        unordered_map<int, int> have;
        for (auto &bill : bills) {
                int change = bill - 5;
                for (int i = 0; change && i < money.size(); ++i) {
                        int cnt = min(have[money[i]], change/money[i]);
                        if (cnt) {
                                have[money[i]] -= cnt;
                                change -= cnt * money[i];
                        }
                }
                if (change) return false;
                ++have[bill];
        }
        return true;
    }
};
*/

// solution 1: 因为存在的变化很少， 所以可以写得固定精简一些, hardcode
class Solution {
public:
    bool lemonadeChange(vector<int>& bills) {
        int five = 0, ten = 0;
        for (auto &bill : bills) {
                if (5 == bill) ++five;
                else if (10 == bill) {
                        if (!five) return false;
                        ++ten;
                        --five;
                } else {
                        if (ten && five) --ten, --five;
                        else if (five >= 3) five -= 3;
                        else return false;
                }
        }
        return true;
    }
};

int main(int argc, char *argv[]) {

	return 0;
}
