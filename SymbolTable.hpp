#include "AST.hpp"
#include <vector>
const int PRIME_NUMBER_SIZE = 53;
/*To store the variables, we will build a dynamic array of expressions, where each index will correspond to a variable name (string). We use mapFunction() to encode a string into an index. This way, whenever we are calling an already declared variable/function, we can find/modify it in O(1). */
template <class T>
class SymbolTable {
	struct Pair {
		Token key;
		T evalExpr;
		Pair(Token key, T expr) : key(key), evalExpr(expr) {};
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
	void Insert(Token key, T value) {
		int index = key.hash % PRIME_NUMBER_SIZE;
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
		for (auto it = entries[index].begin(); it != entries[index].end(); it++) {
			if ((*it).key.name == key.name)
				return (*it).evalExpr;
		}
		std::cerr << "ERROR: invoking undeclared variable or function on line #" << key.line;
		exit(1);
	}
};