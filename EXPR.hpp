#include "Interpreter.hpp"
#include <fstream>
class EXPR {
	std::string sourceCode;
	SinglyLinkedList<Token> tokens;
	size_t fileSize(std::ifstream& fileStream) {
		fileStream.seekg(0, std::ios::end);
		size_t size = fileStream.tellg();
		fileStream.seekg(0, std::ios::beg);
		return size;
	}
	friend class Lexer;
	void freeAST(Node* root) {
		if (root == nullptr)
			return;
		freeAST(root->left);
		freeAST(root->right);

		delete root;
	}
	void load(std::ifstream& ifs) {
		size_t len = fileSize(ifs);
		sourceCode.resize(len);
		ifs.read(&sourceCode[0], sourceCode.size());
		ifs.close();
		run();

	}
	void run() {
		Lexer lexer(sourceCode);
		tokens = lexer.tokens;
		Parser parser(tokens);
		Node* AST = parser.parseAll();
		Interpreter interpret(AST);
		freeAST(AST);
		//exit(0);
	}
public:
	void start() {
		std::ifstream loadedFile;
		std::cout << "PLEASE ENTER THE SOURCE CODE'S FILE NAME:" << std::endl;
		std::string name;
		std::cin >> name;
		loadedFile.open(name);
		while (!loadedFile) {
			std::cerr << "FILE NOT FOUND OR CANNOT OPEN. YOU CAN TRY AGAIN OR ENTER exit TO EXIT:" << std::endl;
			std::cin.clear();
			std::cin.ignore(256, '\n');
			std::cin >> name;
			if (name == "exit") {
				std::cout << "EXITING..." << std::endl;
				exit(1);
			}
			loadedFile.open(name);
		}
		std::cout << "LOADED " << name << " SUCCESSFULLY!" << std::endl;
		load(loadedFile);
	}
};