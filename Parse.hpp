/*This parses a split string into a number*/
#include <string>
#include <vector>
#include <iostream>
#include <stack>
using namespace std;
// Distinguish
const int VAR_TERMINALS = 31;
size_t hashFunction(string s) { //Polynomial rolling hash
	int id = 0;
	int n = s.length();
	for (int i = 0; i < n; i++) {
		id += s[i] * pow(VAR_TERMINALS, i);
	}
	return id;
}
bool isWhitespace(char ch) {
	return (ch == ' ' || ch == '/t');
}
bool isDigit(char ch) {
	return (ch >= '0' && ch <= '9');
}
bool isFunction(char ch) {
	return (ch >= 'A' && ch <= 'Z');
}
bool isVariable(std::string s) {
	for (int i = 0; i < s.size(); i++) {
		if (s[i] < 'a' || s[i] > 'z')
			return false;
	}
	return true;
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
vector<string> splitString(const std::string& s) {
	vector<string> split;
	//In case there's a number in the string:
	for (int i = 0; i < s.length(); i++) {
		string temp;
		//In case there are many whitespaces or tabs, skip through them:
		while (isWhitespace(s[i])) {
			i++;
		}
		//In case there's a number in the string, 
		if (isDigit(s[i])) {
			while (isDigit(s[i])) {
				temp += s[i];
				i++;
			}
			i--; //while loop positions i at the next non-digit and it would be skipped in the next for loop?
				// no need to check further
		}
		else {
			temp.push_back(s[i]);
		}
		split.push_back(temp);

	}
	return split;
}

