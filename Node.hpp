#include "Token.hpp"

class Node {
protected:
	Token data;
	Node* left;
	Node* right;
public:
	Node() : left(nullptr), right(nullptr) {
	}
	virtual ~Node() = 0;
};

class BinOP : public Node {
public:
	BinOP(Node* left, Token token, Node* right) {
		this->left = left;
		data = token;
		this->right = right;
	}
	~BinOP() {
		delete left;
		delete right;
	}
};
class Number : public Node {
public:
	Number(int value) {
		data.value = value;
		data.type = TokenTypes::Number;
	}
	~Number() {};
};

class Parser {
	vector<Token> tokens;
	Token currentToken;
	int index;
public:
	Parser(string text) {
		tokens = tokenizeAll(text);
		index = 0;
		currentToken = tokens[index];
		//index = 0;
	}
	Node* Parse() {
		return Expression();
	}
	void test() {
		nextToken();
	}
	void nextToken() {
		currentToken = tokens[index++];
	}
	bool isClosingBracket() {
		return currentToken.type == TokenTypes::RightBracket;
	}

	Node* Expression() {
		Node* left = Expression();
		Node* right;
		Token op = currentToken;
		switch (currentToken.type) {
		case TokenTypes::ADD:
			nextToken();
			right = Term();
			return new BinOP(left, op, right);
		case TokenTypes::SUB:
			nextToken();
			right = Term();
			return new BinOP(left, op, right);
			
		}
	}

	Node* Term() {
		Node* left = Factor();
		Node* right;
		Token op;
		switch (currentToken.type) {
		case TokenTypes::MULT:
			op = currentToken;
			nextToken();
			right = Term();
			return new BinOP(left, op, right);
		case TokenTypes::DIV:
			op = currentToken;
			nextToken();
			right = Term();
			return new BinOP(left, op, right);
		}
	}

	Node* Factor() {
		Node* node;
		int value;
		switch (currentToken.type) {
		case TokenTypes::Number:
			value = currentToken.value;
			nextToken();
			return new Number(value);
		case TokenTypes::LeftBracket:
			nextToken();
			node = Expression();
			if (isClosingBracket())
				nextToken();
			return node;
		}
	}

};
//class AST {
//	vector<Token> tokens;
//	size_t index = 0;
//	Token current_token = tokens[0];
//
//	Node* createNode(TokenTypes type, Node* left, Node* right) {
//		Node* root = new Node();
//		root->type = type;
//		root->left = left;
//		root->right = right;
//
//	}
//
//	Node* numberNode(int data) {
//		Node* leaf = new Node();
//		leaf->data = data;
//		leaf->type = TokenTypes::Number;
//		
//		return leaf;
//	}
//
//	Node* Expr() {
//		Node* left = Expr();
//		Node* right = Term();
//	}
//	Node* Term() {
//		Node* left = Term();
//		Node* right = Factor();
//	}
//	Node* Factor() {
//		Node* node;
//		switch (current_token.type) {
//		case TokenTypes::Number:
//			int value = current_token.value;
//			tokens[index++];
//			return numberNode(value);
//		}
//	}
//};