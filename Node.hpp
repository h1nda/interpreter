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
	BinOP(Node* left, string op, Node* right) {
		this->left = left;
		Token temp(op);
		data = temp;
		this->right = right;
	}
};
class Number : public Node {
public:
	Number(int value) {
		data.value = value;
		data.type = TokenTypes::Number;
	}
};

class Parser {
	vector<Token> tokens;
	Token currentToken;
	int index;

	Parser(string text) {
		tokens = tokenizeAll(text);
		currentToken = tokens.front();
		index = 0;
	}

	void nextToken() {
		currentToken = tokens[index++];
	}

	Node* Factor() {
		Node* node;
		switch (currentToken.type) {
		case TokenTypes::Number:
			int value = currentToken.value;
			nextToken();
			Number* num = new Number(value);
			return num;
		case TokenTypes::LeftBracket:

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