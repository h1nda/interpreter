//!!!MEMORY LEAK
#include "Interpreter.hpp"

int main() {
	
	Lexer expr1("b = 4 +4 *10\nprint b\nread q\nprint q+b");
	Parser par(expr1.tokens);
	Node* root = par.parseAll();
	Interpreter interp;
	interp.Evaluate(root);

	return 0;
}