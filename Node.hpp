#include "Token.hpp"

class Node {
	TokenTypes type = TokenTypes::Null;
	int data = -1;
	Node* left = nullptr;
	Node* right = nullptr;
	friend class AST;
public:
	//Node() { };
	~Node() {
		delete left;
		delete right;
	}

};

class AST {
	vector<Token> tokens;
	size_t index = 0;
	Token current_token = tokens[0];

	Node* createNode(TokenTypes type, Node* left, Node* right) {
		Node* root = new Node();
		root->type = type;
		root->left = left;
		root->right = right;

	}

	Node* numberNode(int data) {
		Node* leaf = new Node();
		leaf->data = data;
		leaf->type = TokenTypes::Number;
		
		return leaf;
	}

	Node* Expr() {
		Node* left = Expr();
		Node* right = Term();
	}
	Node* Term() {
		Node* left = Term();
		Node* right = Factor();
	}
	Node* Factor() {
		Node* node;
		switch (current_token.type) {
		case TokenTypes::Number:
			int value = current_token.value;
			tokens[index++];
			return numberNode(value);
		}
	}
};