/*This parses a split string into a number*/
#include <cstdlib>
#include "SinglyLinkedList.hpp"
#include "Token.hpp"
class Lexer {
public: //REMOVE L8R
	std::string sourceCode;
	SinglyLinkedList<Token> tokens;
	int current = 0;
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
			case '\t':
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
			default:
				if (isDigit()) {
					int value = parseStringToInt();
					buildToken(TokenTypes::NUMBER, value);
				}
				else if (isLowerCase()) {
					std::string name = buildVariableName();
					if (name == "print")
						buildToken(TokenTypes::PRINT);
					else if (name == "read")
						buildToken(TokenTypes::READ);
					else {
						buildToken(TokenTypes::VAR, name);
					}
				}
				else if (isUpperCase()) {
					std::string name = buildFunctionName();
					buildToken(TokenTypes::FUNCTION, name);
				}
				else {
					std::cout << "UNDEFINED TOKEN ERROR: unknown symbol '" << sourceCode[current] << "' on line #" << line << std::endl;
					std::cout << "exit"; 
					std::exit(1);
				}

			}
		}
		buildToken(TokenTypes::END);
		//return tokens;
	}
	bool isDigit() {
		return (sourceCode[current] >= '0' && sourceCode[current] <= '9');
	}
	bool isFunction(char ch) {
		return (sourceCode[current] >= 'A' && sourceCode[current] <= 'Z');
	}
	bool isLowerCase() {
		return sourceCode[current] >= 'a' && sourceCode[current] <= 'z';
	}
	bool isUpperCase() {
		return sourceCode[current] >= 'A' && sourceCode[current] <= 'Z';
	}
	std::string buildVariableName() {
		std::string temp;
		while (isLowerCase()) {
			temp += sourceCode[current++];
		}
		return temp;
	}
	std::string buildFunctionName() {
		std::string temp;
		while (isUpperCase()) {
			temp += sourceCode[current++];
		}
		return temp;
	}
	std::string buildNumberFromString() {
		std::string temp;
		while (isDigit()) {
			temp += sourceCode[current++];
		}
		return temp;
	}
	int parseStringToInt() {
		std::string s = buildNumberFromString();/*Returns true or false and saves the parsed number into result*/
		int result = 0;
		for (int i = 0; i < s.length(); i++) {
			result = result * 10 + (s[i] - '0');
		}
		return result;
	}
public:
	Lexer(std::string src) {
		sourceCode = src;

		generateTokenList();

	}
};

