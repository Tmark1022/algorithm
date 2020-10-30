/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Fri 30 Oct 2020 11:27:03 PM CST
 @ File Name	: 0146_LRUCache.cpp
 @ Description	: 146. LRU缓存机制 
 ************************************************************************/
#include <iostream>
#include <unordered_map>

using namespace std;

struct DLinkListNode {
	int key;
	int value;	
	DLinkListNode * prev;	
	DLinkListNode * next;	
	
	DLinkListNode(int key, int value): key(key), value(value), prev(nullptr), next(nullptr) {}
};


class LRUCache {
public:
	LRUCache(int capacity) {
		this->capacity = capacity;	
		this->head = new DLinkListNode(0,0);
		this->tail = new DLinkListNode(0,0);
		this->head->next = this->tail; 
		this->tail->prev = this->head;
	}

	~LRUCache() {
		if (head) {
			for (DLinkListNode *ptr = head, *tmp; ptr != nullptr; ) {
				tmp = ptr->next;	 
				delete ptr;;	
				ptr = tmp;
			}	
		}
	}
    
	int get(int key) {
		auto iter = cache.find(key);		
		if (iter == cache.end()) {
			return -1;
		}

		RemoveNode(iter->second);
		AddToHead(iter->second);
		return iter->second->value;
    	}
    	
    	void put(int key, int value) {	
		auto iter = cache.find(key);		
		if (iter != cache.end()) {
			iter->second->value = value;
			RemoveNode(iter->second);
			AddToHead(iter->second);
		} else{
			// 值不存在	
			DLinkListNode *new_node = new DLinkListNode(key, value);
			cache[key] = new_node;
			AddToHead(new_node);

			if (cache.size() > capacity) {
				DLinkListNode *del_node = RemoveFromTail(); 	
				cache.erase(del_node->key);
				delete del_node;
			}
		}
    	}
	
	void AddToHead(DLinkListNode *node) {
		node->next = head->next;
		node->next->prev = node;
		head->next = node;	
		node->prev = head;
	}		

	void RemoveNode(DLinkListNode *node) {
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}

	DLinkListNode * RemoveFromTail() {
		DLinkListNode *node = tail->prev;
		RemoveNode(node);		
		return node;
	}

private:
	unordered_map<int, DLinkListNode *> cache;
	int capacity;

	// dummy listNode, 避免头尾节点空的情况判断
	DLinkListNode *head;
	DLinkListNode *tail;


};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */






int main(int argc, char *argv[]) {

	return 0;
}
