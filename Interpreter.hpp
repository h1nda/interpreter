#pragma once //DEL
#include "SymbolTable.hpp" //takes the ast then traverses/interprets/evaluates it
//Takes the root of the AST
class Interpreter {
public:
	SymbolTable<int> vars; //where we will store the corresponding values of declared variables. they are always int
	SymbolTable<Node*> funcs; //where we will store the corresponding EXPRESSIONS of declared functions. when we are calling a function, we'll lookup its' expression and substitute the parameter with the variable.
	int x; // functions can only be declared using an X parameter, this makes it easier to evaluate
public:
	Interpreter(Node* root) {
		Evaluate(root);
	}
	int DividingByZeroWarning(Token info) {
		std::cerr << "WARNING: diving by zero on line #" << info.line << ". initialising to 0!" << std::endl;
		return 0;
	}
	int validInput() { //makes sure when the READ statement is executed that the user inputs a valid int.
		int input;
		std::cin >> input;
		while (!std::cin.good()) {
			std::cerr << "INPUT ERROR: input must be an integer type: ";
			std::cin.clear();
			std::cin.ignore(256, '\n');
			std::cin >> input;
		}
		return input;
	}
	int Evaluate(Node* root) {
		if (root == nullptr)
			return 0;
		switch (root->data.type) {
		case TokenTypes::PARAMATER:
			return x;
		case TokenTypes::VAR:
			return vars.Get(root->data);
		case TokenTypes::READ: { //To read: get left node token then cin expresion to add to symbol table
			std::cout << "Enter value for variable " << root->left->data.name << ": ";
			int input = validInput();
			vars.Insert(root->left->data, input); //we then insert it in the lookup table for safekeeping
			break;
		}
		case TokenTypes::FUNCCALL:
			x = Evaluate(root->right); 
			return Evaluate(funcs.Get(root->left->data));
		case TokenTypes::ASSIGN:
			if (root->left->data.type == TokenTypes::FUNCDECL) { //if we are making a function declartion
				funcs.Insert(root->left->left->data, root->right);
				x = INT_MAX;
			}
			else // if we are making a variable declaration
			vars.Insert(root->left->data, Evaluate(root->right));
			break;
		case TokenTypes::NUMBER:
			return root->data.value;
		case TokenTypes::PRINT:
			std::cout << Evaluate(root->left) << std::endl;
		case TokenTypes::MULT:
			return Evaluate(root->left) * Evaluate(root->right);
		case TokenTypes::DIV:
			return Evaluate(root->right) == 0 ? DividingByZeroWarning(root->right->data) : Evaluate(root->left) / Evaluate(root->right);
		case TokenTypes::MOD:
			return Evaluate(root->left) % Evaluate(root->right);
		case TokenTypes::ADD:
			return Evaluate(root->left) + Evaluate(root->right);
		case TokenTypes::SUB:
			return Evaluate(root->left) - Evaluate(root->right);
		case TokenTypes::BLOCK:
			Evaluate(root->left);
			Evaluate(root->right);
			break;
		default:
			std::cerr << "UNKNOWN ERROR ENCOUNTERED." << std::endl;
			exit(1);
		}
	}
};
