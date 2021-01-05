#include "Node.hpp"
int main() {
	string assign = "2 + 3 * 4";
	Parser test1(assign);
	Node* root =test1.parseExpression();
	cout << test1.Evaluate(root);
	//cout << test.Evaluate(test.Expression());
}