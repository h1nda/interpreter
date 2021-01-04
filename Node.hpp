#include "Token.hpp"
#include <iostream>
#define COUNT 10
class Node {
public:
	Token data;
	Node* left = nullptr;
	Node* right = nullptr;
	//friend class Parser;
public:
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
	void nextToken() {
		currentToken = tokens[i++];
	}
	Node* Expression() {
		//Using Shunting Yard Algorithm
		//vector<Token> tokens = tokenizeAll(eq);
		stack<Node> nodes;
		stack<Token> ops;

		while (i < tokens.size()) {
			if (currentToken.type == TokenTypes::Number || currentToken.type == TokenTypes::Variable) {
				nodes.push(makeLeaf());
			}
			else if (currentToken.type == TokenTypes::LeftBracket) {
				ops.push(currentToken);
			}
			else if (currentToken.type == TokenTypes::RightBracket) {

				while (ops.top().type != TokenTypes::LeftBracket)
				{

					Node* right = new Node(nodes.top());
					nodes.pop();
					Node* left = new Node(nodes.top());
					nodes.pop();
					nodes.push(Node(ops.top(), left, right));
					ops.pop();

				}
				ops.pop();
			}
			else if (currentToken.type == TokenTypes::BinOp) {
				if (ops.empty() || ops.top().type == TokenTypes::LeftBracket || ops.top().precedence < currentToken.precedence) {
					ops.push(currentToken);
				}
				else {
					Node* right = new Node(nodes.top());
					nodes.pop();
					Node* left = new Node(nodes.top());
					nodes.pop();
					nodes.push(Node(ops.top(), left, right));
					ops.pop();
					ops.push(currentToken);
				}

			}
			nextToken();
		}
		while (!ops.empty()) {
			Node* right = new Node(nodes.top());
			nodes.pop();
			Node* left = new Node(nodes.top());
			nodes.pop();
			nodes.push(Node(ops.top(), left, right));
			ops.pop();
		}

		Node* root = new Node(nodes.top());
		return root;

	}

	Node makeLeaf() {
		return Node(currentToken);
	}
	/*Node* Assign() {
		Node* left = new Node(tokens[0]);
		Node* root = new Node(tokens[1]);
		Node* right = Expression(tokens + 1);
	}*/
	int Evaluate(Node* root) {
		switch (root->data.type) {
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
//Node* VariableAssignment(string assng) {
//	vector<Token> tokens = tokenizeAll(assng);
//	for (int i = 0; i < tokens.size(); i++) {
//
//	}
//}
//Node* VariableAssignment(Node* var, Node* expr) {
//	Token assignment;
//	assignment.type = TokenTypes::Assignment;
//	assignment.op = '=';
//	return new Node(assignment, var, expr);
//}

//Node* FunctionDefinition(char name, Node* Expression) {
//	Node* def = new Node(Token)
//}
//class BinOP : public Node {
//public:
//	BinOP(Node* left, Token token, Node* right) {
//		this->left = left;
//		data = token;
//		this->right = right;
//	}
//	~BinOP() {
//		delete left;
//		delete right;
//	}
//};
//class Number : public Node {
//public:
//	Number(int value) {
//		data.value = value;
//		data.type = TokenTypes::Number;
//	}
//	~Number() {};
//};
//
//class Parser {
//	Node* BinOP(Node* left, Token token, Node* right) {
//		Node* op = new Node();
//		op->left = left;
//		op->data = token;
//		op->right = right;
//		return op;
//	}
//	Node* Number(int value) {
//		Node* number = new Node();
//		number->data.value = value;
//		number->data.type = TokenTypes::Number;
//		return number;
//	}
//
//	vector<Token> tokens;
//	Token currentToken;
//	int index;
//
//	bool isClosingBracket() {
//		return currentToken.type == TokenTypes::RightBracket;
//	}
//
//	void nextToken() {
//		currentToken = tokens[index++];
//	}
//
//	Node* Factor() { // NUMBER, (EXPR), VAR
//		switch (currentToken.type) {
//		case TokenTypes::Number: 
//		{
//			int value = currentToken.value;
//			nextToken();
//			return Number(value);
//		}
//		case TokenTypes::LeftBracket:
//		{
//			nextToken();
//			Node* expr = Expression();
//			if (isClosingBracket())
//				nextToken();
//			else
//				throw "error";
//		}
//		}
//	}
//
//	Node* Term() {
//		switch (currentToken.type) {
//		case TokenTypes::MULT:
//			{
//				Token MULT = currentToken;
//				nextToken();
//				Node* left = Term();
//				Node* right = Factor();
//				return BinOP(left, MULT, right);
//			}
//		case TokenTypes::DIV:
//		{
//			Token div = currentToken;
//			nextToken();
//			Node* left = Term();
//			Node* right = Factor();
//			return BinOP(left, div, right);
//		}
//		case TokenTypes::MOD:
//		{
//			Token MOD = currentToken;
//			nextToken();
//			Node* left = Term();
//			Node* right = Factor();
//			return BinOP(left, MOD, right);
//		}
//		}
//	}
//
//	Node* Expression() //EXPRT + TERM, EXPR - TERM, TERM {
//	{
//		switch (currentToken.type) {
//		case TokenTypes::ADD: {
//			Token ADD = currentToken;
//			nextToken();
//			Node* left = Expression();
//			Node* right = Term();
//			return BinOP(left, ADD, right);
//		}
//		case TokenTypes::SUB: {
//			Token SUB = currentToken;
//			nextToken();
//			Node* left = Expression();
//			Node* right = Term();
//			return BinOP(left, SUB, right);
//		}
//		}
//	}
//public:
//	Parser(string text) {
//		tokens = tokenizeAll(text);
//		currentToken = tokens[0];
//		int index = 0;
//	}
//
//	Node* evaluate() {
//		return Expression();
//	}
//	Parser(string text) {
//		tokens = tokenizeAll(text);
//		index = 0;
//		currentToken = tokens[index];
//		//index = 0;
//	}
//	Node* Parse() {
//		return Expression();
//	}
//	void test() {
//		nextToken();
//	}
//	void nextToken() {
//		currentToken = tokens[index++];
//	}
//	bool isClosingBracket() {
//		return currentToken.type == TokenTypes::RightBracket;
//	}
//
//	Node* Expression() {
//		Node* left = Expression();
//		Node* right;
//		Token op = currentToken;
//		switch (currentToken.type) {
//		case TokenTypes::ADD:
//			nextToken();
//			right = Term();
//			return new BinOP(left, op, right);
//		case TokenTypes::SUB:
//			nextToken();
//			right = Term();
//			return new BinOP(left, op, right);
//			
//		}
//	}
//
//	Node* Term() {
//		Node* left = Factor();
//		Node* right;
//		Token op;
//		switch (currentToken.type) {
//		case TokenTypes::MULT:
//			op = currentToken;
//			nextToken();
//			right = Term();
//			return new BinOP(left, op, right);
//		case TokenTypes::DIV:
//			op = currentToken;
//			nextToken();
//			right = Term();
//			return new BinOP(left, op, right);
//		}
//	}
//
//	Node* Factor() {
//		Node* node;
//		int value;
//		switch (currentToken.type) {
//		case TokenTypes::Number:
//			value = currentToken.value;
//			nextToken();
//			return new Number(value);
//		case TokenTypes::LeftBracket:
//			nextToken();
//			node = Expression();
//			if (isClosingBracket())
//				nextToken();
//			return node;
//		}
//	}
//};
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