/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Mon 09 Nov 2026 02:48:54 PM CST
 @ File Name	: 0380_RandomizedSet.cpp
 @ Description	: 380. O(1) 时间插入、删除和获取随机元素 
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


// solution 1: hashtable + vector; 结构关键点在于删除元素时， 数组直接用back填补被删除的元素， 不用移动后续的元素。
class RandomizedSet {
public:
    RandomizedSet() {
        srand(time(0));
    }

    bool insert(int val) {
        if (mm.count(val)) return false;
        arr.push_back(val);
        mm[val] = arr.size() - 1;
        return true;
    }

    bool remove(int val) {
        if (!mm.count(val)) return false;
        arr[mm[val]] = arr.back();
        mm[arr.back()] = mm[val];
        arr.pop_back();
        mm.erase(val);
        return true;
    }

    int getRandom() {
        return arr[rand() % arr.size()];
    }

private:
    unordered_map<int, int> mm;
    vector<int> arr;
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */



int main(int argc, char *argv[]) {

	return 0;
}
