
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
		Assignment,
		LeftBracket,
		RightBracket,
		FunctionCall,
		FunctionDef,
		Parameter
	};
class Token { 
public:
	TokenTypes type = TokenTypes::Null;
	int value = -1; // for numbers
	char op = ' '; // for operators
	string name; // for variable and function names
	int id = -1;// for var/func lookup table 
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
		else if (isVariable(s)) {
			type = TokenTypes::Variable;
			name = s;
			id = hashFunction(s);
		}
		else {
			switch (s[0]) {
			case '=':
				op = '=';
				type = TokenTypes::Assignment;
				break;
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
	Token(char letter) {


	}

	void print() const {
		if (type == TokenTypes::Number)
			cout << value;
		else
			cout << op;
	}

	
};

// VARIABLES will be a special type of token that have a char and a value. 
//Splits the string into vector then tokenise each one and push into token vector
vector<Token> tokenizeAll(const string& s) {
	vector<string> split = splitString(s);
	vector<Token> tokens;
	for (int i = 0; i < split.size(); i++) {
		tokens.push_back(Token(split[i]));
	}
	return tokens;
}

