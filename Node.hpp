#include "Token.hpp"
#include <iostream>

/*To store the variables, we will build a dynamic array of expressions, where each index will correspond to a variable name (string). We use mapFunction() to encode a string into an index. This way, whenever we are calling an already declared variable, we can find/modify it in O(1). */

bool isPrime(int n) {

	if (n == 1 || n == 0)
		return false;
	int end = sqrt(n);
	for (int i = 2; i <= end; i++) {
		if (n % i == 0)
			return false;
	}
	return true;

}
int nextPrime(int n) {
	do {
		n += 2;
	} while (!isPrime(n));
	return n;
}

class SymbolTable {
	size_t capacity;
	size_t current;
	struct Pair {
		Token key;
		Node* value; //expression
	};
	Pair* entries = nullptr;
	//Variables* data;
public:
	SymbolTable() {
		capacity = 31; //a prime number since we % by it in mapFunction(..)
		current = 0;
		entries = new Pair[capacity];
	}
	void free() {
		delete entries;
	}
	~SymbolTable() {
		free();
	}
	
	Node* insert(Token key, Node* value) {
		if (current >= capacity)
			resize(nextPrime(capacity));

		Pair* entry = findPair(key);

		if (entry == nullptr)
			current++;
		entry->key = key;
		entry->value = value;

	}

	Pair* findPair(Token key) {
		size_t index = key.id % capacity;
		for (int i = index; i < capacity; i++) {
			if (entries[i].key.type == key.type && entries[i].key.name == key.name) {

			}
		}
	}

	
};

struct Node {

	Token data;
	Node* left = nullptr;
	Node* right = nullptr;

	Node(Token data, Node* left = nullptr, Node* right = nullptr) : data(data), left(left), right(right) {};
};

class Parser {
	vector<Token> tokens;
	size_t i = 0;
	Token currentToken;
	//Node* root;
public:
	Parser(string lines) {
		tokens = tokenizeAll(lines);
		currentToken = tokens[0];
	}
	bool nextToken() {
		i++;
		if (i >= tokens.size())
			return 0;
		//i++;
		currentToken = tokens[i];
		return 1;
	}
	Token peek() {
		size_t temp = i + 1;
		if (temp >= tokens.size())
			return Token();
		return tokens[temp];
	}
	/*New: Evaluate EXPRESSIONS using Operator Precedence Parser to build an AST:*/
	Node* parseExpression() {
		return parseExpressionHelper(makeLeaf(), 0);
	}
	/*parseExpression helper function*/
	Node* parseExpressionHelper(Node* left, bool precedence) {
		Token lookahead = peek();
		while (lookahead.type == TokenTypes::BinOp && lookahead.precedence >= precedence) {
			Token binOp = lookahead;
			nextToken();
			nextToken();
			Node* right = makeLeaf();
			lookahead = peek();
			while (lookahead.type == TokenTypes::BinOp && lookahead.precedence >= binOp.precedence) {
				right = parseExpressionHelper(right, lookahead.precedence);
				lookahead = peek();
			}
			left = new Node(binOp, left, right);
		}
		return left;
	}
	//We represent a terminal from the rule FACTOR -> VAR | Num | (Expr) as a leaf in the AST:
	Node* makeLeaf() {
		switch (currentToken.type) {
		case TokenTypes::Number:
		case TokenTypes::Variable:
			return new Node(currentToken);
		case TokenTypes::LeftBracket: {
			nextToken();
			Node* leaf = parseExpression();
			nextToken();
			if (currentToken.type != TokenTypes::RightBracket)
				throw "error";
			//nextToken();
			return leaf;
		}
		}
		//return new Node(currentToken);
	}
	/*We will keep assigned variables */
	Node* Assign() { // a = 5+3 /2 -> a = 4;
		/*
		a = 1
		b = 3
		a = b + 2*/
		Node* left = new Node(currentToken);
		nextToken();
		Token key = currentToken;
		nextToken();
		Node* right = parseExpression();
		return new Node(key, left, right);
	}
	int Evaluate(Node* root) {
		switch (root->data.type) {
		case TokenTypes::Assignment:


		case TokenTypes::Number:
			return root->data.value;
		case TokenTypes::BinOp:
			switch (root->data.op) {
			case '*':
				return Evaluate(root->left) * Evaluate(root->right);
			case '/':
				return Evaluate(root->left) / Evaluate(root->right);
			case '%':
				return Evaluate(root->left) % Evaluate(root->right);
			case '+':
				return Evaluate(root->left) + Evaluate(root->right);
			case '-':
				return Evaluate(root->left) - Evaluate(root->right);

			}
		}
	}
};
