//!!!MEMORY LEAK
#include "Interpreter.hpp"

int main() {
	
	Lexer expr1("F[x] = a-5\nb = F[6] + 3\nprint b");
	Parser par(expr1.tokens);
	Node* root = par.parseAll();
	//std::cout << 3;
	Interpreter interp;
	interp.Evaluate(root);

	return 0;
}