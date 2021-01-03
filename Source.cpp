#include "Token.hpp"
int main() {
	string toParse = "403 % 3 / (11 + 46)";
	vector<Token> result;
	result = tokenizeAll(toParse);
	for (int i = 0; i < result.size(); i++) {
		result[i].print();
		cout << endl;
	}
}