#pragma once //DELETE L8R
/*To help with breaking up an equation, we create a Token class
that will store data (*,/,+ or integers) and their type
Type: NUMBER, VARIABLE, FUNCTION DEFINITION, FUNCTION, =, OPERATOR, and other*/
#include <string>
const int VAR_TERMINALS = 31;
enum class TokenTypes {
	END,
	BLOCK,
	PRINT,
	READ,
	NUMBER,
	VAR,
	MULT,
	SUB,
	MOD,
	DIV,
	ADD,
	NEWLINE,
	FUNCDECL,
	FUNCCALL,
	ASSIGN,
	LEFT_BRACKET,
	LEFT_SQ_BR,
	RIGHT_SQ_BR,
	RIGHT_BRACKET,
	FUNCTION,
	PARAMATER
};
class Token {
public:
	TokenTypes type = TokenTypes::END;
	int value = -1; // for numbers
	std::string name; // for variable and function names
	unsigned long int hash = -1;// for var/func lookup table 
	bool precedence = 1; // We are dealing with two types of precedence - HIGH = 1 (*,/,%) or LOW = 0 (+ ,-);
	int line = 0; // save for if error occurs
unsigned long int hashFunction() { //Polynomial rolling hash
		unsigned long int hash = 0;
		int n = name.length();
		for (int i = 0; i < n; i++) {
			hash += name[i] * pow(VAR_TERMINALS, i);
		}
		return hash;
	}
public:
	Token() {};
	Token(TokenTypes type, int line = 0) {
		if (type == TokenTypes::ADD || type == TokenTypes::SUB)
			precedence = false;
		this->type = type;
		this->line = line;
	}
	Token(TokenTypes type, int value, int line) : type(type), value(value), line(line) {};
	Token(TokenTypes type, std::string name, int line = 0) {
		this->name = name;
		if (type == TokenTypes::FUNCTION || type == TokenTypes::VAR) {
			this->hash = hashFunction();
		}
		this->type = type;
		this->line = line;
	}
};

