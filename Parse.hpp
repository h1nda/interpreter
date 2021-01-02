/*This parses a split string into a number*/
#include <string>
bool isDigit(char ch) {
	return (c >= '0' && c <= '9');
}
bool isFunction(char ch) {
	return (ch >= 'A' && ch <= 'Z');
}
bool isVariable(char ch) {
	return (ch >= 'a' && ch <= 'z');
}
bool isParseableInt(std::string s, int& result) { /*Returns true or false and saves the parsed number into result*/
	if (!isDigit(s[0]))
		return false;
	result = 0;
	for (int i = 0; i < s.length(); i++) {
		result = result * 10 + (s[i] - '0');
	}
	return true;
}
