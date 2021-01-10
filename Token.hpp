/*To help with breaking up a line, we create a Token class that will make the parser's job easier*/
#include <string>
const int VAR_TERMINALS = 31; //The number of lowercase/uppercase latin letters, used in hashFunction()
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
}; //types of lexemes that are allowed in the EXPR language, will help the Parser decide how to build the node
class Token {
public:
	TokenTypes type = TokenTypes::END;
	int value = -1; // for numbers
	std::string name; // for variable and function names
	unsigned long int hash = -1;// for var/func symbol table 
	bool precedence = 1; // We are dealing with two types of precedence - HIGH = 1 (*,/,%) or LOW = 0 (+ ,-);
	int line = 0; //  keeping track for if error occurs
unsigned long int hashFunction() { //A polynomial rolling hash function. 
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
			precedence = false; //+ and - have lower precedence then *, /, %
		this->type = type;
		this->line = line;
	}
	Token(TokenTypes type, int value, int line) : type(type), value(value), line(line) {};
	Token(TokenTypes type, std::string name, int line = 0) {
		this->name = name;
		if (type == TokenTypes::FUNCTION || type == TokenTypes::VAR) {
			this->hash = hashFunction(); //if a Token's constructor is called with a string, that means it's a function or variable name
		}
		this->type = type;
		this->line = line;
	}
};

