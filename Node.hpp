#include "Token.hpp"
#include <iostream>
const int VAR_TERMINALS = 31;
/*To store the variables, we will build a dynamic array of expressions, where each index will correspond to a variable name (string). We use mapFunction() to encode a string into an index. This way, whenever we are calling an already declared variable, we can find/modify it in O(1). */
size_t mapFunction(string s, size_t capacity) {
	int code = 0;
	int n = s.length();
	for (int i = 0; i < n; i++) {
		code += s[i] * pow(VAR_TERMINALS,i);
	}
	return code % capacity;
}
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
