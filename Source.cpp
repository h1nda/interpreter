//!!!MEMORY LEAK
#include "Interpreter.hpp"

int main() {
	
	Lexer expr1("F[x] = x*3-6");
	Parser par(expr1.tokens);
	Node* root = par.parseAll();
	Interpreter interp;
	interp.Evaluate(root);

	return 0;
}