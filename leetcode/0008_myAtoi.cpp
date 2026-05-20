/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Wed 20 May 2026 11:16:40 AM CST
 @ File Name	: 0008_myAtoi.cpp
 @ Description	: 8. 字符串转换整数 (atoi) 
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


/***************************************************
* 状态机 
***************************************************/
/*
enum {eStart, eSign, eNumber, eEnd};

class Context {
public:
	Context(string &s):s(s),idx(0),state(eStart), sign(1), res(0){}
	string s;
	int idx, state, sign, res;
};

class State {
public:
	virtual void Do(Context &ctx) = 0;
};

class StateStart : public State {
public:
	void Do(Context &ctx) override {
		if (ctx.idx >= ctx.s.size()) {
			ctx.res *= ctx.sign, ctx.state = eEnd;
			return ;
		}
		
		if (ctx.s[ctx.idx] == ' ') ++ctx.idx;
		else ctx.state = eSign; 
	}
};

class StateSign : public State {
public:
	void Do(Context &ctx) override {	
		if (ctx.s[ctx.idx] == '-') ++ctx.idx, ctx.sign = -1;
		else if (ctx.s[ctx.idx] == '+') ++ctx.idx;
		ctx.state = eNumber;
	}
};

class StateNumber : public State {
public:
	virtual void Do(Context &ctx) {
		auto ch = ctx.s[ctx.idx];    
		if (ctx.idx >= ctx.s.size() || ch < '0' || ch > '9') {
			ctx.res *= ctx.sign, ctx.state = eEnd;
			return ;
		}
		
		// overflow
		int boundry = INT_MAX / 10, rmd = INT_MAX % 10;
		if (ctx.res > boundry || (ctx.res == boundry && ch - '0' > rmd)) {
			ctx.res = (ctx.sign == 1 ? INT_MAX : INT_MIN), ctx.state = eEnd; 
			return ; 
		}

		ctx.res = ctx.res * 10 + (ch - '0');  
		++ctx.idx;
	}
};

class StateEnd : public State {
public:
	virtual void Do(Context &ctx) {
		// do nothing
	}
};

class Factory {
public:
	static unordered_map<int, State *> mm;
	static State *getInstance(int state) {
		if (mm.count(state)) return mm[state];

		State *p;
		switch(state) {
			case eStart: p = new StateStart(); break;
			case eSign: p = new StateSign(); break;
			case eNumber: p = new StateNumber(); break;
			default: p = new StateEnd();
		}
		return mm[state] = p;
	} 
};

unordered_map<int, State *> Factory::mm;

class Solution {
public:
    int myAtoi(string s) {
	    Context ctx(s);
	    while (ctx.state != eEnd) {
		    auto ps = Factory::getInstance(ctx.state); 
		    ps->Do(ctx);
	    }
	    return ctx.res;
    }
};
*/

/***************************************************
* hard code 
***************************************************/
class Solution {
public:
    int myAtoi(string s) {
	int boundry = INT_MAX / 10, rmd = INT_MAX % 10, idx = 0, res = 0, len = s.size(), sign = 1;

	// 空格
	while (idx < len && s[idx] == ' ') ++idx;

	// 符号
	if (idx >= len) return res;
	if (s[idx] == '-') sign = -1, ++idx;
	else if (s[idx] == '+') ++idx;

	// 数字
	for (; idx < len && s[idx] >= '0' && s[idx] <= '9'; ++idx) {
		if (res > boundry || (res == boundry && s[idx] - '0' > rmd)) return sign == 1 ? INT_MAX : INT_MIN;
		res = res * 10 + (s[idx] - '0');
	}	
	return res * sign;
    }
};

int main(int argc, char *argv[]) {
	Solution obj;
	cout << obj.myAtoi(" -042") << endl;
	cout << obj.myAtoi("1337c0d3") << endl;
	cout << obj.myAtoi("0-1") << endl;
	cout << obj.myAtoi("i am tmark, 123") << endl;
	return 0;
}
