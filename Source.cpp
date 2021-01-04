#include "Node.hpp"
int main() {
	string assign = "a = 1505 % 64 + 5 / (20 -5) * 30";
	Parser test1(assign);
	Node* assignmentTree = test1.Assign();
	cout << "Value of " << assignmentTree->left->data.op << " is " << test1.Evaluate(assignmentTree->right);
	//cout << test.Evaluate(test.Expression());
}