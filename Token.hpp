#pragma once //DELETE L8R
/*To help with breaking up an equation, we create a Token class 
that will store data (*,/,+ or integers) and their type
Type: NUMBER, VARIABLE, FUNCTION DEFINITION, FUNCTION, =, OPERATOR, and other*/
#include <string>
const int VAR_TERMINALS = 31;
enum class TokenTypes {
		Null,
		BLOCK,
		Print,
		Read,
		Number,
		Variable,
		MULT,
		SUB, 
		MOD,
		DIV,
		ADD,
		NEWLINE,
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
	//char op = ' '; // for operators
	std::string name; // for variable and function names
	unsigned long int hash = -1;// for var/func lookup table 
	bool precedence = 1; // We are dealing with two types of precedence - HIGH = 1 (*,/,%) or LOW = 0 (+ ,-);
	int line = 0; // save for if error occurs
	//size_t varCount = 0;
public:
	Token() {};
	//TESTING FUNCTION
	void printHash() {
		std::cout << hash;
	}
	Token(TokenTypes type, int line =0) {
		if (type == TokenTypes::ADD || type == TokenTypes::SUB)
			precedence = false;
		this->type = type;
		this->line = line;
	}
	Token(TokenTypes type, int value, int line) : type(type), value(value), line(line) {};
	Token(TokenTypes type, std::string name, int line) {
		this->name = name;
		if (type == TokenTypes::FunctionDef || type == TokenTypes::Variable) {
			this->hash = hashFunction();
		}
		this->type = type;
		this->line = line;
	}
	unsigned long int hashFunction() { //Polynomial rolling hash
		unsigned long int hash = 0;
		int n = name.length();
		for (int i = 0; i < n; i++) {
			hash += name[i] * pow(VAR_TERMINALS, i);
		}
		return hash;
	}
	//Makes one token out of already split string parts
	/*Token(std::string s) {
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
	}*/
	/*void print() const {
		if (type == TokenTypes::Number)
			std::cout << value;
		else
			std::cout << op;
	}*/

	
};

// VARIABLES will be a special type of token that have a char and a value. 
//Splits the string into vector then tokenise each one and push into token vector
//std::vector<Token> tokenizeAll(const std::string& s) {
//	std::vector<std::string> split = splitString(s);
//	std::vector<Token> tokens;
//	for (int i = 0; i < split.size(); i++) {
//		tokens.push_back(Token(split[i]));
//	}
//	return tokens;
//}

