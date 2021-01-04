
/*To help with breaking up an equation, we create a Token class 
that will store data (*,/,+ or integers) and their type
Type: NUMBER, VARIABLE, FUNCTION DEFINITION, FUNCTION, =, OPERATOR, and other*/

/*TO-DO:
Add Token Type ASSOCIATIVITY bc direct assignment operator '=' is right associative*/
#include "Parse.hpp"
enum class TokenTypes {
		Null,
		Number,
		Variable,
		MULT,
		BinOp,
		ADD,
		SUB,
		MOD,
		DIV,
		LeftBracket,
		RightBracket,
		FunctionCall,
		FunctionDef,
		Parameter
	};
class Token { 
public:
	TokenTypes type = TokenTypes::Null;
	int value = -1;
	char op = ' ';
	bool precedence = 1; // We are dealing with two types of precedence - HIGH = 1 (*,/,%) or LOW = 0 (+,-);
	//size_t varCount = 0;
public:
	Token() {};
	//Makes one token out of already split string parts
	Token(string s) {
		if (isParseableInt(s, value)) {
			type = TokenTypes::Number;
		}
		else if (s == "(")
			type = TokenTypes::LeftBracket;
		else if (s == ")")
			type = TokenTypes::RightBracket;
		else {
			switch (s[0]) {
			case '*':
				op = '*';
				type = TokenTypes::BinOp;
				precedence = 1;
				break;
			case '/':
				op = '/';
				type = TokenTypes::BinOp;
				precedence = 1;
				break;
			case '%':
				op = '%';
				type = TokenTypes::BinOp;
				precedence = 1;
				break;
			case '+':
				op = '+';
				type = TokenTypes::BinOp;
				precedence = 0;
				break;
			case '-':
				op = '-';
				type = TokenTypes::BinOp;
				precedence = 0;
				break;
			}
		}
	}
	void print() const {
		if (type == TokenTypes::Number)
			cout << value;
		else
			cout << op;
	}
	friend ostream& operator<<(ostream& out, const Token& io) {
		if (io.type == TokenTypes::Number) {
			out << io.value;
		}
		else
			out << io.op;
		return out;
	}
	
};
//Splits the string into vector then tokenise each one and push into token vector
vector<Token> tokenizeAll(const string& s) {
	vector<string> split = splitString(s);
	vector<Token> tokens;
	for (int i = 0; i < split.size(); i++) {
		tokens.push_back(Token(split[i]));
	}
	return tokens;
}

