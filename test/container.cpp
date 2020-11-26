/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Wed 11 Nov 2020 05:37:03 PM CST
 @ File Name	: container.cpp
 @ Description	: 
 ************************************************************************/
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <unordered_map>

using namespace std;


void PrintVec(vector<int>& nums) 
{
	for (auto &e : nums) {
		cout << e << " ";
	}
	cout << endl;	
}



// 无论有序还是无序的关联容器， 相同关键字的元素都是相邻存储的



/***************************************************
* 有序关联容器 
***************************************************/	
void TestMultiMap() {
	vector<string> key  = {"id", "score", "name", "id", "score", "name", "id", "score", "name"};	
	vector<string> value  = {"109", "100", "tmark", "50", "88", "jace", "1", "50", "uuu"};		

	cout << "--------------------------------------------------------------multimap" << endl;
	multimap<string, string> mm;
	for (int i = 0; i < key.size(); ++i) 
		 mm.insert({key[i], value[i]});
	
	// 遍历
	for (auto &e : mm) {
		cout << "<" << e.first << "," << e.second << ">" << endl;
	}
	
	// 范围输出 1
	auto range = mm.equal_range("name");		
	for (auto i = range.first; i != range.second; ++i) {
		cout << "===============" <<"<" << i->first << "," << i->second << ">" << endl;
	}

	// 范围输出 2
	auto begin = mm.find("name");		
	if (begin != mm.end()) {
		for (int i = 1; i<= mm.count("name"); ++i, ++begin) {
			cout << "++++++++++++++" <<"<" << begin->first << "," << begin->second << ">" << endl;
		}
	}
}	


void TestUnorderedMultiMap() {
	vector<string> key  = {"id", "score", "name", "id", "score", "name", "id", "score", "name"};	
	vector<string> value  = {"109", "100", "tmark", "50", "88", "jace", "1", "50", "uuu"};		

	cout << "-----------------------------------------------------unordered_multimap" << endl;
	unordered_multimap<string, string> umm;
	for (int i = 0; i < key.size(); ++i) 
		 umm.insert({key[i], value[i]});
	
	// 遍历
	for (auto &e : umm) {
		cout << "<" << e.first << "," << e.second << ">" << endl;
	}
	
	// 范围输出 1
	auto range = umm.equal_range("name");		
	for (auto i = range.first; i != range.second; ++i) {
		cout << "===============" <<"<" << i->first << "," << i->second << ">" << endl;
	}

	// 范围输出 2
	auto begin = umm.find("name");		
	if (begin != umm.end()) {
		for (int i = 1; i<= umm.count("name"); ++i, ++begin) {
			cout << "++++++++++++++" <<"<" << begin->first << "," << begin->second << ">" << endl;
		}
	}
}	

void TestMap() {
	TestMultiMap();
	cout << endl << endl;
	TestUnorderedMultiMap();
}



int main(int argc, char *argv[]) {
	//TestMap();
	vector<int> aa;	
	cout << aa.size() - 1 << endl;
	for (int i = 0; i < aa.size() - 1; ++i)			// 坑
		cout << i << endl;

	return 0;
}
