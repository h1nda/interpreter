//!!!MEMORY LEAK
#include "Interpreter.hpp"
//#include <vld.h>
//class SymbolTable {
//	size_t capacity = 31;
//	//size_t current;
//struct Pair {
//	Token key;
//	Node* value;
//	Pair(Token key, Node* value) {
//		this->key = key;
//		this->value = value;
//	}
//};
//	std::vector<SinglyLinkedList<Pair>> entries; //dynamic array of SLLs
//	/*void free() {
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
//	}*/
//public:
//	//4
//	SymbolTable() {
//		capacity = 31; //a prime number since we % by it in mapFunction(..)
//		//current = 0;
//		entries.resize(capacity);
//	}
//	//~SymbolTable() {
//	//	free();
//	//}
//	//SymbolTable(const SymbolTable& other) {
//	//	copyFrom(other);
//	//}
//	//SymbolTable& operator=(const SymbolTable& other) {
//	//	if (this != &other) {
//	//		free();
//	//		copyFrom(other);
//	//	}
//	//	return *this;
//	//}
//	void Insert(Token key, Node* value) {
//		int index = key.id % capacity;
//		if (entries[index].isEmpty()) {
//			entries[index].pushBack(Pair(key, value));
//			return;
//		}
//		// SinglyLinkedList<Pair> LookInto = &entries[index];
//		for (auto it = entries[index].begin(); it != entries[index].end(); it++) {
//			if ((*it).key.name == key.name) {
//				if ((*it).value == value)
//					throw "Variable already exists";
//				(*it).value = value;
//			}
//			else {
//				entries[index].pushBack(Pair(key, value));
//			}
//		}
//	}
//	Node* Get(Token key) {
//		int index = key.id % capacity;
//		//SinglyLinkedList<Pair> LookInto = entries[index];
//		for (auto it = entries[index].begin(); it != entries[index].end(); it++) {
//			if ((*it).key.name == key.name)
//				return (*it).value;
//		}
//	}
//};

int main() {
	//string assign = " a = (43 + 3) / 2";
	//Parser test1(assign);
	//Node* a = test1.Assign();
	////cout << "Value of variable " << a->left->data.op << " is " << 
	//	//test1.Evaluate(a->right);
	////cout << test.Evaluate(test.Expression());
	/*Classroom seventhGrade;
	seventhGrade.add("Stancho", 3847);
	seventhGrade.add("Dragancho", 3231);
	seventhGrade.add("Ivancho", 2222);
	seventhGrade.printStudents();
	SinglyLinkedList<int> a;
	a.pushBack(5);
	a.pushBack(1);
	a.pushBack(40);
	for (auto it = a.begin(); it != a.end(); it++) {
		std::cout << "Member of a: " << *it << std::endl;
	}*/
	////std::cout << a << std::endl;
	//SinglyLinkedList<int> b;
	//b.pushBack(403);
	//std::cout << b;
	//SymbolTable<int,int> declare;
	//declare.Insert(3, 8);
	//Token testt("varname");
	//Parser test1("403 + 21 / 7");
	//Node* node = test1.parseExpression();
	////std::cout << test1.Evaluate(node);
	////std::cout << test.Evaluate(node);
	////Token test1("dfhgs");
	//SymbolTable init;
	//init.Insert(testt, node);
	//std::cout << test1.Evaluate(init.Get(testt));
	//std::cout << "oop";
//	Lexer tester("print 5+3\na = 504\nb=40+a");
////	Parser parser(tester.tokens);
	/*Node* result = parser.parseAll();*/
	/*SymbolTable sb;*/
	Lexer expr1("b = 4 +4 *10\nread 55");
	Parser par(expr1.tokens);
	Node* root = par.parseAll();
	Interpreter interp;
	interp.Evaluate(root);
	
	return 0;
	//TEST
	/*SinglyLinkedList<int> a;
	a.pushBack(4);
	a.pushBack(1);
	a.pushBack(3);
	a.pushBack(5);
	a.pushBack(35);
	auto it = a.begin();
	std::cout << *it.peek();
	std::cout << std::endl << *it;*/


}