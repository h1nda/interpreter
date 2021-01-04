#include "Node.hpp"
int main() {
	string toParse = "5 + 4";
	Parser test(toParse);
	cout << endl;
	cout << test.Evaluate(test.Expression());
}