#include "SinglyLinkedList.hpp"
#include "AST.cpp"
#include "Token.hpp"
const int PRIME_NUMBER_SIZE = 53;
/*To store the variables, we will build a dynamic array of expressions, where each index will correspond to a variable name (string). We use mapFunction() to encode a string into an index. This way, whenever we are calling an already declared variable, we can find/modify it in O(1). */
template <class K, class V>
class SymbolTable {
	size_t capacity = 31;
	//size_t current;
struct Pair {
	Token key;
	Node* value;
	Pair(Token key, Node* value) {
		this->key = key;
		this->value = value;
	}
};
	std::vector<SinglyLinkedList<Pair>> entries; //dynamic array of SLLs
	/*void free() {
		delete[] entries;
	}
	void copyFrom(const SymbolTable& other) {
		
		capacity = other.capacity;
		current = other.capacity;
		entries = new SinglyLinkedList<Pair>[capacity];
		for (int i = 0; i < capacity; i++) {
			entries[i] = other.entries[i];
		}
	}*/
public:
	//4
	SymbolTable() {
		capacity = 31; //a prime number since we % by it in mapFunction(..)
		//current = 0;
		entries.resize(capacity);
	}
	//~SymbolTable() {
	//	free();
	//}
	//SymbolTable(const SymbolTable& other) {
	//	copyFrom(other);
	//}
	//SymbolTable& operator=(const SymbolTable& other) {
	//	if (this != &other) {
	//		free();
	//		copyFrom(other);
	//	}
	//	return *this;
	//}
	void Insert(Token key, Node* value) {
		int index = key.id % capacity;
		// SinglyLinkedList<Pair> LookInto = &entries[index];
		for (auto it = entries[index].begin(); it != entries[index].end(); it++) {
			if ((*it).key.name == key.name) {
				if ((*it).value == value)
					throw "Variable already exists";
				(*it).value = value;
			}
			else {
				entries[index].pushBack(Pair(key, value));
			}
		}
	}
	Node* Get(Token key) {
		int index = key.id % capacity;
		//SinglyLinkedList<Pair> LookInto = entries[index];
		for (auto it = entries[index].begin(); it != entries[index].end(); it++) {
			if ((*it).key.name == key.name)
				return (*it).value;
		}
	}
};