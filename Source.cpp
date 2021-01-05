#include "Node.hpp"
int main() {
	string assign = " a = (43 + 3) / 2";
	Parser test1(assign);
	Node* a = test1.Assign();
	cout << "Value of variable " << a->left->data.op << " is " << 
		test1.Evaluate(a->right);
	
	//cout << test.Evaluate(test.Expression());
}