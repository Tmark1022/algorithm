/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Tue 15 Dec 2020 11:30:09 AM CST
 @ File Name	: 0069_mySqrt.cpp
 @ Description	: 
 ************************************************************************/
#include <cmath>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
#include <deque>
#include <unordered_map>
#include <unordered_set> #include <cmath>

using namespace std;


/*
// 导数求解过程
例子：函数 f(x) = x2
我们知道 f(x) = x2，也可以计算 f(x+Δx) ：

开始：			f(x+Δx) = (x+Δx)^2
展开 (x + Δx)^2:	f(x+Δx) = x^2 + 2x Δx + (Δx)^2
 
坡度公式是：	 [f(x+Δx) − f(x)] / Δx
 
代入 f(x+Δx) 和 f(x)：	 [x^2 + 2x Δx + (Δx)^2 − x^2] / Δx
简化 (x2 and −x2 约去）：	 [2x Δx + (Δx)^2] / Δx
再简化（除以 Δx）：	  = 2x + Δx
 	 
当 Δx 趋近 0时，我们得到：	= 2x
 
结果：x2 的导数是 2x
*/


/*
// solution 1: 二分查找, 时间复杂度为log(x)
class Solution {
public:
    int mySqrt(int x) {
        int low = 0, high = x, ans = -1, mid;
        while (low <= high) {
                mid = low + ((high - low) >> 1);
                if (static_cast<long long>(mid) * mid <= x) ans = mid, low = mid+1;
                else high = mid - 1;
        }
        return ans;
    }
};
*/

// solution 2: 牛顿迭代法; 最后推导公式 为 X(k+1) = (X(k) + n / X(k))  / 2, 循环迭代， 直到X(k+1) - X(K) <= 1e-6;
//              注意: 需要选择一个初始点作为开始迭代的起点(不能选择驻点),
//                      根据y = x^2的曲线图可以知道， 对于一个给定的y， x有两个正负取值， 所以牛顿迭代法能求到哪个收敛值取决于开始的点的选择
class Solution {
public:
    int mySqrt(int x) {
        double prev, cur = 1.0;                                 // 选择起点
        do {
                prev = cur;
                cur = (cur + x/cur) * 0.5;
        } while (abs(cur - prev) > 1e-6);
        return static_cast<int>(cur);
    }
};




int main(int argc, char *argv[]) {


	return 0;
}
