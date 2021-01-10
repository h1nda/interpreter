#include "Lexer.hpp"
//Abstract syntax tree node struct
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
//The Parser will build an abstract syntax tree (AST). It is similiar to a parser tree but many of the operators are inferred. 
class Parser {
	SinglyLinkedList<Token> tokens; //takes in a list of tokens
	SinglyLinkedList<Token>::Iterator currentTokenIndex; //we track the iterator over the tokens, so the recursion across the different functions would be easier
	void expect(TokenTypes type, const char* tokench) { //to make sure the user's input corresponds to EXPR's grammar rules, for example: closing brackets, equal sign
		if ((*currentTokenIndex).type != type)
		{
			error(tokench);
		}
	}
	void error(const char* tokench) {
		std::cerr << "UNEXPECTED TOKEN ERROR: expected " << tokench << " on line #" << (*currentTokenIndex).line << std::endl;
		exit(1);
	} //outputs an error and exits
	void next() {
		currentTokenIndex++;
	} //advances the iterator
	Token peek() {
		Token next = *currentTokenIndex.peek();
		return next;
	} //so the parser can 'predict' what's next and take according action
	bool isNextBinaryOp() { //self-explanatory
		return peek().type == TokenTypes::ADD || peek().type == TokenTypes::SUB ||
			peek().type == TokenTypes::MULT || peek().type == TokenTypes::DIV || peek().type == TokenTypes::MOD;
	}
	//The grammar for EXPR can be divided into two parts: expressions and statements. parseExpression() deals with the expressions. Uses a recursive Operator Precedence Parsing algorithm. The tree for an expression is:
	/*         binOp (+,-,*,%,/)
	          /     \
	     Terminal   Terminal*/
	Node* parseExpression() {
		return parseExpressionHelper(Terminal(), 0); //starts off with building a terminal because expr rules are in the from TERM + TERM | TERM - TERM, etc.
	}
	/*parseExpression helper function*/
	Node* parseExpressionHelper(Node* left, bool precedence) {
		Token lookahead = peek(); //sees the upcoming token
		while (isNextBinaryOp() && lookahead.precedence >= precedence) { //if it's a binary operation and a higher precedence than current
			Token binOp = lookahead;
			next(); //consumes the lookahead token
			next(); //moves to the next one
			Node* right = Terminal(); // always has to be a term
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
	//The other part of EXPR's grammar are statements. They are represented by the LINE grammar rule. Statements in EXPR are print, read and function and variable Declarations.
	Node* parseStatement() {
		Node* left = nullptr;
		switch ((*currentTokenIndex).type) {
		case TokenTypes::PRINT: { //RULE is PRINT EXPR
			Token print = *currentTokenIndex; 
			next();
			left = new Node(print, parseExpression()); // PRINT node with left child that's an expression
			next();
			return left;
		}
		case TokenTypes::READ: { //Rule is READ Var
			Token read = *currentTokenIndex;
			next();
			expect(TokenTypes::VAR, "{a-z}*");
			left = new Node(read, Terminal()); //similar to READ: READ node with a left child that's a variable
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
	//This function builds the AST and returns the root. Here we are using the TokenType BLOCK that basically introduces hierarchy in the tree, so that statements are interpreted in sequence. A BLOCK node's left child is always another BLOCK statement or nullptr. Its' right child is always a statement. For example, take the source
	/*a = 3;
	INC[x] = x + 1
	print (a+b). The AST for this should look like:*/
	//Three BLOCK nodes, as there are three lines:
	/*                     BLOCK
	*                   /       \
	             BLOCK          print
			     /     \         /
	            /        =      a
		      /      /      \
		     /   FUNCDECL     +
            /    /     \     /  \
		   /  INC       x   x    1
		BLOCK
		/   \
	null     =
	       /   \
		  a     3
	When we are interpreting this tree, we are going to start from the bottom and work our way up.
			 */
	Node* parseAll() {
		Node* block = nullptr;
		while ((*currentTokenIndex).type != TokenTypes::END) {
			if ((*currentTokenIndex).type == TokenTypes::NEWLINE)
				next();
			else
				block = new Node(TokenTypes::BLOCK, block, parseStatement());
		}
		return block;
	}
};
