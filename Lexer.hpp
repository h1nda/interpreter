//The Lexer taken in the source code and breaks it up in tokens using several functions to determine what token type should be assigned
#include "SinglyLinkedList.hpp"
#include "Token.hpp"
class Lexer {
	friend class EXPR;
	std::string sourceCode;
	int current = 0; //to iterate through sourceCode
	int line = 1;
	void buildToken(TokenTypes type) {
		tokens.pushBack(Token(type, line));
	} // FOR SYMBOLS
	void buildToken(TokenTypes type, int value) {
		tokens.pushBack(Token(type, value, line));
	} //FOR NUMBERS
	void buildToken(TokenTypes type, std::string name) {
		tokens.pushBack(Token(type, name, line));
	} //FOR VARIABLES/FUNCTIONS/KEYWORDS
	void generateTokenList() { 
		while (current < sourceCode.size()) {
			switch (sourceCode[current]) {
			case ' ':
			case '\t': //ignore whitespaces and tabulations
				current++;
				break;
			case 'x': //functions can only be declared with a parameter 'x'. 
				buildToken(TokenTypes::PARAMATER);
				current++;
				break;
			case '\n': 
				buildToken(TokenTypes::NEWLINE);
				line++;
				current++;
				break;
			case '(':
				buildToken(TokenTypes::LEFT_BRACKET);
				current++;
				break;
			case ')':
				buildToken(TokenTypes::RIGHT_BRACKET);
				current++;
				break;
			case ']':
				buildToken(TokenTypes::RIGHT_SQ_BR);
				current++;
				break;
			case '[':
				buildToken(TokenTypes::LEFT_SQ_BR);
				current++;
				break;

			case '*':
				buildToken(TokenTypes::MULT);
				current++;
				break;
			case '/':
				buildToken(TokenTypes::DIV);
				current++;
				break;
			case '+':
				buildToken(TokenTypes::ADD);
				current++;
				break;
			case '-':
				buildToken(TokenTypes::SUB);
				current++;
				break;
			case '%':
				buildToken(TokenTypes::MOD);
				current++;
				break;
			case '=':
				buildToken(TokenTypes::ASSIGN);
				current++;
				break;
			case '\0': //reaching END OF FILE
				buildToken(TokenTypes::END);
				current++;
				break;
			default:
				if (isDigit()) {
					int value = parseStringToInt();
					buildToken(TokenTypes::NUMBER, value);
				}
				else if (isLowerCase()) {
					std::string name = buildVariableName(); //if it encounters a lowercase letter, try building a string of lowercase letters
					//PRINT and READ are special cases as they are keywords of EXPR
					if (name == "print")
						buildToken(TokenTypes::PRINT);
					else if (name == "read")
						buildToken(TokenTypes::READ);
					else {
						buildToken(TokenTypes::VAR, name); //EXPR variables are defined as a string of strictly lowercase letters
					}
				}
				else if (isUpperCase()) {
					std::string name = buildFunctionName();
					buildToken(TokenTypes::FUNCTION, name); //EXPR functions are defines as a string of strictly uppercase letters 
				}
				else { //in case it encounters undefines symbols such as #,$,!, etc.
					std::cout << "LEXER ERROR: unknown token '" << sourceCode[current] << "' on line #" << line << std::endl;
					std::cout << "exit";
					std::exit(1);
				}

			}
		}
		//return tokens;
	}
	bool isDigit() {
		return (sourceCode[current] >= '0' && sourceCode[current] <= '9');
	}
	bool isLowerCase() {
		return sourceCode[current] >= 'a' && sourceCode[current] <= 'z';
	}
	bool isUpperCase() {
		return sourceCode[current] >= 'A' && sourceCode[current] <= 'Z';
	}
	std::string buildVariableName() {
		std::string temp;
		while (isLowerCase()) { //only lowercase letters
			temp += sourceCode[current++];
		}
		return temp;
	}
	std::string buildFunctionName() {
		std::string temp;
		while (isUpperCase()) { //only uppercase letters
			temp += sourceCode[current++];
		}
		return temp;
	}
	std::string buildNumberFromString() { //extracts a substring of digits
		std::string temp;
		while (isDigit()) {
			temp += sourceCode[current++];
		}
		return temp;
	}
	int parseStringToInt() {
		std::string s = buildNumberFromString();
		int result = 0;
		for (int i = 0; i < s.length(); i++) {
			result = result * 10 + (s[i] - '0');
		}
		return result;
	} //transforms the  substring of digits into an int
SinglyLinkedList<Token> tokens; //will be the output of generateTokenList();
public:
	Lexer(std::string src) {
		sourceCode = src;

		generateTokenList();

	}
	
};

