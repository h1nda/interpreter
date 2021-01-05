//#include "SinglyLinkedList.hpp"
//#include "Node.hpp"
///*To store the variables, we will build a dynamic array of expressions, where each index will correspond to a variable name (string). We use mapFunction() to encode a string into an index. This way, whenever we are calling an already declared variable, we can find/modify it in O(1). */
//class SymbolTable {
//	size_t capacity;
//	size_t current;
//	struct Pair {
//		Token key;
//		Node* value; //expression
//	};
//	SinglyLinkedList<Pair>* entries; //dynamic array of SLLs
//	void free() {
//		delete[] entries;
//	}
//	void copyFrom(const SymbolTable& other) {
//		
//		capacity = other.capacity;
//		current = other.capacity;
//		entries = new SinglyLinkedList<Pair>[capacity];
//		for (int i = 0; i < capacity; i++) {
//			entries[i] = other.entries[i];
//		}
//	}
//public:
//	//4
//	SymbolTable() {
//		capacity = 31; //a prime number since we % by it in mapFunction(..)
//		current = 0;
//		entries = new SinglyLinkedList<Pair>[capacity];
//	}
//	~SymbolTable() {
//		free();
//	}
//	SymbolTable(const SymbolTable& other) {
//		copyFrom(other);
//	}
//	SymbolTable& operator=(const SymbolTable& other) {
//		if (this != &other) {
//			free();
//			copyFrom(other);
//		}
//		return *this;
//	}
//
//	void lookUp(Token key, Node* value) {
//		int index = key.id % capacity;
//		for()
//	}
//	void insert
//	void get
//	Pair* findPair(Token key) {
//		size_t index = key.id % capacity;
//		for (int i = index; i < capacity; i++) {
//			if (entries[i].key.type == key.type && entries[i].key.name == key.name) {
//
//			}
//		}
//	}
//
//
//};