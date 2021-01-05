#include "SinglyLinkedList.hpp"


int main() {
	//string assign = " a = (43 + 3) / 2";
	//Parser test1(assign);
	//Node* a = test1.Assign();
	////cout << "Value of variable " << a->left->data.op << " is " << 
	//	//test1.Evaluate(a->right);
	////cout << test.Evaluate(test.Expression());

	SinglyLinkedList<SinglyLinkedList<int>> a;


	for (SinglyLinkedList<SinglyLinkedList<int>>::Iterator it = a.begin(); it != a.end(); it++) {
		std::cout << *it << ' ';
	}
	//a.~SinglyLinkedList();
	
	return 0;
}
