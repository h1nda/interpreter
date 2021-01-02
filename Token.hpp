
/*To help with breaking up an equation, we create a Token class 
that will store data (*,/,+ or integers) and their type
Type: NUMBER, VARIABLE, FUNCTION DEFINITION, FUNCTION, =, OPERATOR, and other*/
#include <string>
#include "Parse.hpp"
using namespace std;
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
	Token(){}
	//Tokenizes the seperate parts of a string:
	Token tokenize(string s) {
		Token tkn;
		if (isParseableInt(s, value)) {
			tkn.type = TokenTypes::Number;
		}
		else if (s == "(")
			tkn.type = TokenTypes::LeftBracket;
		else if (s == ")")
			tkn.type = TokenTypes::RightBracket;
		else {
			tkn.type = TokenTypes::BinaryOperator;
			switch (s[0]) {
			case '*':
				tkn.op = '*';
				tkn.precedence = 1;
			case '/': 
				tkn.op = '/';
				tkn.precedence = 1;
			case '%':
				tkn.op = '%';
				tkn.precedence = 1;
			case '+': 
				tkn.op = '+';
				tkn.precedence = 0;
			case '-': 
				tkn.op = '-';
				tkn.precedence = 0;
			}
		}
	}
};