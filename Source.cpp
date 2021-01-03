#include "Node.hpp"
int main() {
	string toParse = "403 % 3 / (11 + 46)";
	Parser test(toParse);
	test.Parse();

}