/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Thu 18 Mar 2021 07:05:25 PM CST
 @ File Name	: 0460_LFUCache.cpp
 @ Description	: 460. LFU 缓存 
 ************************************************************************/
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
#include <deque>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <list>

using namespace std;

/*
	solution 1: hash table + set(avl tree / rb tree); 根据题意提示， 使用time作为使用计数器， 用于表示最近访问的元素。
			使用 <cnt, time> 作为二元组来排序最小使用和最近使用(使用平次一样时).
		
			时间复杂度:
				get 操作 O(logn), put 操作 O(logn), 主要的事件复杂度在于set 的 插入与删除

			空间复杂度:
				O(capacity)

	solution 2: 双hash table + double linked list; 
			时间复杂度:
				get 操作 O(1), put 操作 O(1)	

			空间复杂度:
				O(capacity)
   */

/*
// solution 1:
class LFUCache {
public:
	struct Node {
		int key, value, freq, time;
		Node() = default;
		Node(int k, int v, int f, int t):key(k), value(v), freq(f), time(t) {}				
		
		bool operator<(const Node &r) const {
			return freq == r.freq ? time < r.time : freq < r.freq;	
			
		}		
	};

    LFUCache(int capacity):cap(capacity), time(0) {}
    
    int get(int key) {
	if (cap <= 0) return -1;		
	auto it = map.find(key);
	if (it == map.end()) return -1; 

	// 从set中删除旧node
	s.erase(it->second);

	// 更新map中的node 
	it->second.time = ++time;
	++it->second.freq;

	// 向set中插入新的node
	s.insert(it->second);
	
	return it->second.value; 
    }
    
    void put(int key, int value) {
	if (cap <= 0) return ;		
	auto it = map.find(key);
	if (it == map.end()) {
		// non-exist
		// 需要注意这里必须要先删除后插入新的(因为插入的新node的freq为1, 可能需要被删除的node的freq就比1大， 导致删除了新插入的node)
		if (map.size() >= cap) {
			auto del_it = s.begin();
			map.erase(del_it->key);
			s.erase(del_it);
		}

		// 注意map[key] 执行时会使用Node的默认构造函数来构造默认Node对象， 然后才是赋值运算
		map[key] = Node(key, value, 1, ++time);			
		s.insert(map[key]);
	} else {
		// exist
		// 从set中删除旧node
		s.erase(it->second);

		// 更新map中的node 
		it->second.time = ++time;
		++it->second.freq;
		it->second.value = value;

		// 向set中插入新的node
		s.insert(it->second);
	}
    }

private:
	int cap, time;    
	unordered_map<int, Node> map;	
	set<Node> s;
};
*/


// solution 2:
class LFUCache {
public:
	struct Node {
		int key, value, freq;
		Node() = default;
		Node(int k, int v, int f):key(k), value(v), freq(f) {}					
	};

    LFUCache(int capacity):cap(capacity), min_freq(0) {}
    
    int get(int key) {
	if (cap <= 0) return -1;		
	auto it = key_map.find(key);
	if (it == key_map.end()) return -1; 

	list<Node>::iterator node_it = it->second;	
	int val = node_it->value, freq = node_it->freq;    

	// 从freq_list 的 list 中删除对应node
	freq_map[freq].erase(node_it);	
	if (freq_map[freq].size() <= 0) {
		freq_map.erase(freq);	
		if (min_freq == freq) ++min_freq;		
	}			

	// 在freq_map 的新的list中插入对应node
	freq_map[freq + 1].push_front(Node(key, val, freq + 1));

	// 更新key_map对应node iterator
	it->second = freq_map[freq + 1].begin();
	
	return it->second->value;
    }
    
    void put(int key, int value) {
	if (cap <= 0) return ;		
	auto it = key_map.find(key);
	if (it == key_map.end()) {
		// non-exist	
		// 需要注意这里必须要先删除后插入新的(因为插入的新node的freq为1, 可能需要被删除的node的freq就比1大， 导致删除了新插入的node)
		if (key_map.size() >= cap) {
			key_map.erase(freq_map[min_freq].back().key);
			freq_map[min_freq].pop_back();
			if (freq_map[min_freq].size() <= 0) freq_map.erase(min_freq);	
		}
		
		// 在freq_map[1] 中插入新的节点， 并将min_freq 设置为1
		freq_map[1].push_front(Node(key, value, 1));					
		min_freq = 1;

		// 在key_map 插入新节点
		key_map[key] = freq_map[1].begin();
	} else {
		// exist
		list<Node>::iterator node_it = it->second;	
		int freq = node_it->freq;    
	
		// 从freq_list 的 list 中删除对应node
		freq_map[freq].erase(node_it);	
		if (freq_map[freq].size() <= 0) {
			freq_map.erase(freq);	
			if (min_freq == freq) ++min_freq;		
		}			
	
		// 在freq_map 的新的list中插入对应node
		freq_map[freq + 1].push_front(Node(key, value, freq + 1));
	
		// 更新key_map对应node iterator
		it->second = freq_map[freq + 1].begin();
	}
    }

private:
	int cap, min_freq;    
	unordered_map<int, list<Node>> freq_map;	
	unordered_map<int, list<Node>::iterator> key_map;		// 增删list元素并不影响list的迭代器
};


/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 *
 */


int main(int argc, char *argv[]) {

	return 0;
}
