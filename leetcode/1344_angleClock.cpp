/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Thu 18 Jun 2026 11:04:27 AM CST
 @ File Name	: 1344_angleClock.cpp
 @ Description	: 1344. 时钟指针的夹角  
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
    double angleClock(int hour, int minutes) {
        double angle = abs(minutes*6 - (hour%12 + minutes/60.0)*30);
        return angle > 180.0 ? 360-angle : angle;
    }
};

int main(int argc, char *argv[]) {

	return 0;
}
