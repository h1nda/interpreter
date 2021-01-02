
/*To help with breaking up an equation, we create a Token class 
that will store data (*,/,+ or integers) and their type
Type: NUMBER, VARIABLE, FUNCTION DEFINITION, FUNCTION, =, OPERATOR, and other*/

#include "Parse.hpp"

class Token {
	enum class TokenTypes {
		Number,
		Variable,
		BinaryOperator,
		LeftBracket,
		RightBracket,
		FunctionCall,
		FunctionDef,
		Parameter
	};
	TokenTypes type;
	int value;
	char op = ' ';
	bool precedence = 0; // We are dealing with two types of precedence - HIGH = 1 (*,/,%) or LOW = 0 (+,-);
	//size_t varCount = 0;
public:
	Token(){}
	//Makes one token out of already split string parts
	Token(string s) {
		Token tkn;
		if (isParseableInt(s, value)) {
			type = TokenTypes::Number;
		}
		else if (s == "(")
			type = TokenTypes::LeftBracket;
		else if (s == ")")
			type = TokenTypes::RightBracket;
		else {
			type = TokenTypes::BinaryOperator;
			switch (s[0]) {
			case '*':
				op = '*';
				precedence = 1;
				break;
			case '/':
				op = '/';
				precedence = 1;
				break;
			case '%':
				op = '%';
				precedence = 1;
				break;
			case '+':
				op = '+';
				precedence = 0;
				break;
			case '-':
				op = '-';
				precedence = 0;
				break;
			}
		}
	}
};

//Splits the string into vector then tokenise each one and push into token vector
vector<Token> tokenizeAll(vector<string> split) {
	vector<Token> tokens;
	for (int i = 0; i < split.size(); i++) {
		tokens.push_back(Token(split[i]));
	}
	return tokens;
}