#include "Lexer.hpp"
//#include <iostream>

//todo seperate node types
class Node {
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
	Parser() {}
	Parser(const SinglyLinkedList<Token>& tokens) {
		this->tokens = tokens;
		currentTokenIndex = tokens.begin();
	}
	void next() {
		currentTokenIndex++;
	}
	Token peek() {
		Token next = *currentTokenIndex.peek();
		if (next.type == TokenTypes::Null)
			return Token();
		return *(currentTokenIndex.peek());
	}
	bool isNextBinaryOp() {
		return peek().type == TokenTypes::ADD || peek().type == TokenTypes::SUB ||
			peek().type == TokenTypes::MULT || peek().type == TokenTypes::DIV || peek().type == TokenTypes::MOD;
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
	/*For making Statements into trees we will use Recursive Descent algorithm
	reason for this is so the Interpreter can traverse it from top to bottom but execute them from bottoum up and this will keep the integrity of the source codes' flow
	Recursive Descent approach:
	We will have an empty Token with type Flow, which will be the root of the tree.
	It obeys the following rules: it's the root of the tree.
	it's left-hand side is either nullptr or another Flow node
	it's right-hand side can only be a Statement Node
	*/
	Node* parseStatement() {
		Node* left = nullptr; //will be the returned node in the end, FLOW
		switch ((*currentTokenIndex).type) {
		case TokenTypes::Print: { //print node: one child, -> expr?
			Token print = *currentTokenIndex; // print
			next();
			left = new Node(print, parseExpression());
			next();// Flow, left: Flow/null, right: PrntStnt
			return left;
		}
		case TokenTypes::Variable: {
			Node* right = new Node(*currentTokenIndex);
			next();
			next(); //TO DO: MAKE SURE IT MATCHES ASSIGNMENT OPERATOR
			left = new Node(TokenTypes::Assignment, right, parseExpression());
			next();
			return left;
		}
		case TokenTypes::NEWLINE:
			next();
			break;
		}
		//next();

		}			

	Node* parseAll() {
		Node* flow = nullptr;
		while ((*currentTokenIndex).type != TokenTypes::Null) {
			if ((*currentTokenIndex).type == TokenTypes::NEWLINE)
				next();
			else
			flow = new Node(TokenTypes::BLOCK, flow, parseStatement());
			//next();
		}
		return flow;
	}
};
