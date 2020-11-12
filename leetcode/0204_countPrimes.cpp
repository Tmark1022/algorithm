/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Sat 24 Oct 2020 05:46:10 PM CST
 @ File Name	: 0204_countPrimes.cpp
 @ Description	: 204. 计数质数
 统计所有小于非负整数 n 的质数的数量。
   
 示例 1： 
 输入：n = 10
 输出：4
 解释：小于 10 的质数一共有 4 个, 它们是 2, 3, 5, 7 。


 示例 2： 
 输入：n = 0
 输出：0

 示例 3： 
 输入：n = 1
 输出：0
  
 
 提示： 
 0 <= n <= 5 * 106

 ************************************************************************/
#include <iostream>
#include <cmath>
#include <cstring>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;


class Solution {
public:
	// 判断一个整数是否为质数
	// 1. 遍历N个数判断
	bool IsPrimes1(int n)
	{
		for (int i = 2; i < n; ++i) {
			if (n % i == 0) {
				return false;	
			}
		}	

		return true;
	}

	// 2. 如果一个数是合数， 那么总是存在两个约数a和b， a <= sqrt(n) && b >= sqrt(n)
	// 所以只需遍历sqrt(n)即可
	bool IsPrimes2(int n)
	{
		int m = sqrt(n); 
		for (int i = 2; i <= m; ++i) {
			if (n%i == 0) {
				return false;	
			}
		}	

		return true;
	}

	// 3. 根据质因数分解， 可以知道任意合数可以分解为有限的质因数的乘积。对于判断一个数只需跟质因数求余即可， 
	// 如一个数不能被2整除， 那么肯定不能被4，被6等整除。 所以只需要判断质因数2即可， 4,6等都是多余重复的判断。
	//
	// 另外其实素数还有个特性，除了2和3, 其他素数的值符合 6x-1 或 6x+1; 按照这个特性， 可以将判断包含所有质数的集合缩小很多
	//
	bool IsPrimesOptimal(int n)
	{
		// 2 和 3特殊处理
		if (2 == n || 3 == n) {
			return true;
		}

		// 质数 2, 3 求余判断
		if (0 == n % 2 || 0 == n % 3) {
			return false;
		}	

		// 对不小于5的质数求余
		int m = sqrt(n); 
		for (int i = 5; i <= m; i+=6) {
			if (n%i == 0 || n%(i+2) == 0) {
				return false;	
			}
		}	

		return true;
	}

public:
	/*
	// solution 1: 暴力, 循环调用IsPrime
	int countPrimes(int n) {
		int count = 0;	
		for (int i = 2; i < n; ++i) {
			if (IsPrimesOptimal(i)) {
				cout << "------" << i << endl;
				++count;
			}
		}	

		return count;
	}
	*/
	
	// solution 2: 厄拉多塞素数筛选法, 把合数剔除出来，剩下的就是素数
	// 根据上边质因数分解得知，任何一个合数由有限任意质因数相乘所得, 所以排除质因数的所有倍数值, 剩下的都是质数了
	int countPrimes(int n) {
		bool *is_prime = static_cast<bool *>(malloc(sizeof(bool) * n)); 
		memset(is_prime, 0x1, sizeof(bool) * n);

		// 同理， 对于一个合数， 总有一个约数 <= sqrt(n), 故这里第一个循环要排除所有合数， 也最多只需遍历sqrt(n)即可，
		// 不过注意这题要统计小于n的素数， 不包括统计n在内， 故不能简单 <= sqrt， 可以使用i*i < n 来判断。
		//
		// 不过这里遍历到n是顺便把count 统计处理, 无需最后额外统计一遍count
		int count = 0;		
		for (int i = 2; i < n; ++i) {
			if (is_prime[i]) {
				++count;

				// 排除所有i的倍数
				for (int j = i+i; j < n; j += i) {
					is_prime[j] = false;
				}	
			}
		}	

		return count;
	}

public: 
	// 获取n内所有的素数
	vector<int> GetPrimes(int n) {
		vector<bool> is_prime(n, true);
		vector<int> ans;
		for (int i = 2; i < n; ++i) {
			if (is_prime[i]) {
				ans.push_back(i);

				// 排除所有i的倍数
				for (int j = i+i; j < n; j += i) {
					is_prime[j] = false;
				}	
			}
		}	

		return ans;
	}
	
};

int main(int argc, char *argv[]) {
	Solution obj;
	//cout << obj.countPrimes(0) <<endl;
	
	int n ;
	cout << "n is ";
	cin >> n;
	for (auto & elem : obj.GetPrimes(n))
		cout << elem << ",";
	cout << endl;
	
	return 0;
}
