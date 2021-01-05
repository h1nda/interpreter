#include "Node.hpp"
int main() {
	string assign = " a = (43 + 3) / 2";
	Parser test1(assign);
	Node* a = test1.Assign();
	//cout << "Value of variable " << a->left->data.op << " is " << 
		//test1.Evaluate(a->right);
	cout << mapFunction("discriminant", 31) << endl;
	cout << mapFunction("alpha", 31) << endl;
	cout << mapFunction("q", 31) << endl;
	//cout << test.Evaluate(test.Expression());
}