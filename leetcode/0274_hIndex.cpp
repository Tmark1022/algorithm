/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Fri 06 Nov 2026 11:50:30 AM CST
 @ File Name	: 0274_hIndex.cpp
 @ Description	: 274. H 指数  
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
// solution 1:  暴力， 枚举h; O(N^2)
// solution 1.1: 二分枚举h, 然后O(N) 遍历查找大于h的论文篇数; O(NlogN)
// solution 2: sort, 再反向遍历, O(Nlogn)
// solution 3: 计数排序， 收集阶段指导了每个引用数应放置的下标（即知道>=该引用数的有多少个论文); O(1000 + N) -> O(N)
// solution 4: solution 3的基础上， 最后求h采用二分; O(N)
*/

/*
// solution 1: 暴力， 枚举h; O(N^2)
class Solution {
public:
    int hIndex(vector<int>& citations) {
        int h = 0;

        while(true) {
            int n = h + 1, c = 0;
            for (auto &e : citations) {
                if (e >= n) ++c;
            }
            if (c >= n) h = n;
            else break;
        }
        return h;  
    }
};
*/

// solution 1.1: 二分枚举h, 然后O(N) 遍历查找大于h的论文篇数; O(NlogN)


/*
// solution 2: sort, 再反向遍历, O(Nlogn)
class Solution {
public:
    int hIndex(vector<int>& citations) {
        sort(citations.rbegin(), citations.rend());
        int idx = 0;
        while (idx < citations.size() && citations[idx] >= idx + 1) ++idx;
        return idx;
    }
};
*/

/*
// solution 3: 计数排序， 收集阶段指导了每个引用数应放置的下标（即知道>=该引用数的有多少个论文); O(1000 + N) -> O(N)
class Solution {
public:
    int hIndex(vector<int>& citations) {
        vector<int> count(1001, 0), idxs(1001, 0);
        for (auto &e : citations) ++count[e];

        for (int i = 1; i < idxs.size(); ++i) {
            idxs[i] = count[i-1] + idxs[i-1]; 
        }

        int h = 0, len = citations.size();
        while (h < min(len, 1000) && len - idxs[h+1] >= h+1) ++h;
        return h;
    }
};
*/

// solution 4: solution 3的基础上， 最后求h采用二分; O(N)
class Solution {
public:
    int hIndex(vector<int>& citations) {
        vector<int> count(1001, 0), idxs(1001, 0);
        for (auto &e : citations) ++count[e];

        for (int i = 1; i < idxs.size(); ++i) {
            idxs[i] = count[i-1] + idxs[i-1];
        }

        // 二分
        int l = 0, len = citations.size(), r = min(len, 1000);
        while (l < r) {
            int mid = l + (r - l + 1) / 2;
            if (len - idxs[mid] >= mid) l = mid;
            else r = mid - 1;
        }
        return l;
    }
};

int main(int argc, char *argv[]) {
	return 0;
}
