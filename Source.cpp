#include "Node.hpp"
int main() {
	string toParse = "10 * 4 - 2 / 10";
	Node* root = ShuntingYard(toParse);
	cout << Evaluate(root);
}