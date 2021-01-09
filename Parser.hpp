#include "Lexer.hpp"

struct Node {
	Token data;
	Node* left = nullptr;
	Node* right = nullptr;
	Node(Token data, Node* left = nullptr, Node* right = nullptr) : data(data), left(left), right(right) {};
	Node() : data(Token(TokenTypes::END)) {
		left = nullptr;
		right = nullptr;
	}
};

class Parser {
	SinglyLinkedList<Token> tokens;
	SinglyLinkedList<Token>::Iterator currentTokenIndex;
	void expect(TokenTypes type, const char* tokench) {
		if ((*currentTokenIndex).type != type)
		{
			error(tokench);
		}
	}
	void error(const char* tokench) {
		std::cerr << "UNEXPECTED TOKEN ERROR: expected " << tokench << " on line #" << (*currentTokenIndex).line << std::endl;
		exit(1);
	}
	void next() {
		currentTokenIndex++;
	}
	Token peek() {
		Token next = *currentTokenIndex.peek();
		/*if (next.type == TokenTypes::END)
			return Token();*/
		return next;
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
	//We represent a terminal from the rule FACTOR -> VAR | Num | (Expr) |FUNC[EXPR] as a leaf in the AST:
	Node* Terminal() {
		switch ((*currentTokenIndex).type) {
		case TokenTypes::PARAMATER:
		case TokenTypes::NUMBER:
		case TokenTypes::VAR:
			return new Node(*currentTokenIndex);
		case TokenTypes::LEFT_BRACKET: {
			next();
			Node* leaf = parseExpression();
			next();
			expect(TokenTypes::RIGHT_BRACKET, "')'");
			//nextToken();
			return leaf;
		}
		case TokenTypes::FUNCTION:
			Node* funcName = new Node(*currentTokenIndex);
			next();
			expect(TokenTypes::LEFT_SQ_BR, "'[");
			next();
			Node* expr = parseExpression();
			next();
			expect(TokenTypes::RIGHT_SQ_BR, "']'");
			return new Node(TokenTypes::FUNCCALL, funcName, expr);

		}
		//return new Node(currentToken);
	}
	/*For making Statements into trees we will use Recursive Descent Parsing
	reason for this is so the Interpreter can traverse it from top to bottom but execute them from bottom up and this will keep the integrity of the source codes' flow
	Recursive Descent approach:
	We will have an empty Token with type Flow, which will be the root of the tree.
	It obeys the following rules: it's the root of the tree.
	it's left-hand side is either nullptr or another Flow node
	it's right-hand side can only be a Statement Node
	*/
	Node* parseStatement() {
		Node* left = nullptr; //will be the returned node in the end, FLOW
		switch ((*currentTokenIndex).type) {
		case TokenTypes::PRINT: { //print node: one child, -> expr?
			Token print = *currentTokenIndex; // print
			next();
			left = new Node(print, parseExpression());
			next();// Flow, left: Flow/null, right: PrntStnt
			return left;
		}
		case TokenTypes::READ: {
			Token read = *currentTokenIndex;
			next();
			expect(TokenTypes::VAR, "{a-z}*");
			left = new Node(read, Terminal());
			next();
			return left;
		}
		case TokenTypes::VAR: {
			Node* right = new Node(*currentTokenIndex);
			next();
			expect(TokenTypes::ASSIGN, "'='");
			Token assign = *currentTokenIndex;
			next();//TO DO: MAKE SURE IT MATCHES ASSIGNMENT OPERATOR
			left = new Node(assign, right, parseExpression());
			next();
			return left;
		}
		case TokenTypes::NEWLINE: {
			next();
			break;
		}
		case TokenTypes::FUNCTION:
		{
			Node* funcName = new Node(*currentTokenIndex);
			next();
			expect(TokenTypes::LEFT_SQ_BR, "'['");
			next();
			expect(TokenTypes::PARAMATER, "a parameter");
			Node* arg = new Node(*currentTokenIndex);
			next();
			expect(TokenTypes::RIGHT_SQ_BR, "']'");
			next();
			Node* prototype = new Node(TokenTypes::FUNCDECL, funcName, arg);
			expect(TokenTypes::ASSIGN, "'='");
			next();
			Node* body = parseExpression();
			Node* left = new Node(TokenTypes::ASSIGN, prototype, body);
			next();
			return left;
		}
		default:
		{std::cerr << "EXPECTED STATEMENT: invalid statement at line #" << (*currentTokenIndex).line << std::endl;
		exit(1);
		}
		}
	}
public:
	Parser() {};
	Parser(const SinglyLinkedList<Token>& tokens) {
		this->tokens = tokens;
		currentTokenIndex = tokens.begin();
	}
	Node* parseAll() {
		Node* block = nullptr;
		while ((*currentTokenIndex).type != TokenTypes::END) {
			if ((*currentTokenIndex).type == TokenTypes::NEWLINE)
				next();
			else
				block = new Node(TokenTypes::BLOCK, block, parseStatement());
			//next();
		}
		return block;
	}
};
