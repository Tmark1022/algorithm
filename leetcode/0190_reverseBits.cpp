/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Mon 15 Mar 2021 02:53:41 PM CST
 @ File Name	: 0190_reverseBits.cpp
 @ Description	: 190. 颠倒二进制位 
 ************************************************************************/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
#include <deque>
#include <unordered_map>
#include <unordered_set>
#include <bitset>

using namespace std;

/*
	solution 1: 常规, 遍历32遍  
	solution 2: 以一个byte作为reverse 单位，只要记录一个byte内所有可能的逆转值即可 
	solution 3: 不使用循环，类似分治思想

	solution 4: 使用bitset实现, uint32_t -> bitset<32> -> uint32_t
	*/

/*
// solution 1:
class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
	uint32_t ans = 0;
	for (int i = 0; i < 32; ++i) {
		if (n & (1 << i)) {
			ans |= 1 << (31 - i); 
		}	
	}
	return ans;
    }
};

// solution 1:
class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
	uint32_t ans = 0;
	for (int i = 0; i < 32; ++i) {
		ans <<= 1;	
		ans |= n&1;
		n >>= 1;
	}
	return ans;
    }
};

// solution 2:
class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
	uint32_t ans = 0;
	for (int i = 0; i < 4; ++i) {
		ans <<= 8;	
		ans |= GetReverseByte(n&0xff);
		n >>= 8;
	}
	return ans;
    }

    uint8_t GetReverseByte(uint8_t byte) {
	static unordered_map<uint8_t, uint8_t> map;		// 记录byte大小的reverse bit 数据
	if (map.count(byte)) return map[byte];

	uint8_t ans = 0, key = byte;
	for (int i = 0; i < 8; ++i) {
		ans <<= 1;	
		ans |= byte&1;
		byte >>= 1;
	}
	map[key] = ans; 
	return map[key];
    }
};

// solution 3:
class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
	n = (n >> 16) | (n << 16);
	n = ((n & 0xff00ff00) >> 8) | ((n & 0x00ff00ff) << 8);
	n = ((n & 0xf0f0f0f0) >> 4) | ((n & 0x0f0f0f0f) << 4);
	n = ((n & 0xcccccccc) >> 2) | ((n & 0x33333333) << 2);
	n = ((n & 0xaaaaaaaa) >> 1) | ((n & 0x55555555) << 1);
	return n;
    }
};
*/

// solution 4:
class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
	bitset<32> bits(n);	
	int low = 0, high = bits.size() - 1;
	while (low < high) {
		bits[low] = bits[low] ^ bits[high];
		bits[high] = bits[low] ^ bits[high]; 
		bits[low] = bits[low] ^ bits[high]; 
		++low, --high;
	}
	return bits.to_ulong();
    }
};

int main(int argc, char *argv[]) {

	return 0;
}
