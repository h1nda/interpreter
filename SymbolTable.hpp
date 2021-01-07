#include "AST.hpp"
#include <vector>
const int PRIME_NUMBER_SIZE = 53;
/*To store the variables, we will build a dynamic array of expressions, where each index will correspond to a variable name (string). We use mapFunction() to encode a string into an index. This way, whenever we are calling an already declared variable/function, we can find/modify it in O(1). */
template <class T>
class SymbolTable {


	struct Pair {
		Token key;
		T evalExpr;
		Pair(Token key, int expr) : key(key), evalExpr(expr) {};
	};
	SinglyLinkedList<Pair> entries[PRIME_NUMBER_SIZE]; 
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
	////4
	/*SymbolTable() {
		for (size_t i = 0; i < PRIME_NUMBER_SIZE; i++) {
			entries[i] = SinglyLinkedList<Node*>();
		}
	}*/
	//~SymbolTable() {
	//	free();
	//}
	/*SymbolTable(const SymbolTable& other) {
		copyFrom(other);
	}
	SymbolTable& operator=(const SymbolTable& other) {
		if (this != &other) {
			free();
			copyFrom(other);
		}
		return *this;
	}*/
	void Insert(Token key, T value) {
		int index = key.hash % PRIME_NUMBER_SIZE;
		// SinglyLinkedList<Pair> LookInto = &entries[index];
		if (entries[index].isEmpty()) {
			entries[index].pushBack(Pair(key,value));
			
		}
		else {
			for (auto it = entries[index].begin(); it != entries[index].end(); it++) {
				if ((*it).key.name == key.name) {
					if ((*it).evalExpr == value)
						throw "Variable already exists";
					(*it).evalExpr = value;
				}
				else {
					entries[index].pushBack(Pair(key,value));
				}
			}
		}
	}
	T Get(Token key) {
		int index = key.hash % PRIME_NUMBER_SIZE;
		//SinglyLinkedList<Pair> LookInto = entries[index];
		for (auto it = entries[index].begin(); it != entries[index].end(); it++) {
			if ((*it).key.name == key.name)
				return (*it).evalExpr;
		}
		std::cerr << "ERROR: invoking undeclared variable or function on line #" << key.line;
		exit(1);
	}
};