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
NOTE:
	切线是曲线的线性逼近	
	函数在某一点的导数就是该函数所代表的曲线在这一点上的切线斜率

// 导数求解过程
例子：函数 f(x) = x^2
我们知道 f(x) = x^2，也可以计算 f(x+Δx) ：

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
	solution 1: 二分

	solution 2: 牛顿迭代法; 
			在f(x) = x^2 曲线中， 求当f(x) = a 时, x的取值为多少; 该问题可以转换为 在f(x) = x^2 - a 的曲线中， 当f(x) = 0, x 的取值为多少
			我们可以在f(x) = x^2 - a中使用牛顿迭代法, 当迭代N次后， 横坐标x 无限收敛于 0 = x^2 -a 的x值

			假如我们的起点的横坐标为 x0, 那么在曲线上其纵坐标 为 x0^2 - a; 
			我们求曲线方程 f(x) = x^2 - a 在 x0 点时的导数（切线斜率）k :
				k = [f(x0 + Δx) - f(x0))] / (x0+Δx - x0) 
				  = [(x0 + Δx)^2 - a - (x0^2 - a)] / Δx
				  = (2x0Δx - Δx^2) / Δx
				  = 2x0
			
			即对于曲线方程 f(x) = x^2 - a , 的任意一点x0， 该点上的曲线斜率为 2x0

			我们下载求迭代方程, 现在已知当前迭代到x0, 求下一个迭代的x坐标[其y坐标值为0], 因为我们知道k, 所以 
				0 - (x0^2 - a) = k * (x - x0)
				即 -(x0^2 - a) = 2x0x - 2x0^2
				
				2x0x = x0^2 + a
				
				即 迭代方程 为 x = (x0 + a / x0) / 2
			
			我们不断迭代， 直到存在x 得到 x^2 - a <= 1e-5
			该x 即 sqrt(a) 的答案
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
