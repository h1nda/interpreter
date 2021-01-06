#include "Lexer.hpp"
//#include <iostream>
struct Node {
	Token data;
	Node* left = nullptr;
	Node* right = nullptr;
	Node(Token data, Node* left = nullptr, Node* right = nullptr) : data(data), left(left), right(right) {};

};

class Parser {
	SinglyLinkedList<Token> tokens;
	SinglyLinkedList<Token>::Iterator currentTokenIndex;
	//Node* root;
public:
	Parser(SinglyLinkedList<Token> tokens) {
		this->tokens = tokens;
		currentTokenIndex = tokens.begin();
	}
	void next() {
		currentTokenIndex++;
	}
	Token peek() {
		return *(currentTokenIndex.peek());
	}
	bool isNextBinaryOp() {
		return peek().type == TokenTypes::ADD || peek().type == TokenTypes::SUB ||
			peek().type == TokenTypes::MULT || peek().type == TokenTypes::DIV;
	}
	/*New: Evaluate EXPRESSIONS using Operator Precedence Parser to build an AST:*/
	Node* parseExpression() {
		return parseExpressionHelper(Terminal(), 0);
	}
	/*parseExpression helper function*/
	Node* parseExpressionHelper(Node* left, bool precedence) {
		Token lookahead = peek();
		while (isNextBinaryOp() && lookahead.precedence >= precedence) {
			Token binOp = lookahead;
			next();
			next();
			Node* right = Terminal();
			lookahead = peek();
			while (isNextBinaryOp() && lookahead.precedence >= binOp.precedence) {
				right = parseExpressionHelper(right, lookahead.precedence);
				lookahead = peek();
			}
			left = new Node(binOp, left, right);
		}
		return left;
	}
	//We represent a terminal from the rule FACTOR -> VAR | Num | (Expr) as a leaf in the AST:
	Node* Terminal() {
		switch ((*currentTokenIndex).type) {
		case TokenTypes::Number:
		case TokenTypes::Variable:
			return new Node(*currentTokenIndex);
		case TokenTypes::LeftBracket: {
			next();
			Node* leaf = parseExpression();
			next();
			if ((*currentTokenIndex).type != TokenTypes::RightBracket)
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
		Node* left = new Node(*currentTokenIndex);
		next();
		Token key = *currentTokenIndex;
		next();
		Node* right = parseExpression();
		return new Node(key, left, right);
	}
	int Evaluate(Node* root) {
		switch (root->data.type) 
		{
		case TokenTypes::Assignment:
		case TokenTypes::Number:
			return root->data.value;
		case TokenTypes::MULT:
				return Evaluate(root->left) * Evaluate(root->right);
		case TokenTypes::DIV:
				return Evaluate(root->left) / Evaluate(root->right);
		case TokenTypes::MOD:
				return Evaluate(root->left) % Evaluate(root->right);
		case TokenTypes::ADD:
				return Evaluate(root->left) + Evaluate(root->right);
		case TokenTypes::SUB:
				return Evaluate(root->left) - Evaluate(root->right);

		}
	}
};
