#include "Node.hpp"
int main() {
	string toParse = "8*(6-11)";
	Node* root = ShuntingYard(toParse);
	print2D(root);
}